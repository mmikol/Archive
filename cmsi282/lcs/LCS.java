package lcs;

import java.util.HashSet;
import java.util.Set;

/** 
  *@author Miliano Mikol
  *@author Nico Raymundo
  */
public class LCS {
    
    /**
     * memoCheck is used to verify the state of your tabulation after
     * performing bottom-up and top-down DP. Make sure to set it after
     * calling either one of topDownLCS or bottomUpLCS to pass the tests!
     */
    public static int[][] memoCheck;
    
    /**
     * LCS_LENGTH stores the length of the longest common subsequence
     */
    public static int LCS_LENGTH;
    
    // -----------------------------------------------
    // Shared Helper Methods
    // -----------------------------------------------

    public static Set<String> collectSolution(String rStr, int r, String cStr, int c, int[][] table) {
        Set<String> result = new HashSet<>();
        
        if (r == 0 || c == 0) {
        	result.add("");
        } else if (rStr.charAt(r - 1) == cStr.charAt(c - 1)) {
            for (String lcs : collectSolution(rStr, r - 1, cStr, c - 1, table)) {
            	result.add(lcs + rStr.charAt(r - 1));
            }
        } else {
            if (table[r - 1][c] >= table[r][c - 1]) {
               result.addAll(collectSolution(rStr, r - 1, cStr, c, table));
            }
            
            if (table[r][c - 1] >= table[r - 1][c]) {
            	result.addAll(collectSolution(rStr, r, cStr, c - 1, table));
            }
        }

        return result;
    }

    // -----------------------------------------------
    // Bottom-Up LCS
    // -----------------------------------------------
    
    /**
     * Bottom-up dynamic programming approach to the LCS problem, which
     * solves larger and larger subproblems iterative using a tabular
     * memoization structure.
     * @param rStr The String found along the table's rows
     * @param cStr The String found along the table's cols
     * @return The longest common subsequence between rStr and cStr +
     *         [Side Effect] sets memoCheck to refer to table
     */
    public static Set<String> bottomUpLCS (String rStr, String cStr) {
        memoCheck = new int[rStr.length() + 1][cStr.length() + 1];
        LCS_LENGTH = bottomUpTableFill(rStr, cStr, memoCheck);
    	return collectSolution(rStr, rStr.length(), cStr, cStr.length(), memoCheck);
    }
     
    /**
    * Completes the memoization table using bottom-up dynamic programming
    * @param rStr The String along the memoization table's rows
    * @param cStr The String along the memoization table's cols
    * @param table The table containing optimal solutions
    */
    public static int bottomUpTableFill(String rStr, String cStr, int[][] table) {    	
    	for (int r = 0; r <= rStr.length(); r++) {
            for (int c = 0; c <= cStr.length(); c++) {
            	if (r == 0 || c == 0) {
            		table[r][c] = 0;
            	} else if (rStr.charAt(r - 1) == cStr.charAt(c - 1)) {
                    table[r][c] = table[r - 1][c - 1] + 1;
                } else {
                   table[r][c] = Math.max(table[r - 1][c], table[r][c - 1]);
                }
            }
        }
        return table[rStr.length()][cStr.length()];
    }
    
    // -----------------------------------------------
    // Top-Down LCS
    // -----------------------------------------------
    
    /**
     * Top-down dynamic programming approach to the LCS problem, which
     * solves smaller and smaller subproblems recursively using a tabular
     * memoization structure.
     * @param rStr The String found along the table's rows
     * @param cStr The String found along the table's cols
     * @return The longest common subsequence between rStr and cStr +
     *         [Side Effect] sets memoCheck to refer to table  
     */
    public static Set<String> topDownLCS (String rStr, String cStr) {
        memoCheck = new int[rStr.length() + 1][cStr.length() + 1];
        LCS_LENGTH = topDownTableFill(rStr, cStr, rStr.length(),  cStr.length(), memoCheck);
    	return collectSolution(rStr, rStr.length(), cStr, cStr.length(), memoCheck);
    }

    /**
    * Completes the memoization table using top-down dynamic programming
    * @param rStr The String along the memoization table's rows
    * @param r The current letter's index in rStr
    * @param cStr The String along the memoization table's cols
    * @param c The current letter's index in cStr
    * @param table The memoization table containing optimal solutions
    */
    public static int topDownTableFill(String rStr, String cStr, int r, int c, int[][] table) {
	    if (table[r][c] <= 0) {
    		if (r == 0 || c == 0) { 
	            return 0;
	        }
  
	        if (rStr.charAt(r - 1) == cStr.charAt(c - 1)) {   
	            table[r][c] = topDownTableFill(rStr, cStr, r - 1, c - 1, table) + 1;
	        } else { 
                table[r][c] = Math.max(topDownTableFill(rStr, cStr, r - 1, c, table),
                    topDownTableFill(rStr, cStr, r, c - 1, table));
	        }
        }
        return table[r][c];
    }
}