package csp;

import java.time.LocalDate;
import java.util.HashSet;
import java.util.Set;
import java.util.ArrayList;
import java.util.List;

/**
 * CSP: Calendar Satisfaction Problem Solver Provides a solution for scheduling
 * some n meetings in a given period of time and according to some unary and
 * binary constraints on the dates of each meeting.
 */
public class CSP {

	/**
	 * Public interface for the CSP solver in which the number of meetings, range of
	 * allowable dates for each meeting, and constraints on meeting times are
	 * specified.
	 * 
	 * @param nMeetings   The number of meetings that must be scheduled, indexed
	 *                    from 0 to n-1
	 * @param rangeStart  The start date (inclusive) of the domains of each of the n
	 *                    meeting-variables
	 * @param rangeEnd    The end date (inclusive) of the domains of each of the n
	 *                    meeting-variables
	 * @param constraints Date constraints on the meeting times (unary and binary
	 *                    for this assignment)
	 * @return A list of dates that satisfies each of the constraints for each of
	 *         the n meetings, indexed by the variable they satisfy, or null if no
	 *         solution exists.
	 */
	public static List<LocalDate> solve(int nMeetings, LocalDate rangeStart, LocalDate rangeEnd, Set<DateConstraint> constraints) {
		Set<LocalDate> initialDomain = getInitialDomain(rangeStart, rangeEnd);
		List<DateVar> variables = generateVariables(nMeetings, initialDomain, constraints);
		List<LocalDate> assignments = new ArrayList<>();
		
		for (int i = 0; i < nMeetings; i++) {
			assignments.add(null);
		}
		
		return recursiveBacktracker(assignments, variables, 0, nMeetings, constraints);
	}
	
	/**
	 * 
	 * @param nMeetings
	 * @param assignments
	 * @param variables
	 * @param constraints
	 * @return
	 */
	private static List<LocalDate> recursiveBacktracker(List<LocalDate> assignments, List<DateVar> variables, int i, int nMeetings, Set<DateConstraint> constraints) {
		DateVar var = selectUnassignedVariable(assignments, variables);

		if (var == null) {
			return assignments;
		}

		for (LocalDate d : var.domain) {
			assignments.add(i, d);

			if (valueIsConsistent(assignments, constraints)) {
				List<LocalDate> result = recursiveBacktracker(assignments, variables, i + 1, nMeetings, constraints);
				
				if (result != null) {
					return result;
				}
			}
			
			assignments.remove(i);
		}
		
		return null;
	}
	
	/*
	 * ----------------------------
	 * HELPER METHODS
	 * ----------------------------
	 */
	
	/**
	 * 
	 * @param rangeStart
	 * @param rangeEnd
	 * @return
	 */
	private static Set<LocalDate> getInitialDomain(LocalDate rangeStart, LocalDate rangeEnd) {
		Set<LocalDate> domain = new HashSet<>();
		
		for (LocalDate curr = rangeStart; !curr.isAfter(rangeEnd); curr = curr.plusDays(1)) {
			domain.add(curr);
		}
		
		return domain;
	}

	/**
	 * generates nodes preprocessing included
	 * @param nMeetings
	 * @param initialDomain
	 * @param constraints
	 * @return
	 */
	private static List<DateVar> generateVariables(int nMeetings, Set<LocalDate> initialDomain, Set<DateConstraint> constraints) {
		List<DateVar> variables = new ArrayList<>(nMeetings);
		
		for (int i = 0; i < nMeetings; i++) {
			Set<LocalDate> temp = initialDomain;
			
			filterDomain(i, temp, initialDomain, constraints);
			
			variables.add(i, new DateVar(temp));
		}
		
		return variables;
	}
	
	/**
	 * preprocessing helper
	 * @param varIndex
	 * @param newDomain
	 * @param initialDomain
	 * @param constraints
	 */
	private static void filterDomain(int varIndex, Set<LocalDate> newDomain, Set<LocalDate> initialDomain, Set<DateConstraint> constraints) {
		for (DateConstraint c : constraints) {
			if (c.arity() == 1 && c.L_VAL == varIndex) {
				LocalDate right = ((UnaryDateConstraint) c).R_VAL;

				if (initialDomain.contains(right)) {
					switch (c.OP) {
					case "==":
						newDomain.clear();
						newDomain.add(right);
						break;
					case "!=":
						newDomain.remove(right);
						break;
					case ">":
						newDomain.removeIf(date -> {
							return date.isBefore(right) || date.isEqual(right);
						});
						break;
					case "<":
						newDomain.removeIf(date -> {
							return date.isAfter(right) || date.isEqual(right);
						});
						break;
					case ">=":
						newDomain.removeIf(date -> {
							return date.isBefore(right);
						});
						break;
					case "<=":
						newDomain.removeIf(date -> {
							return date.isAfter(right);
						});
						break;
					}	
				}
			}
		}
		return;
	}
	
	/**
	 * 
	 * @param assignments
	 * @param variables
	 * @return
	 */
	private static DateVar selectUnassignedVariable(List<LocalDate> assignments, List<DateVar> variables) {
		DateVar min = null;
		
		for (int i = 0; i < variables.size(); i++) {
			if (assignments.get(i) == null && min == null) {
				min = variables.get(i);
			}
			
			if (assignments.get(i) == null && variables.get(i).domain.size() < min.domain.size()) {
				min = variables.get(i);
			}			
		}

		return min;
	}
	
	/**
	 * 
	 * @param assignments
	 * @param constraints
	 * @return
	 */
	private static boolean valueIsConsistent(List<LocalDate> assignments, Set<DateConstraint> constraints) {		
		LocalDate left = null, right = null;
		
		for (DateConstraint c : constraints) {
			if (c.L_VAL < assignments.size()) {
				left = assignments.get(c.L_VAL);
				
				if (c.arity() == 1) {
					right = ((UnaryDateConstraint) c).R_VAL;					
				} else if (c.arity() == 2) {
					if (((BinaryDateConstraint) c).R_VAL < assignments.size()) {
						right = assignments.get(((BinaryDateConstraint) c).R_VAL);						
					}
				}
				
				if (left != null && right != null) {
					if (!testConstraint(c.OP, left, right)) {
						return false;
					}	
				}
			}
		}
		return true;
	}
	
	/**
	 * 
	 * @param constraint
	 * @param left
	 * @param right
	 * @return
	 */
	private static boolean testConstraint(String operator, LocalDate left, LocalDate right) {
		switch (operator) {
		case "==":
			return left.isEqual(right);
		case "!=":
			return !left.isEqual(right);
		case ">":
			return left.isAfter(right);
		case "<":
			return left.isBefore(right);
		case ">=":
			return left.isAfter(right) || left.isEqual(right);
		case "<=":
			return left.isBefore(right) || left.isEqual(right);
		default:
			break;
		}
		// this condition should never be reached since operator is a parameter
		return false;
	}
	
	/**
	 * 
	 * 
	 *
	 */
	private static class DateVar {
		public Set<LocalDate> domain;
		
		public DateVar (Set<LocalDate> initialDomain) {
			domain = initialDomain;
		}		
	}
}