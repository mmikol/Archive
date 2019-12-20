#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Method returns a given character as an int between 0 ~ 9 if possible
 * 
 * @param c is an integer typed as a character 
 * @return an ASCII encoded int where the subtraction of the char and '0' produces 
 * the correct mapping (i.e. ASCII value of integer 6 is 6; '6' = 54, '0' = 48; 54 - 48 == 6))
 * 
*/
int to_digit(char c) {
    if (!(c >= '0' && c <= '9')) {
        puts("Character given is not a convertible number.");
        exit(EXIT_FAILURE);
    }
    return c - '0';
}

/*
 * Method returns the total amount of characters in a string, exluding '/0'
 * 
 * @param template is the madlib template
 * @param word_count is the number of possible words to choose for substitution of numbers 
 * @param words[] is an array of possible words for substition of numbers
 * 
*/
int get_char_count(char* template, int word_count, char* words[]) {
    int c = 0;
    for (int i = 0; i < strlen(template); i++) {
        if (isdigit(template[i]) && to_digit(template[i]) < word_count) {
            int word_index = to_digit(template[i]);
            c += strlen(words[word_index]);
        } else {
            c++;
        }
    }
    return c;
}

char* madlib_by_numbers(char* template, int word_count, char* words[]) {
    char* result = (char*) malloc((get_char_count(template, word_count, words) * sizeof(char)) + 1);

    if (result) {
        for (int i = 0; i < strlen(template); i++) {
            if (isdigit(template[i]) && to_digit(template[i]) < word_count) {
                strcat(result, words[to_digit(template[i])]);
            } else {
                strcat(result, (char[]) { template[i], '\0' });
            }
        }
    }
    
    return result;
}