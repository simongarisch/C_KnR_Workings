#include <stdio.h>

int main(){ // some quick examples with printf
  // we can use %d and %i for int 
  int x=2, y=4;
  printf("x=%d, y=%i\n", x, y);

  // %s for string
  char s[] = "This is a string!";
  printf("Variable s is '%s'\n", s);
  
  // %c for single characters
  char a='t', b='6';
  printf("a='%c', b='%c'\n", a, b);

  // %f for float
  float f=2.23;
  printf("Variable f is %0.2f\n", f);

  // %p for pointer
  float *pf = &f;  
  printf("Pointer to variable f is %p\n", pf);

  return(0);
}
