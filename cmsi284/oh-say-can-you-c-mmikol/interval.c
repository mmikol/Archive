#include <stdio.h>
#include <string.h>
#include <stdlib.h>
  
const int NUMBER_OF_KEYS = 12;

const char* const KEYS[NUMBER_OF_KEYS] = { 
  "C", "C#", "D", "D#", "E", "F", 
  "F#", "G", "G#", "A", "A#", "B"
};

const char* const INTERVALS[NUMBER_OF_KEYS] = { 
  "perfect octave", "minor second", "major second", 
  "minor third", "major third", "perfect fourth", 
  "tritone", "perfect fifth", "minor sixth", 
  "major sixth", "minor seventh", "major seventh"
};

int getDistBetween(char* str1, char* str2) {
  int start = -1, end = -2;

  for (int i = 0; i < NUMBER_OF_KEYS; i++) {
    if (strcmp(str1, KEYS[i]) == 0) {
      start = i;
      for (int j = i; j < 2 * NUMBER_OF_KEYS; j++) {
        if (strcmp(str2, KEYS[j % NUMBER_OF_KEYS]) == 0) {
          end = j;
          break;
        }  
      }  
    }
  }

  if (start == -1) return start;
  else if (end == -2) return end;

  return abs(end - start);
}

int main(int argc, char** argv) {
  if (argc != 3) {
    puts("This program requires exactly two command line arguments.");
    return 1;
  }

  int dist = getDistBetween(argv[1], argv[2]);

  if (dist == -1) {
    printf("No such key: %s\n", argv[1]);
    return -1;
  } else if (dist == -2) {
    printf("No such key: %s\n", argv[2]);
    return -2;
  } 
  
  printf("%s to %s is a %s.\n", argv[1], argv[2], INTERVALS[dist]); 
  
  return 0;
}