protocol Animal {
  var name: String { get }
  var sound: String { get }
  func speak() -> String 
}

extension Animal {
  func speak() -> String {
    return "\(self.name) says \(self.sound)"
  }
}

class Cow : Animal {
  var name: String
  var sound = "moooo"
  init(name: String) {
      self.name = name
  }
}

class Horse : Animal {
  var name: String
  var sound = "neigh"
  init(name: String) {
    self.name = name
  }
}


class Sheep : Animal {
  var name: String
  var sound = "baaaa"
  init(name: String) {
    self.name = name
  }
}


struct NegativeAmountError : Error {}

func change (_ amount: Int) -> Result<(Int, Int, Int, Int), NegativeAmountError> {
  guard amount >= 0 else {
    return .failure(NegativeAmountError())
  }

  var result = [Int]()
  var remaining = amount

  for denomination in [25, 10, 5, 1] {
    let (quotient, amount) = remaining.quotientAndRemainder(dividingBy: denomination)
    remaining = amount
    result.append(quotient)
  }

  let (quarters, dimes, nickles, pennies) = (result[0], result[1], result[2], result[3])

  return .success((quarters, dimes, nickles, pennies))
}

extension String {
  var stretched: String {
    return self
        .filter{(character) in 
          return !character.isWhitespace 
        }
        .enumerated()
        .map{(index, character) in
          return String(repeating: character, count: index + 1)  
        }
        .joined(separator: "")
  }
}

extension Array {
  func mapThenUnique<T>(mapper: (Element) -> T) -> Set<T> { 
    return Set(self.map{ mapper($0) })
  }
}

func powers(of base: Int, through limit: Int, _ consumer: (Int) -> Void) {
  var power = 1
  while power <= limit {
    consumer(power)
    power *= base
  }
}

struct Sayer {
  let phrase: String
  func and(_ words: String) -> Sayer {
    return Sayer(phrase: "\(self.phrase) \(words)")
  }
}

func say(_ word: String) -> Sayer {
  return Sayer(phrase: word)
}

func twice<T>(_ f: (T) -> T, appliedTo x: T) -> T {
  return f(f(x))
}

func uppercasedFirst(of a: [String], longerThan n: Int) -> String? {
  return a.first(where: { $0.count > n })?.uppercased() ?? nil
}