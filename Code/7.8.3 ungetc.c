// the standard library provides a rather restricted version of ungetch
// that we previously wrote; it is called ungetc
// int ungetc(int c, FILE *fp)
// pushes a character c back onto file fp and returns either c, or EOF
// if there is an error
// The ungetc() function pushes the unsigned character c back onto the 
// given input stream
#include <stdio.h>

int main(){
  ungetc('\n', stdin);  
  ungetc('t', stdin);  
  ungetc('s', stdin);
  ungetc('e', stdin);
  ungetc('t', stdin);
  
  // prints "test\n"
  while(putchar(getchar()) != '\n')
    ;
  
  return(0);
}
