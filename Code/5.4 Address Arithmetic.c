#include <stdio.h>

#define ALLOCSIZE 10000 // size of available space

// https://stackoverflow.com/questions/572547/what-does-static-mean-in-c
// for some good examples
static char allocbuf[ALLOCSIZE]; // storage for alloc 
static char *allocp = allocbuf;  // next free position

char *alloc(int n); // function prototypes
void afree(char *p);

int main(){
  int n = 10;
  char *p;
  
  p = alloc(n);
  if(p){
    printf("Allocation successful.\n");
  }else{
    printf("Allocation failed!\n");
    return(-1);
  }
  
  afree(p);
  return(0);
}


/*C guarantees that zero is never a valid address
  the symbolic constant NULL is often used in place of zero
  as a mneumonic to indicate more clearly that this is a special 
  value for a pointer. NULL is defined in <stdio.h> */
char *alloc(int n){ // return pointer to n characters
  if(allocbuf + ALLOCSIZE - allocp >= n){
    allocp += n;
    return(allocp - n); // old p
  }else{ // not enough room
    return(0);
  }
}


void afree(char *p){
  if(p>=allocbuf && p<allocbuf+ALLOCSIZE)
    allocp = p;
}

