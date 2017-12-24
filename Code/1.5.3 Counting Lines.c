// counting lines is just counting new lines

#include <stdio.h>

int main(){
    
  int c, nl;
  nl = 0;
  while((c = getchar()) != EOF){
    // A character  written between single quotes represents an integer value equal
    // to the numerical value of the character in the machine's character set
    if(c == '\n'){
      ++nl;
    }
  }
  printf("%d\n", nl);

  return(0);
}

