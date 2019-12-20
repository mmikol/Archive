#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "madlib.h"

int main() {
  char* t1 = madlib("The %s %s likes to %s in the moonlight", "brilliant", "git", "swim");  
  
  assert(strcmp(t1, "The brilliant git likes to swim in the moonlight") == 0);
  free(t1);

  char* t2 = madlib("She so %s attacked the %s as it %s", "stylishly", "sauce", "boiled");  

  assert(strcmp(t2, "She so stylishly attacked the sauce as it boiled") == 0);
  free(t2);

  char* t3 = madlib("The %s %s %s hard", "dying", "animal", "fought");  

  assert(strcmp(t3, "The dying animal fought hard") == 0);
  free(t3);

  char* t4 = madlib("%s%s%s", "1", "2", "3");  

  assert(strcmp(t4, "123") == 0);
  free(t4);

  char* t5 = madlib("%s %s", "nice", "person", "runs");  

  assert(strcmp(t5, "nice person") == 0);
  free(t5);

  puts("All tests passed!");

  return 0;
}
