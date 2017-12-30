// Since C passes arguments to functions by value, 
// there is no direct way for the called function to alter
// a variable in the calling function
// Pointer arguments enable a function to access and change
// objects in the function that called it

#include <stdio.h>

void swap(int *px, int *py);

int main(){
  int x = 7, y = 9;
  printf("Starting with x=%d, y=%d\n", x, y);
  int *px = &x;
  int *py = &y;

  swap(px, py);
  printf("After swap we have x=%d, y=%d\n", x, y);
  return(0);
}


void swap(int *px, int *py){
  int temp;
  temp = *px;
  *px = *py;
  *py = temp;
}
