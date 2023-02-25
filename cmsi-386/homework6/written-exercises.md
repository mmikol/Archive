# Homework 6

Miliano Mikol  
CMSI 386  
15 December 2020  

### Problem 1  
```cpp
#include <iostream>

using namespace std;

int main() {
  struct {
    int n;
    char c;
  } A[9][9]

  cout << &(A[0][0]) << '\n'; // 0x7ffeed66d760
  cout << &(A[3][7]) << '\n'; // 0x7ffeed66d870
}
```
This is a declaration of an array of structs. Arrays are reserved, contiguous, byte-sized spaces in memory according to C++ alignment rules. There are 34 possible indices to access between A[0][0] and A[3][7]. Thus, the addresses follow from simple math (in pseudo-ish code):
```
toDecimal[(0x7ffeed66d870 - 0x7ffeed66d760) / 0x8] == 34 // Number of 8-bit slots required
```

### Problem 2  

```golang
a [n]*float64
b *[n]float64
c func()*[n]float64 
d [n]func()float64
f func(func(int, []int) int, int) func(...int) float64
```

### Problem 3  
(a) Static scope: f() * h() - x = 1 * 1 - 1 -> **output: 0**  

(b) Dynamic scope: f() * h() - x = 1 * 3 - 1 -> **output: 2**

### Problem 4  
(a) Deep binding: x = 5; x + 3 = 5 + 3 -> **output: 8**

(b) Shallow binding: x = 2;  x + 3 = 2 + 3 -> **output: 5**  

### Problem 5  
(a) Pass by value -> **output: 1, 2, 3, 4**  

(b) Pass by reference -> **output: 2, 2, 3, 4**  

(c) Pass by value-result ->  **output: 2, 2, 4, 4**  

(d) Pass by name -> **output: 2, 2, 3, 3**  

### Problem 6  

```javascript
function isPrime(n) { 
  return isNaN(n) || !Number.isInteger(n) ?
      new Error('Not an integer') 
    : n < 2 || n > Number.MAX_SAFE_INTEGER ?
      new Error('Number too big or too small')
    : n === 2 || n === 3 ?
      true
    : n % 2 === 0 || n % 3 === 0 ?
      false 
    : (function notComposite(k, w) {
        if (k * k > n) return true
        if (n % k === 0) return false
        return notComposite(k + w, 6 - w)
  })(5, 2)
}

```
### Problem 7  
The billion dollar mistake is Java's inclusion of the null reference as a member of all reference types. Unlike Java, Python avoids the distinction between primitives and references; everything is an object, and every object has a type. This includes the None object which is of the NoneType. Because of this distinction, the NullPointerException cannot be an issue for Python. 

### Problem 8  

```golang
func powers(base int, limit int, channel chan <- int) {
  for power := 1; power < limit; power *= base {
    channel <- power
  }
}
```