#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "madlib-by-numbers.h"

int main() {
  //Tests for to_digit
  
  assert(to_digit('0') == 0);
  assert(to_digit('1') == 1);
  assert(to_digit('9') == 9);

  //Tests for get_char_count

  assert(get_char_count("this has 17 chars", 0, (char*[]){}) == 17);
  assert(get_char_count("         ", 0, (char*[]){}) == 9);
  assert(get_char_count("01234567", 3, (char*[]) { "four", "five", "six" }) == 16);

  //Tests for madlib_by_numbers
  char* t1[] = { "swim", "brilliant", "git" };
  char* t1_str = madlib_by_numbers("The 1 2 likes to 0 in the 1 moonlight", 3, t1);
  
  assert(strcmp(t1_str, "The brilliant git likes to swim in the brilliant moonlight") == 0);
  
  free(t1_str);

  char* t2[] = { "a", "b", "c", "d", "e", "f", "g" };
  char* t2_str = madlib_by_numbers("01234567", 7, t2);

  assert(strcmp(t2_str, "abcdefg7") == 0);

  free(t2_str);

  char* t3[] = { "waffles", "awesome" };
  char* t3_str = madlib_by_numbers("I like 0 because they are 1", 2, t3);

  assert(strcmp(t3_str, "I like waffles because they are awesome") == 0);

  free(t3_str);

  puts("All tests passed!");

  return 0;
}
