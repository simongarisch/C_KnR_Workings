#include <stdio.h>
#include <string.h>
#define MAXLEN 30

// function prototypes
char *fgets2(char *s, int n, FILE *iop);
int fputs2(char *s, FILE *iop);
int getline2(char *line, int max);


int main(int argc, char *argv[]){
  char line[MAXLEN]; // a character string
  int len;

  while((len = getline2(line, MAXLEN)) != 0)
    fputs2(line, stdout);

  return(0);
}


// get at most n chars from iop
char *fgets2(char *s, int n, FILE *iop){
  register int c;
  register char *cs;
  cs = s;
  
  while(--n>0 && (c=getc(iop))!=EOF){
    if ((*cs++ = c) == '\n')
      break;
  }
  *cs = '\0';
  return((c == EOF && cs == s) ? NULL : s);
}


// put string s on file iop
int fputs2(char *s, FILE *iop){
  int c;
  char *cs = s;
  while(c=*cs++)
    putc(c, iop);
  return(ferror(iop)? EOF : 0);
}


// read a line, return length
int getline2(char *line, int max){
  if(fgets2(line, max, stdin) == NULL)
    return(0);
  else
    return(strlen(line));
}
