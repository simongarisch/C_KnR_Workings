#include <stdio.h>
#include <string.h>

int strlen2(char *s);

int main(){
  char s[20];
  strcpy(s, "Some string!");
  
  int n = strlen2(s);
  printf("The length of string '%s' is %d\n", s, n);
  return(0);
}


int strlen2(char *s){
  int n;
  for(n=0; *s!='\0'; s++)
    n++;
  return(n);
}
