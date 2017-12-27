// Because external variables are globally accessible, 
// they can be used instead of argument lists to communicate data
// between functions

// An external variable must be defined,
// exactly once, outside of any function;
// this sets aside storage for it. The variable must also be
// declared in each function that wants to access it; this states the type of the variable

#include <stdio.h>

#define MAXLINE 1000

int max;
char line[MAXLINE];
char longest[MAXLINE];

int getline2(void); // function prototypes
void copy(void);

// print the longest line
int main(){
  int len;
  extern int max;
  extern char longest[];

  max = 0;
  while((len = getline2()) > 0){
    if(len > max){
      max = len;
      copy();
    }
  }
  if(max > 0){
    printf("%s", longest);
  }
  return(0);
}


int getline2(void){
  int c, i;
  extern char line[];
  for(i=0; i<MAXLINE-1 && (c=getchar())!=EOF && c!='\n'; ++i){
    line[i] = c;
  }
  if(c=='\n'){
    line[i] = c;
    ++i;
  }
  line[i] = '\0';
  return(i);
}


void copy(void){
  int i = 0;
  extern char line[], longest[];
  while((longest[i] = line[i]) != '\0'){
    ++i;
  }
}
