class TuringMachine:
  def __init__ (self, alphabet, transitions):
    self.__HALT_SYMBOL__ = '^'
    self.__BLANK_SYMBOL__ = '$'
    self.alphabet = alphabet + [self.__BLANK_SYMBOL__]
    self.transitions = transitions
  
  def __load_tape__ (self, string):
    return [self.__BLANK_SYMBOL__] + list(string) + [self.__BLANK_SYMBOL__]

  def __contains_accepted_symbols__ (self, string):
    return all(symbol in self.alphabet for symbol in string)
    
  def simulate (self, string):
    if self.__contains_accepted_symbols__(string):
      tape = self.__load_tape__(string)
      [state, pos] = [0, 1]

      while True:
        if tape[pos] not in self.transitions[state]: break

        transition = self.transitions[state][tape[pos]]
        tape[pos] = transition['replace']
        
        if tape[pos] == self.__HALT_SYMBOL__: return True

        pos += transition['shift']
        state = transition['next']

    return False