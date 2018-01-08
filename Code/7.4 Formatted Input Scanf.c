// the function scanf is the input analog of printf
// other arguments, each of which must be a pointer, 
// indicate where the corresponding converted input
// should be stored.
#include <stdio.h>

int main(){
  double sum=0, v;
  while(scanf("%lf", &v)==1)
    printf("\t%0.2f\n", sum += v);
  return(0);
}