// In C, all arguments are passed by value
#include <stdio.h>

int func(int i); // function prototype

int main(){
  int i = 3;
  printf("In C, all arguments are passed by value\n");
  printf("i before function call %d\n", i);
  func(i);
  printf("i after function call %d\n", i);
}


int func(int i){
  ++i;
  printf("i at the end of func %d\n", i);
}

