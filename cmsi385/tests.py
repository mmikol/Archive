from turing_machine import TuringMachine as TM
from random import randint, sample

def t1():
  t_alphabet = ['a', 'b']
  t_transitions = (
    {
      'a': {
        'replace': 'x', 
        'shift': 1,
        'next': 1
      },
      'y': {
        'replace': 'y',
        'shift': 1,
        'next': 4
      },
      '$': {
        'replace': '^',
        'shift': 1,
        'next': 0
      }
    },
    {
      'a': {
        'replace': 'a',
        'shift': 1,
        'next': 1
      },
      'y': {
        'replace': 'y', 
        'shift': 1, 
        'next': 1
      },
      'b': {
        'replace': 'y',
        'shift': 1, 
        'next': 2
      }
    },
    {
      'b': {
        'replace': 'y',
        'shift': -1, 
        'next': 3
      }
    },
    {
      'y': {
        'replace': 'y',
        'shift': -1,
        'next': 3
      },
      'a': {
        'replace': 'a',
        'shift': -1,
        'next': 3
      },
      'x': {
        'replace': 'x',
        'shift': 1,
        'next': 0
      },
    },
    {
      'y': {
        'replace': 'y',
        'shift': 1,
        'next': 4
      },
      '$': {
        'replace': '^',
        'shift': 1,
        'next': 5
      }
    }
  )

  # this machine accepts { a^nb^2n where n >= 0}
  t_tm = TM(t_alphabet, t_transitions)

  # accept cases
  for i in range(50):
    num_letters = randint(1, 100)
    t_str = 'a' * num_letters + 'b' * 2 * num_letters
    assert t_tm.simulate(t_str)

  # reject cases
  assert not t_tm.simulate('xyabnm')
  assert not t_tm.simulate('aab')
  assert not t_tm.simulate('aaabbb')
  assert not t_tm.simulate('ba')
  assert not t_tm.simulate('aba')
  assert not t_tm.simulate('ababb')

  print('Test 1 passed!')
  return True

def t2():
  t_alphabet = ['0', '1']
  t_transitions = (
    {
      '0': {
        'replace': 'x',
        'shift': 1,
        'next': 1
      },
      'y': {
        'replace': 'y',
        'shift': 1,
        'next': 3
      },
      '1': {
        'replace': 'y',
        'shift': 1,
        'next': 3
      },
      '$': {
        'replace': '^',
        'shift': 1,
        'next': 0
      }
    }, 
    {
      '0': {
        'replace': '0',
        'shift': 1,
        'next': 1
      }, 
      'y': {
        'replace': 'y',
        'shift': 1,
        'next': 1
      },
      '1': {
        'replace': 'y',
        'shift': -1,
        'next': 2
      }
    },
    {
      '0': {
        'replace': '0',
        'shift': -1,
        'next': 2
      },
      'y': {
        'replace': 'y',
        'shift': -1,
        'next': 2
      },
      'x': {
        'replace': 'x',
        'shift': 1,
        'next': 0
      }
    },
    {
      'x': {
        'replace': 'x',
        'shift': 1,
        'next': 3
      },
      'y': {
        'replace': 'y',
        'shift': 1,
        'next': 3
      },
      '1': {
        'replace': 'y',
        'shift': 1,
        'next': 3
      },
      '$': {
        'replace': '^',
        'shift': 1,
        'next': 4
      }
    }
  )

  # this machine accepts { 0^n1^n1^* }
  t_tm = TM(t_alphabet, t_transitions)

  # accept cases
  for i in range(50):
    t_str = '0' * i + '1' * i
    assert t_tm.simulate(t_str)
  
  for i in range(50):
    num_letters = randint(1, 100)
    t_str = '0' * num_letters + '1' * num_letters + '1' * randint(1, 100)
    assert t_tm.simulate(t_str)

  # reject cases
  assert not t_tm.simulate('001')
  assert not t_tm.simulate('10')
  assert not t_tm.simulate('101')
  assert not t_tm.simulate('01011')

  print('Test 2 passed!')
  return True

def t3():
  t_alphabet = ['0', '1']
  t_transitions = (
    {
      '$': {
        'replace': '^',
        'shift': 1,
        'next': 0
      },
      'y': {
        'replace': 'y',
        'shift': 1,
        'next': 0
      },
      '1': {
        'replace': 'x',
        'shift': 1,
        'next': 1
      },
      '0': {
        'replace': 'x',
        'shift': 1,
        'next': 2
      }
    },
    {
      '0': {
        'replace': 'y',
        'shift': -1,
        'next': 3
      },
      'y': {
        'replace': 'y',
        'shift': 1,
        'next': 1
      },
      '1': {
        'replace': '1',
        'shift': 1,
        'next': 1
      },
      'x': {
        'replace': 'x',
        'shift': 1,
        'next': 0
      }
    },
    {
      '0': {
        'replace': '0',
        'shift': 1,
        'next': 2
      },
      'y': {
        'replace': 'y',
        'shift': 1,
        'next': 2
      },
      '1': {
        'replace': 'y',
        'shift': -1,
        'next': 4
      }
    },
    {
      '0': {
        'replace': '0',
        'shift': -1,
        'next': 3
      },
      '1': {
        'replace': '1',
        'shift': -1,
        'next': 3
      },
      'y': {
        'replace': 'y',
        'shift': -1,
        'next': 3
      },
      'x': {
        'replace': 'x',
        'shift': 1,
        'next': 0
      }
    },
    {
      'y': {
        'replace': 'y',
        'shift': -1,
        'next': 4
      },
      '0': {
        'replace': '0',
        'shift': -1,
        'next': 4
      },
      '1': {
        'replace': '1',
        'shift': -1,
        'next': 4
      },
      'x': {
        'replace': 'x',
        'shift': 1,
        'next': 0
      }
    }
  )

  # this machine accepts { #(0) == #(1) where |0|, |1| >= 0 }
  t_tm = TM(t_alphabet, t_transitions)

  # accept cases
  for i in range(50):
    num_letters = randint(0, 100)
    t_str = '0' * num_letters + '1' * num_letters
    assert t_tm.simulate(t_str)

  for i in range(50):	
    num_letters = randint(0, 100)
    t_str = '0' * num_letters + '1' * num_letters
    t_str = ''.join(sample(t_str, len(t_str)))
    assert t_tm.simulate(t_str)

  # reject cases
  assert not t_tm.simulate('011')
  assert not t_tm.simulate('100')
  assert not t_tm.simulate('101')
  assert not t_tm.simulate('010')
  assert not t_tm.simulate('0')
  assert not t_tm.simulate('1')

  print('Test 3 passed!')
  return True

def init():
  if all(t() for t in [t1, t2, t3]):
    print('All tests passed!')
  return

init()