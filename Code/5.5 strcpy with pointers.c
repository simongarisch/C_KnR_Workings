#include <stdio.h>
#include <string.h> // this will contain strcpy

// function prototypes
void strcpy1(char *s, char *t);
void strcpy2(char *s, char *t);
void strcpy3(char *s, char *t);
void strcpy4(char *s, char *t);

int main(){
  char x[20], y[20];
  strcpy(x, "Some String!");
  strcpy(y, "Another String!");
  printf("x is '%s', y is '%s'\n", x, y);

  // now we'll use versions of strcpy we've written ourselves
  strcpy(y, "strcpy1 test!");
  strcpy1(x, y);
  printf("'%s'\n", x);

  strcpy(y, "strcpy2 test!");
  strcpy2(x, y);
  printf("'%s'\n", x);

  strcpy(y, "strcpy3 test!");
  strcpy3(x, y);
  printf("'%s'\n", x);

  strcpy(y, "strcpy4 test!");
  strcpy4(x, y);
  printf("'%s'\n", x);

  return(0);
}


// the simple first version of strcpy
void strcpy1(char *s, char *t){
  int i=0;
  while((s[i] = t[i]) != '\0')
    i++;
}

// a similar version with pointers
void strcpy2(char *s, char *t){
  while((*s = *t) != '\0'){
    s++;
    t++;
  }
}

// version 3 using post increment operators
void strcpy3(char *s, char *t){
  while((*s++ = *t++) != '\0')
    ;
}

// finally. the comparison against zero is redundant
// this style of syntax will be seen frequently
void strcpy4(char *s, char *t){
  while(*s++ = *t++)
    ;
}


