#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define QUANTUM 40

bool allDone(bool arr[], int size);
int nextThread(int current, bool arr[], int size);

int main( int argc, char *argv[] ) {
    if ( argc % 2 != 1 ) {
        printf("invalid number of arguments");
        return 1;
    }
    int pairs = (argc / 2);
    char* thread_names[100];
    int thread_sizes[100];
    bool thread_done[100];
    for (int i = 0, j = 1; j + 1 < argc; i++, j += 2) {
        thread_names[i] = argv[j];
        thread_sizes[i] = atoi(argv[j + 1]);
        thread_done[i] = false;
    }

    int remaining;
    int current = 0;
    while (!allDone(thread_done, pairs)) {
        remaining = thread_sizes[current] - QUANTUM;
        if (remaining <= 0) {
            printf("%s:%d:%s\n", thread_names[current], thread_sizes[current], "done");
            thread_done[current] = true;
        } else {
            thread_sizes[current] = remaining;
            printf("%s:%d:%d\n", thread_names[current], QUANTUM, remaining);
        }
        current = nextThread(current, thread_done, pairs);
    }
    return 0;
}

bool allDone(bool arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (!arr[i]) {
            return false;
        }
    }
    return true;
}

int nextThread(int current, bool arr[], int size) {
    do {
        current = current + 1;
        if (current == size) {
            current = 0;
        }
    } while (arr[current]);
    return current;    
}