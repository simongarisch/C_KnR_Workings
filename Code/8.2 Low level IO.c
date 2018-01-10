#include <stdio.h>
#include <unistd.h>
//#include "sys/syscall.h"
// BUFSIZ is also defined in syscalls.h;
// it's value is a good size for the local system

int main(){ // copy input to output
  char buf[BUFSIZ];
  int n;

  while((n=read(0, buf, BUFSIZ)) > 0)
    write(1, buf, n);
  return(0);
}

// a version of getchar that does unbuffered
// input, by reading the standard input one 
// character at a time
int getchar(void){
  char c;
  return((read(0, &c, 1)==1)? (unsigned char)c : EOF);
}
