// the function rand() computes a sequence of pseudo-random integers
// in the range zero to RAND_MAX, which is defined in <stdlib.h>
// the function srand(unsigned) sets the seed for rand

#include <stdio.h>
#include <stdlib.h>

int main(){
  int n;
  printf("Random numbers from 0->9 inclusive...\n");
  
  for(int i=0; i<5; i++){ 
    n = rand() % 10;
    printf("%d\n", n);
  }

  return(0);
}
