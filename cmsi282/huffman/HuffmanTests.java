package huffman;

import static org.junit.Assert.*;
import org.junit.Test;

public class HuffmanTests {
    
    // Compression Tests
    // -----------------------------------------------
    @Test
    public void comp_t0() {
        Huffman h = new Huffman("AB");
        // byte 0: 0000 0010 = 2 (message length = 2)
        // byte 1: 0100 0000 = 64 (0 = "A", 1 = "B")
        // [!] Only first 2 bits of byte 1 are meaningful
        byte[] compressed = {2, 64};
        assertArrayEquals(compressed, h.compress("AB"));
    }
    
    @Test
    public void comp_t1() {
        Huffman h = new Huffman("AB");
        // byte 0: 0000 0010 = 2 (message length = 2)
        // byte 1: 1000 0000 = -128 (0 = "A", 1 = "B")
        // [!] Only first 2 bits of byte 1 are meaningful
        byte[] compressed = {2, -128};
        assertArrayEquals(compressed, h.compress("BA"));
    }
    
    @Test
    public void comp_t2() {
        Huffman h = new Huffman("ABBBCC");
        // byte 0: 0000 0110 = 6 (message length = 6)
        // byte 1: 1000 0111 = -121 (10 = "A", 0 = "B", C = 11)
        // byte 2: 1000 0000 = -128
        // [!] Only first bit of byte 2 is meaningful
        byte[] compressed = {6, -121, -128};
        assertArrayEquals(compressed, h.compress("ABBBCC"));
    }
    
    @Test
    public void comp_t3() {
        Huffman h = new Huffman("ABBBCC");
        // byte 0: 0000 0110 = 6 (message length = 6)
        // byte 1: 0100 1101 = 77 (10 = "A", 0 = "B", C = 11)
        // byte 2: 1000 0000 = -128
        byte[] compressed = {6, 77, -128};
        assertArrayEquals(compressed, h.compress("BABCBC"));
    }
    
    @Test
    public void comp_t4() {
        Huffman h = new Huffman("ABC");
        // byte 0: 0000 0011 = 3 (message length = 3)
        // byte 1: 0101 1000 = 88 (10 = "A", 0 = "B", C = 11)
        byte[] compressed = {3, 88};
        assertArrayEquals(compressed, h.compress("BAC"));
    }
    
    @Test
    public void comp_t5() {
        Huffman h = new Huffman("ABBBBBC");
        // byte 0: 0000 0111 = 7 (message length = 7)
        // byte 1: 0011 1110 = 62 (00 = "A", 1 = "B", C = 01)
        // byte 2: 1000 0000 = -128
        byte[] compressed = {7, 62, -128};
        assertArrayEquals(compressed, h.compress("ABBBBBC"));
    }
    
    @Test
    public void comp_t6() {
        Huffman h = new Huffman("AAA");
        // byte 0: 0000 0011 = 3 (message length = 3)
        // byte 1: 0000 0000 = 0 (0 = "A")
        byte[] compressed = {3, 0};
        assertArrayEquals(compressed, h.compress("AAA"));
    }
    
    @Test
    public void comp_t7() {
        Huffman h = new Huffman("AABBCC");
        // byte 0: 0000 0110 = 6 (message length = 6)
        // byte 1: 1010 0011 = -93 (10 = "A", 0 = "B", C = 11)
        // byte 2: 1100 0000 = -64 
        byte[] compressed = {6, -93, -64};
        assertArrayEquals(compressed, h.compress("AABBCC"));
    }
    
    @Test
    public void comp_t8() {
        Huffman h = new Huffman("ABC");
        // byte 0: 0000 0110 = 3 (message length = 6)
        // byte 1: 1001 1000 = -104 (0 = "A")
        byte[] compressed = {3, -104};
        assertArrayEquals(compressed, h.compress("ABC"));
    }
    
    // Decompression Tests
    // -----------------------------------------------
    @Test
    public void decomp_t0() {
        Huffman h = new Huffman("AB");
        // byte 0: 0000 0010 = 2 (message length = 2)
        // byte 1: 0100 0000 = 64 (0 = "A", 1 = "B")
        byte[] compressed = {2, 64};
        assertEquals("AB", h.decompress(compressed));
    }
    
    @Test
    public void decomp_t1() {
        Huffman h = new Huffman("AB");
        // byte 0: 0000 0010 = 2 (message length = 2)
        // byte 1: 1000 0000 = -128 (0 = "A", 1 = "B")
        byte[] compressed = {2, -128};
        assertEquals("BA", h.decompress(compressed));
    }
    
    @Test
    public void decom_t2() {
        Huffman h = new Huffman("ABBBCC");
        // byte 0: 0000 0110 = 6 (message length = 6)
        // byte 1: 1000 0111 = -121 (10 = "A", 0 = "B", C = 11)
        // byte 2: 1000 0000 = -128
        byte[] compressed = {6, -121, -128};
        assertEquals("ABBBCC", h.decompress(compressed));
    }
    
    @Test
    public void decom_t3() {
        Huffman h = new Huffman("ABBBCC");
        // byte 0: 0000 0110 = 6 (message length = 6)
        // byte 1: 0100 1101 = 77 (10 = "A", 0 = "B", C = 11)
        // byte 2: 1000 0000 = -128
        byte[] compressed = {6, 77, -128};
        assertEquals("BABCBC", h.decompress(compressed));
    }
    
    @Test
    public void decom_t4() {
        Huffman h = new Huffman("ABC");
        // byte 0: 0000 0011 = 3 (message length = 3)
        // byte 1: 1001 1000 = -104 (10 = "A", 0 = "B", C = 11)
        byte[] compressed = {3, -104};
        assertEquals("ABC", h.decompress(compressed));
    }
    
    @Test
    public void decom_t5() {
        Huffman h = new Huffman("AAABBB");
        // byte 0: 0000 0110 = 6 (message length = 6)
        // byte 1: 0111 0000 = 112 (0 = "A", 1 = "B")
        byte[] compressed = {6, 112};
        assertEquals("ABBBAA", h.decompress(compressed));
    }
    
    @Test
    public void decom_t6() {
        Huffman h = new Huffman("ABBCCCC");
        // byte 0: 0000 0111 = 7 (message length = 7)
        // byte 1: 0001 0111 = 23 (00 = "A", 01 = "B", C = 1)
        // byte 2: 1100 0000 = -64	
        byte[] compressed = {7, 23, -64};
        assertEquals("ABBCCCC", h.decompress(compressed));
    }
    
    @Test
    public void decom_t7() {
        Huffman h = new Huffman("AABBCC");
        // byte 0: 0000 0110 = 6 (message length = 6)
        // byte 1: 1010 0011 = -93 (10 = "A", 0 = "B", C = 11)
        // byte 2: 1100 0000 = -64
        byte[] compressed = {6, -93, -64};
        assertEquals("AABBCC", h.decompress(compressed));
    }
    
}
