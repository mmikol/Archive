  #include <stdio.h>

  int main( int argc, char * argv[] ) {
     char* indicator;
     int numOdd = 0, numEven = 0;

     for (int i = -10; i <= 10; i++) {
       if (i % 2 == 0) {
         indicator = "EVEN";
         numEven++;
       } else {
         indicator = "ODD";
         numOdd++;
       }
       printf("%d\t%d\t%s\n", i, i * i, indicator);
     }

     printf("# odd numbers = %d\n", numOdd);
     printf("# even numbers = %d\n", numEven);
     
     return 0;
  }
