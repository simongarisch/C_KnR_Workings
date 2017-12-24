#include <stdio.h>

int power(int base, int power); // function prototype

int main(){
  for(int i = 0; i < 10; ++i){
    printf("%d %d %d\n", i, power(2, i), power(-3, i));
  }
  return(0);
}


int power(int base, int power){
  int p = 1;

  for(int i = 1; i <= power; ++i){
    p = p * base;
  }
  return(p);
}

