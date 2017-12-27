#include <stdio.h>

int strlen2(char s[]);

int main(){
  char *s = "Some string!";
  int len = strlen2(s);
  printf("The character string '%s' has length %d", s, len); 
}


int strlen2(char s[]){
  int i = 0;
  while(s[i] != '\0'){
    ++i;
  }
  return(i);
}
