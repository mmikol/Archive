#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//TODO: Expand to return more than seconds
int getTime()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_sec;
    printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int main(int argc, char *argv[])
{
    int begin = getTime();
    int arrsize = atoi(argv[1]);
    int *arr = malloc(arrsize * sizeof(int));

    for (int i = 0; i < arrsize; i++)
    {
        arr[i] = (rand() % 100) + 1;
    }

    printf("\nArray filled . . .\n");

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < arrsize; j++)
        {
            if (j % 4096 == 0)
            {
                printf("\nArray element accessed: %d . . .\n", arr[j]);
            }
        }
    }

    free(arr);

    int end = getTime();
    printf("Total time: %d seconds", end - begin);
    return 0;
}
