package huffman;

import java.io.ByteArrayOutputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;

/**
 * Huffman instances provide reusable Huffman Encoding Maps for
 * compressing and decompressing text corpi with comparable
 * distributions of characters.
 */
public class Huffman {
    
    // -----------------------------------------------
    // Construction
    // -----------------------------------------------

    private HuffNode trieRoot;
    private Map<Character, String> encodingMap;
    
    /**
     * Creates the Huffman Trie and Encoding Map using the character
     * distributions in the given text corpus
     * @param corpus A String representing a message / document corpus
     *        with distributions over characters that are implicitly used
     *        throughout the methods that follow. Note: this corpus ONLY
     *        establishes the Encoding Map; later compressed corpi may
     *        differ.
     */
    Huffman (String corpus) {    	
    	generateHuffTrie(getCharFrequencies(corpus));
    	encodingMap = new HashMap<Character, String>();  	
    	setEncodingMap(trieRoot, "");
    }
    
    /**
     * Creates a Map representing how many times a character appears in a given string.
     * @param String containing the characters.
     * @return Map containing the character and integer representing the 
     *         	  number of times it appears in the string.
     */
    private Map<Character, Integer> getCharFrequencies(String str) {
    	Map<Character, Integer> freq = new HashMap<Character, Integer>();
    	
    	for (int i = 0; i < str.length(); i++) {
    		if (!freq.containsKey(str.charAt(i))) {
    			freq.put(str.charAt(i), 1);
    		} else {
    			freq.put(str.charAt(i), freq.get(str.charAt(i)) + 1);
    		}
        }
    	
    	return freq;
    }
    
    /**
     * Generates a tree with edges encoding characters.
     * @param Map containing the character and integer representing the 
     *           number of times it appears in the string.
     */
    private void generateHuffTrie(Map<Character, Integer> frequencies) {
    	Queue<HuffNode> queue = new PriorityQueue<>();
    	
    	for (Character c : frequencies.keySet()) {
    		queue.add(new HuffNode(c, frequencies.get(c)));
    	}           
    	    	  
    	while (queue.size() > 1) {
    		HuffNode n1 = queue.poll();
            HuffNode n2 = queue.poll();
    		HuffNode n3 = new HuffNode('/', n1.count + n2.count);
    		
    		n3.left = n1;
    		n3.right = n2;
    		
    		queue.add(n3);
    	}
    	
    	trieRoot = queue.poll();
    	
    	return;
    }
    
    /**
     * Performs a recursive depth first search to find the encodings
     * of each character, results are stored in a Map
     * @param HuffNode node and string s representing the node and the 
     *           encoded string.
     */
    private void setEncodingMap(HuffNode node, String s) {
    	if (node.isLeaf() && s.isEmpty()) {
        	encodingMap.put(node.character, s + "0");
        	return;
    	} else {
            if (node.isLeaf()) {
            	encodingMap.put(node.character, s);
                return; 
            }
            setEncodingMap(node.left, s + "0"); 
            setEncodingMap(node.right, s + "1");     		
    	}
    }
        
    // -----------------------------------------------
    // Compression
    // -----------------------------------------------
    
    /**
     * Compresses the given String message / text corpus into its Huffman coded
     * bitstring, as represented by an array of bytes. Uses the encodingMap
     * field generated during construction for this purpose.
     * @param message String representing the corpus to compress.
     * @return {@code byte[]} representing the compressed corpus with the
     *         Huffman coded bytecode. Formatted as 3 components: (1) the
     *         first byte contains the number of characters in the message,
     *         (2) the bitstring containing the message itself, (3) possible
     *         0-padding on the final byte.
     */
    public byte[] compress (String message) {
        ByteArrayOutputStream compressedMsg = new ByteArrayOutputStream(4);        
        String bitstring = generateBitstring(message);
    	int msgByte = Integer.parseInt(bitstring, 2);

        compressedMsg.write(message.length());
    	         
 		if (bitstring.length() > 8) {
 			compressedMsg.write(msgByte >> (bitstring.length() - 8));
 		    compressedMsg.write(msgByte << (16 - bitstring.length()));
 		} else {
 		    compressedMsg.write(msgByte << (8 - bitstring.length()));
 		}
 		
        return compressedMsg.toByteArray();
    }
    
    /**
     * Uses the encoding map to generate a message's bitstring
     * @param msg is a string message
     * @return message bitstring
     */
    private String generateBitstring(String msg) {
    	String res = "";
    	
    	for (int i = 0; i < msg.length(); i++) {
    		res += encodingMap.get(msg.charAt(i)); 
        }
    	
    	return res;

    }

    // -----------------------------------------------
    // Decompression
    // -----------------------------------------------
    
    /**
     * Decompresses the given compressed array of bytes into their original,
     * String representation. Uses the trieRoot field (the Huffman Trie) that
     * generated the compressed message during decoding.
     * @param compressedMsg {@code byte[]} representing the compressed corpus with the
     *        Huffman coded bytecode. Formatted as 3 components: (1) the
     *        first byte contains the number of characters in the message,
     *        (2) the bitstring containing the message itself, (3) possible
     *        0-padding on the final byte.
     * @return Decompressed String representation of the compressed bytecode message.
     */
    public String decompress (byte[] compressedMsg) {    	
        String bitstring = getBitstring(compressedMsg);
        HuffNode curr = trieRoot;
        String msg = "";

    	for (int i = 0; i < bitstring.length() - 1; i++) {
    		if (msg.length() >= compressedMsg[0]) {
    			break;
    		}
    		
    		if (curr.isLeaf()) {
    			msg += curr.character;
    			curr = trieRoot;	
    		}
    		
    		if (bitstring.charAt(i) == '0') {
    			curr = curr.left;
    		} else if (bitstring.charAt(i) == '1') {
    			curr = curr.right;
    		}
    	}
    	
        return msg;
    }
    
    /**
     * Retrieves original bitstring through byte conversion and 1's complement
     *  @param byte[] the compressed message to decompress
     *  @return the message String, decoded
     */
    private String getBitstring(byte[] compressedMsg) {
		String bStr = Integer.toBinaryString(compressedMsg[1] & 0xFF);
    	
    	if (compressedMsg.length > 2) {
    		bStr += Integer.toBinaryString(compressedMsg[2] & 0xFF);
        	return String.format("%16s", bStr).replace(' ', '0');    		
    	} 

        return String.format("%8s", bStr).replace(' ', '0');    		    	
    }

    // -----------------------------------------------
    // Huffman Trie
    // -----------------------------------------------
    
    /**
     * Huffman Trie Node class used in construction of the Huffman Trie.
     * Each node is a binary (having at most a left and right child), contains
     * a character field that it represents (in the case of a leaf, otherwise
     * the null character \0), and a count field that holds the number of times
     * the node's character (or those in its subtrees) appear in the corpus.
     */
    private static class HuffNode implements Comparable<HuffNode> {
        
        HuffNode left, right;
        char character;
        int count;
        
        HuffNode (char character, int count) {
            this.count = count;
            this.character = character;
        }
        
        public boolean isLeaf () {
            return left == null && right == null;
        }
        
        public int compareTo (HuffNode other) {
            return this.count - other.count;
        }
        
    }

}
