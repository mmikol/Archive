#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[]) {
    int arr_size = atoi(argv[1]);
    int * arr = malloc(arr_size * sizeof(int));
    
    for (int i = 0; i < arr_size; i++) {
        arr[i] = (rand() % 100) + 1;
    }
    
    int num_tests = 2;
    float avg_access_time, total_time = 0.0;
    clock_t start, end;
    for (int i = 0; i < num_tests; i++) {
        int start = clock();
        for (int j = 0; j < arr_size; j++) {
            if (j % 4096 == 0) {
                int end = clock();
                float t = ((double) end - start)/CLOCKS_PER_SEC;
                printf("\nArray element accessed: %d . . .\n", arr[j]);
                printf("Time to access: %f seconds\n", t);
                total_time += t;
            }
        }
    }
    
    avg_access_time = (total_time / (arr_size / 4096)) / num_tests;
    
    printf("Total average time: %f\n", avg_access_time);
    
    free(arr);
    
    return 0;

}
