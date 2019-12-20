package pathfinder.informed;

import org.junit.Test;
import static org.junit.Assert.*;

import java.util.ArrayList;

/**
 * Unit tests for Maze Pathfinder. Tests include completeness and
 * optimality.
 */
public class PathfinderTests {
    @Test
    public void testPathfinder_t0() {
        String[] maze = {
            "XXXXXXX",
            "XI...KX",
            "X.....X",
            "X.X.XGX",
            "XXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        // result will be a 2-tuple (isSolution, cost) where
        // - isSolution = 0 if it is not, 1 if it is
        // - cost = numerical cost of proposed solution
        int[] result = prob.testSolution(solution);
        assertEquals(1, result[0]); // Test that result is a solution
        assertEquals(6, result[1]); // Ensure that the solution is optimal
    }

    @Test
    public void testPathfinder_t1() {
        String[] maze = {
            "XXXXXXX",
            "XI....X",
            "X.MMM.X",
            "X.XKXGX",
            "XXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        int[] result = prob.testSolution(solution);
        assertEquals(1, result[0]);  // Test that result is a solution
        assertEquals(14, result[1]); // Ensure that the solution is optimal
    }

    @Test
    public void testPathfinder_t2() {
        String[] maze = {
            "XXXXXXX",
            "XI.G..X",
            "X.MMMGX",
            "X.XKX.X",
            "XXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        int[] result = prob.testSolution(solution);
        assertEquals(1, result[0]);  // Test that result is a solution
        assertEquals(10, result[1]); // Ensure that the solution is optimal
    }

    @Test
    public void testPathfinder_t3() {
        String[] maze = {
            "XXXXXXX",
            "XI.G..X",
            "X.MXMGX",
            "X.XKX.X",
            "XXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        assertNull(solution); // Ensure that Pathfinder knows when there's no solution
    }

    @Test
    public void testPathfinder_t4() {
        String[] maze = {
            "XXXXXXXXXXXX",
            "XI.G.......X",
            "X.MXM....M.X",
            "XGM.....MKMX",
            "XXXXXXXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        int[] result = prob.testSolution(solution);
        assertEquals(1, result[0]);  // Test that result is a solution
        assertEquals(22, result[1]); // Ensure that the solution is optimal
    }

    @Test
    public void testPathfinder_t5() {
        String[] maze = {
            "XXXXXXXXXXXXXXXXXXXXX",
            "XI..................X",
            "X.MXM....M..........X",
            "X..........M.....M.MX",
            "X.M......M.......M.MX",
            "X.M.....MKM........MX",
            "X.M.....MM.........MX",
            "XGM.....M..........MX",
            "XXXXXXXXXXXXXXXXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        int[] result = prob.testSolution(solution);
        assertEquals(1, result[0]);  // Test that result is a solution
        assertEquals(30, result[1]); // Ensure that the solution is optimal
    }

    @Test
    public void testPathfinder_t6() {
        String[] maze = {
            "XXXXXXXXXXXXXXXXXXXXX",
            "XI................XGX",
            "X.MXM....M........XXX",
            "X..........M.....M.MX",
            "X.M......M.......M.MX",
            "X.M.....MMM........MX",
            "XXX.....MM........KMX",
            "X.X.....M..........MX",
            "XXXXXXXXXXXXXXXXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        assertNull(solution); // Ensure that Pathfinder knows when there's no solution
    }

    @Test
    public void testPathfinder_t7() {
        String[] maze = {
            "XXXXXXXXXXXXXXXXXXXXX",
            "XI..................X",
            "X.MXM....M..........X",
            "X..........M.....M.MX",
            "X.M......MG......MKMX",
            "X.M.....M.M........MX",
            "X.M.....MM.........MX",
            "X.M.....M..........MX",
            "XXXXXXXXXXXXXXXXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        int[] result = prob.testSolution(solution);
        assertEquals(1, result[0]);  // Test that result is a solution
        assertEquals(30, result[1]); // Ensure that the solution is optimal
    }

    @Test
    public void testPathfinder_t8() {
        String[] maze = {
            "XXXXXXXXXXXXXXXXXXXXX",
            "XI....G.............X",
            "XMMXM....M..........X",
            "XM.........M.....M.MX",
            "XMM.............M..MX",
            "XMM.....M.M........MX",
            "XGMMMMK.MM.........MX",
            "X.M.....M..........MX",
            "XXXXXXXXXXXXXXXXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        int[] result = prob.testSolution(solution);
        assertEquals(1, result[0]);  // Test that result is a solution
        assertEquals(15, result[1]); // Ensure that the solution is optimal
    }

    @Test
    public void testPathfinder_t9() {
        String[] maze = {
            "XXXXXXXXXXXXXXXXXXXXX",
            "XI....G........G....X",
            "XMMXM....M..........X",
            "XM..G......M.G...M.MX",
            "XMMG....G....G..M..MX",
            "XMM.....M.M........MX",
            "XGMMMMK.MM..G......MX",
            "X.M.....M........G.MX",
            "XXXXXXXXXXXXXXXXXXXXX"
        };
        MazeProblem prob = new MazeProblem(maze);
        ArrayList<String> solution = Pathfinder.solve(prob);

        int[] result = prob.testSolution(solution);
        assertEquals(1, result[0]);  // Test that result is a solution
        assertEquals(14, result[1]); // Ensure that the solution is optimal
    }
}
