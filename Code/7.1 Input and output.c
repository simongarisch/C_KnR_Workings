// Many programs read only one input stream and write only one output
// stream; for such programs, input and output wit getchar, putchar, and
// printf may be entirely adequate, and is certainly enough to get started
#include <stdio.h>
#include <ctype.h> // defines tolower()

int main(){
  int c;
  while((c = getchar()) != EOF)
    putchar(tolower(c));
  return(0);
}



