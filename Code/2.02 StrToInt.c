#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int atoi2(char s[]);

int main(){
  char s[20];
  strcpy(s, "42");
  printf("Converting %s to int is %d\n", s, atoi2(s));
  return(0);
}


int atoi2(char s[]){
  int i, n;
  n = 0;
  for(i=0; s[i]>='0' && s[i] <= '9'; ++i){
    n = 10 * n + (s[i] - '0');
  }
  return(n);
}
