#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "reverse-words.h"

#define MAX_TEST_STRING_LENGTH 30

int main() {  
  char* t1 = "Hello, my friends!";
  char test_string[MAX_TEST_STRING_LENGTH];
  
  strncpy(test_string, t1, MAX_TEST_STRING_LENGTH);

  reverse_words(test_string);
  assert(strcmp(test_string, "friends! my Hello,") == 0);
  reverse_words(test_string);
  assert(strcmp(test_string, t1) == 0);

  char* t2 = "i love programming very much";

  strncpy(test_string, t2, MAX_TEST_STRING_LENGTH);

  reverse_words(test_string);
  assert(strcmp(test_string, "much very programming love i") == 0);
  
  char* t3 = "   a  b  c   ";

  strncpy(test_string, t3, MAX_TEST_STRING_LENGTH);

  reverse_words(test_string);
  assert(strcmp(test_string, "   c  b  a   ") == 0);

  char* t4 = " a  b  c   ";

  strncpy(test_string, t4, MAX_TEST_STRING_LENGTH);

  reverse_words(test_string);
  assert(strcmp(test_string, "   c  b  a ") == 0);

  char* t5 = "A1";

  strncpy(test_string, t5, MAX_TEST_STRING_LENGTH);
  
  reverse_words(test_string);
  assert(strcmp(test_string, "A1") == 0);

  char* t6 = "reversed is string this";

  strncpy(test_string, t6, MAX_TEST_STRING_LENGTH);

  reverse_words(test_string);

  assert(strcmp(test_string, "this string is reversed") == 0);

  puts("All tests passed!");

  return 0;
}
