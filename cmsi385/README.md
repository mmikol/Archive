# CMSI386 Final Project
Author: Miliano Mikol  
Semester: Fall 2019

## Universal Turing Machine Simulator
This program is implemented in Python 3.8.0 and is run through Command Line. 
* main.py runs a program that allows a user to create a Turing Machine.
* test.py runs a series of tests to prove that the program's implementation works.

### Instructions
The program will direct the user throughout the process of inputs, however, the following describes how the inputs work.

**1) Input an alphabet**  
Separate symbols by spaces.

**2) Input the number of states in the Turing Machine**  
Note that the number of states = ( number_of_nodes ) - ( number_of_accepts ). Accept states are recognized by the reserved replacement symbol "^".

**3) Input transitions for each state in the Turing Machine**  
State (0) is assumed to be the initial state. Inputs are accepted in the following order:
< read_symbol > < replace_symbol > < shift_direction > < next_state >

* < read_symbol > defines what symbol is read on the tape (the current position in the given string).
* < replace_symbol > defines what symbol will be written to the tape at the position of the current read_symbol.
* < shift_direction > defines what direction the tape will be shifted. "R"/"r" = right shift and "L"/"l" = left shift.
* < next_state > defines what state the Turing Machine will enter upon reflecting the aforementioned actions.

**4) Confirm that the defined Turing Machine is correct to the User's liking**  
Indicated by a "Y"/"y" (yes) or "N"/"n" (no).

**5) Input a string for the Turing Machine to evaluate**
The program will run the defined Turing Machine and return whether the string is accepted. Once the program returns a result, the user may do one of three functions:
* Evaluate another string simply by entering the new string.
* Define a new Turing Machine for testing by entering "+".
* Quit the program by entering "-"

Instructions for defining a transition, as given by the program, are shown as follows:

    ***********
    HOWTO
    ***********
    INPUT ORDER: <read_symbol> <replace_symbol> <shift_direction> <next_state>
    FINISHED DEFINING A TRANSITION: "Enter" key on keyboard
    FINISHED DEFINING ALL TRANSITIONS FOR CURRENT STATE: "&"
    DEFINING A TERMINATING TRANSITION: <read_symbol> "^" <shift_direction> current_state_number

    ***********
    DICTIONARY
    ***********
    ACCEPT/TERMINATING SYMBOL: "^"
    BLANK SYMBOL: "$"
    RIGHT SHIFT: "R" or "r"
    LEFT SHIFT: "L" or "l"

    ***********
    TRANSITIONS
    ***********
    To prevent errors, ensure the following conditions are met for each transition:
      * No empty inputs
      * At most four inputs
      * If <replace_symbol> == '^' then <next_state> == current state
      * <shift_direction> == 'R'/'r' or 'L'/'l'
      * 0 <= <next_state> < number of states

### Reserved Symbol Dictionary  
The following symbols should be used for the defined purposes only.

**Turing Machine Inputs**  
* "$" defines a blank space in a string.
* "^" defines a halt symbol for the Turing Machine.

**Program Inputs**  
* "&" defines the completion of a transition definition.
* "+" defines a call to create a new Turing Machine after evaluating a string.
* "-" defines a call to quit the program after evaluating a string.

### A Note on Accept States
When inputting transitions for a state in the Turing Machine, the user is, in actually, creating edges in a graph of nodes (states). Accept states are defined by the following convention:

* < read_symbol > = any symbol considered to signal a "finish" to the Turing Machine's process.
* < replace_symbol > = "^" (halt symbol).
* < shift_direction > = any direction of preference to the user.
* < next_state > = the current state that is being defined (shown by the program). Think of this as a looping edge to the current state.

### Demo
This is an example of a Turing Machine that accepts { aba<sup>*</sup> }

    INIT

    (input alphabet)

    -> a b

    (input num_states)

    -> 3

    (input transitions)

    state ( 0 )
    -> a a r 1
    -> &

    state ( 1 )
    -> b b r 2
    -> &

    state ( 2 )
    -> a a r 2
    -> $ ^ r 2
    -> &

    (confirm machine)

    -> y

    (input test string)

    -> abaaaa

    (exit, create a new machine, or test a new string)

    -> -

    EXIT