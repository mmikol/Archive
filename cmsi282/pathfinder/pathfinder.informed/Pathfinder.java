package pathfinder.informed;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Iterator;

/**
 * Maze Pathfinding algorithm that implements a basic, uninformed, breadth-first tree search.
 */
public class Pathfinder {

    /**
     * Given a MazeProblem, which specifies the actions and transitions available in the
     * search, returns a solution to the problem as a sequence of actions that leads from
     * the initial to a goal state.
     *
     * @param problem A MazeProblem that specifies the maze, actions, transitions.
     * @return An ArrayList of Strings representing actions that lead from the initial, to the key,
     * to the goal state, in the format: ["R", "R", "L", ...]
     */
    public static ArrayList<String> solve (MazeProblem problem) {
        if (!problem.keyFound) {
        	SearchTreeNode keyNode = getPath(problem, problem.INITIAL_STATE, problem.KEY_TILES);

        	if (keyNode != null) {
        		SearchTreeNode goalNode = getPath(problem, keyNode.state, problem.GOAL_TILES);

        		if (goalNode != null) {
        			ArrayList<String> path = traceback(keyNode);

        			path.addAll(traceback(goalNode));

        			return path;
        		}
            }
        }
        return null;
    }

    /**
     * Given a problem, state, and set of destinations, will compute the
     * optimal path and return the final node in the path
     *
     * @param the maze to be solved
     * @param the starting state
     * @param a set of possible goals or a key, aka destinations
     * @return a SearchTreeNode that is the final node in the path
     */
    private static SearchTreeNode getPath (MazeProblem problem, MazeState state, HashSet<MazeState> dests) {
        PriorityQueue<SearchTreeNode> frontier = new PriorityQueue<SearchTreeNode>(1, (n1, n2) -> {
        	if (n1.cost < n2.cost) return -1;
        	if (n1.cost > n2.cost) return 1;
        	else return 0;
        });
        HashSet<MazeState> history = new HashSet<MazeState>();
        SearchTreeNode curr = new SearchTreeNode(state, null, null);

        frontier.add(curr);

        while (!frontier.isEmpty()) {

            Iterator<MazeState> value = dests.iterator();

            curr = frontier.poll();

            history.add(curr.state);

            while (value.hasNext()) {

            	MazeState destination = value.next();

                Map<String, MazeState> transitions = problem.getTransitions(curr.state);

                for (Map.Entry<String, MazeState> transition : transitions.entrySet()) {
                    SearchTreeNode neighbor = new SearchTreeNode(transition.getValue(), transition.getKey(), curr);

                    if (!problem.keyFound && problem.isKey(neighbor.state)) {
                        problem.keyFound = true;
                        return neighbor;
                    }

                    if (problem.keyFound && problem.isGoal(neighbor.state)) {
                        return neighbor;
                    }

                    if (!history.contains(neighbor.state)) {
                        neighbor.cost = curr.cost + problem.getCost(neighbor.state) + problem.getManhattanDist(neighbor.state, destination);
                        frontier.add(neighbor);
                    }
                }
            }
        }
        return null;
    }

    /**
    * Returns the path that led to a given node
    *
    * @param the "last" node in a path
    * @return a list of directions that leads to the given node in a maze
    */

	private static ArrayList<String> traceback (SearchTreeNode last) {
	    ArrayList<String> result = new ArrayList<>();

	    for (SearchTreeNode current = last; current.parent != null; current = current.parent) {
	       result.add(current.action);
	    }

	    Collections.reverse(result);

	    return result;
	}
}

/**
 * SearchTreeNode that is used in the Search algorithm to construct the Search
 * tree.
 */
class SearchTreeNode {

    MazeState state;
    String action;
    SearchTreeNode parent;
    int cost;

    /**
     * Constructs a new SearchTreeNode to be used in the Search Tree.
     *
     * @param state The MazeState (row, col) that this node represents.
     * @param action The action that *led to* this state / node.
     * @param parent Reference to parent SearchTreeNode in the Search Tree.
     */
    SearchTreeNode (MazeState state, String action, SearchTreeNode parent) {
        this.state = state;
        this.action = action;
        this.parent = parent;
        this.cost = 0;
    }

}
