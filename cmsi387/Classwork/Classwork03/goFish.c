#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int arraySize = 25, numInputs = 0, toAdd;
    double inputs[arraySize];
    char input[10];

    while (1) {
        printf("Enter a number: ");
        toAdd = atof(gets(input));

        if ((int) toAdd == -9999) {
            break;
        } else {
            inputs[numInputs] = toAdd;
            numInputs++;

            if (numInputs >= 25) {
                break;                
            }
        }
    }

    double sum = 0.0;
    int numSevens = 0;
    //char* numStr = "";

    for (int j = 0; j < numInputs; j++) {
    //    sprintf(numStr, "%s%f", numStr, inputs[j]);
        sum += inputs[j];

        if (inputs[j] == 7) {
            numSevens++;
        }
    }

    printf("\navg: %.2f\n", sum / numInputs);
   // printf("%s\n", numStr);
    printf("# sevens: %d\n", numSevens);

    return 0;
}