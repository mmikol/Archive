#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char * argv[]) {
  char name[25];
  printf( "\nHello, %s!\n\n", gets( name ) );
  exit( 0 );
}
