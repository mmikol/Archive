#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

const int NUMBER_OF_KEYS = 12;

const char* const KEYS[NUMBER_OF_KEYS] = { 
  "C", "C#", "D", "D#", "E", "F", 
  "F#", "G", "G#", "A", "A#", "B"
};

int getKeyIndex(char* str) {
  for (int i = 0; i < NUMBER_OF_KEYS; i++) {
    if (strcmp(str, KEYS[i]) == 0) return i;
  }
  return -1;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    puts("This program requires exactly one command line argument.\n");
    return 1;
  }

  int keyIndex = getKeyIndex(argv[1]);

  if (keyIndex != -1) {
    printf("%s: %s %s %s\n", 
        argv[1], 
        KEYS[keyIndex], 
        KEYS[(keyIndex + 4) % NUMBER_OF_KEYS], 
        KEYS[(keyIndex + 7) % NUMBER_OF_KEYS]);
    printf("%sm: %s %s %s\n", 
        argv[1], 
        KEYS[keyIndex], 
        KEYS[(keyIndex + 3) % NUMBER_OF_KEYS], 
        KEYS[(keyIndex + 7) % NUMBER_OF_KEYS]);
    printf("%s7: %s %s %s %s\n", 
        argv[1], 
        KEYS[keyIndex], 
        KEYS[(keyIndex + 4) % NUMBER_OF_KEYS], 
        KEYS[(keyIndex + 7) % NUMBER_OF_KEYS], 
        KEYS[(keyIndex + 10) % NUMBER_OF_KEYS]);
    printf("%sdim7: %s %s %s %s\n", 
        argv[1], 
        KEYS[keyIndex], 
        KEYS[(keyIndex + 3) % NUMBER_OF_KEYS], 
        KEYS[(keyIndex + 6) % NUMBER_OF_KEYS], 
        KEYS[(keyIndex + 9) % NUMBER_OF_KEYS]);
  } else {
    printf("No such key: %s\n", argv[1]);
    return 1;
  }
  return 0;
}