#include <stdio.h>

int main(){
  int x = 1, y = 2, z[10];
  printf("Starting with x=%d, y=%d\n", x, y);
  int *ip;    // ip is a pointer to int
  ip = &x;    // ip = address of x, ip now points to x
  y = *ip;    // y is now 1 too. * is the dereferencing operator
  *ip = 0;    // x is now zero
  ip = &z[0]; // ip now points to z[0]
  
  printf("Ends with x=%d, y=%d\n", x, y);
  return(0);
}
