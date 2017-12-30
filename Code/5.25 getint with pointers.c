#include <stdio.h>
#include <ctype.h>

void getint(int *pn);

int main(){
  int x = 0;
  getint(&x);
  
  printf("x is now %d\n", x);
  return(0);
}

// get next integer from input into *pn
void getint(int *pn){
  int c, sign;

  while(isspace(c = getchar())){
    ; // skip white space
  }

  if(!isdigit(c) && c!=EOF && c!='+' && c!='-'){
    ungetc(c, stdin); // it's not a number
    return;
  }

  sign = (c == '-')? -1 : 1;
  if(c == '+' || c == '-'){
    c = getchar();
  }

  for(*pn=0; isdigit(c); c=getchar()){
    *pn = 10 * *pn + (c - '0');
  }
  *pn *= sign;

  if(c!=EOF){
    ungetc(c, stdin);
  }
}
