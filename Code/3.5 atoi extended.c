#include <stdio.h>
#include <ctype.h>

int atoi2(char s[]); // function prototype

int main(){
  char *s = " +777"; // number with leading white space and + sign
  int i = atoi2(s);
  printf("The int representation of '%s' is %d\n", s, i);
  return(0);
}

int atoi2(char s[]){
  int i, n, sign;
  
  for(i=0; isspace(s[i]); i++)
    ;    // skip leading white space
  sign = (s[i] == '-')? -1: 1;

  if(s[i] == '+' || s[i] == '-')
    i++; // skip these as we already have the sign

  for(n=0; isdigit(s[i]); i++)
    n = 10 * n + (s[i] - '0');
  return(sign * n);
}
