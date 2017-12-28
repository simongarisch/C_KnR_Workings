#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main(){
  char s[20];
  strcpy(s, "Hello World!");
  reverse(s);
  printf("%s\n", s);
  return(0);
}

void reverse(char s[]){
  int c, i, j;
  // the comma often finds use in the for statement
  for(i=0, j=strlen(s)-1; i<j; i++, j--){
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

