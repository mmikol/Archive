from turing_machine import Turing_Machine

def get_alphabet():
  symbols = input(
      'Input a space-separated list of symbols for the machine alphabet. NOTE: "^" and "$" are reserved and cannot be added.\n->').split(' ')

  print(symbols)

  if not len(symbols) >= 1 or any(s in symbols for s in ['', '$', '^']):
    print('Error! Invalid alphabet. Please try again.\n')
    get_alphabet()

  return symbols

def get_num_states():
  try:
    num_states = input(
        'How many states will the machine contain?\n-> ')

    print(f'"{num_states}"')
    
    if len(num_states.split(' ')) == 1:
      result = int(num_states)
      if result > 0:
        return result
      else:
        raise ValueError('Error! Positive numbers only. Please try again.')
    else:
      raise Exception('Error! Invalid number given. Please try again.')

  except Exception:
    print('Error! Invalid number given. Please try again.\n')
    return get_num_states()

def isValidTransition(transition, curr_state, num_states):  
  four_inputs = len(transition) == 4
  not_empty = '' not in transition
  valid_dir = transition[2].lower() == 'l' or transition[2].lower() == 'r'
  valid_next = int(transition[3]) < num_states and int(transition[3]) >= 0
  halt_and_loop = transition[1] == '^' and transition[3] != curr_state

  if all(c for c in [four_inputs, not_empty, valid_dir, valid_next]):
    if transition[3] != '^':
      return True
    elif halt_and_loop:
      return True
  
  print(f'\n* Four inputs: condition was {"" if four_inputs else "NOT"} met')
  print(f'* No empty inputs: condition was {"" if not_empty else "NOT"} met')
  print(f'* Shift direction is "L"/"l" or "R"/"r": condition was {"" if valid_dir else "NOT"} met')
  print(f'* 0 <= next state < number of states: condition was {"" if valid_next else "NOT"} met\n')
  
  if transition[3] =='^':
    print(f'* If replacing with "^" then next state must be the current state: condition was {"" if halt_and_loop else "NOT"} met\n')

  return False

def get_state_transition(curr_state, num_states, result):
  try:
    print(f"INPUTTING FOR STATE ( {curr_state} )")

    r = result

    while (True):
      transition = input('-> ')

      if transition == '&':
        break

      transition = transition.split(' ')

      print(transition)

      if not isValidTransition(transition, curr_state, num_states):
        raise ValueError('Error! Invalid transition. Please try inputting all transitions again.')

      r[transition[0]] = {
        'replace': transition[1],
        'shift': 1 if transition[2].lower() == 'r' else -1,
        'next': int(transition[3])
      }

    return r

  except Exception:
    print('\nError! Invalid transition. Please try again!\n')
    return get_state_transition(curr_state, num_states, r)

def get_transitions(num_states):
  print(
  '''
    Define a transition function for each state. Each transition is a space separated list.

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
  '''
  )

  result = []
  
  for i in range(num_states):
    transition = get_state_transition(i, num_states, {})
    
    print(transition)

    result.append(transition)

  return result

def collect_inputs():
  alphabet = get_alphabet()
  num_states = get_num_states()
  transitions = get_transitions(num_states)

  return {
    'alphabet': alphabet, 
    'transitions': transitions
  }

def getTestString():
  print('\CREATE NEW MACHINE: "+" QUIT: "-"')
  return input('What string do you wish to test in the Turing Machine?\n-> ')

def isDesiredInput(inputs):
  try:
    print(f'\n The following machine has been created: \n{inputs}\n')
    
    isDesired = input('Is this correct? (Y/N)\n-> ').lower()

    if isDesired == 'y':
      return True
    elif isDesired == 'n':
      return False

    raise Exception('Error! Invalid input. Please try again!')

  except Exception:
    return None

def init():
  try:
    inputs = collect_inputs()
        
    if (isDesiredInput(inputs)):
      tm = Turing_Machine(inputs['alphabet'], inputs['transitions'])

      while True:
        input_string = getTestString()
        
        if input_string == '+':
          break
        elif input_string == '-':
          print('Thanks for using!')
          return

        isAccepted = tm.simulate(input_string)
        print(f'\nRESULT: The string, "{input_string}" is {"" if isAccepted else "not"} accepted by the defined Turing Machine.')

  except Exception:
    print('Oops! An error must have occurred. Please try creating a new machine.')

init()
