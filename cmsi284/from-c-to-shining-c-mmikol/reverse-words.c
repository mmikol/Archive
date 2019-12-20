#include <string.h>

#include "reverse-range-in-place.h"


void reverse_words(char* string) {    
    for (int start = 0, i = start; i <= strlen(string); i++) {
        if (string[i] == '\0' || string[i] == ' ') {
            reverse_range_in_place(string, start, i - 1);
            start = i + 1;
        }
    }
   reverse_range_in_place(string, 0, strlen(string));
}