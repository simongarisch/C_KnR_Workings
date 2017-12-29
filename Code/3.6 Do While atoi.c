#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main(){
  int n = -1524;
  char s[10];
  itoa(n, s);
  
  printf("The char string representation of %d is %s\n", n, s);
  return(0);
}


void itoa(int n, char s[]){
  int i, sign;
  if((sign = n) < 0)
    n = -n;
  
  i = 0;
  do{
    s[i++] = n % 10 + '0';
  }while((n/=10) > 0);

  if(sign<0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
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
