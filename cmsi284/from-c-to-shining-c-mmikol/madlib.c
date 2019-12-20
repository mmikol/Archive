#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* madlib(char* template, char* adjective, char* noun, char* verb) {
    char* result = malloc((strlen(template) + strlen(adjective) + strlen(noun) + strlen(verb)) * sizeof(char) + 1);
  
    if (result) {
        sprintf(result, template, adjective, noun, verb, strlen(result) + 1);
    }

    return result;
}