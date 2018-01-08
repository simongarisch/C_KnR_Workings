// This is a re-write of 7.5 with error messages
// The program signals errors in two ways
// First, fprintf output goes to stderr, so it finds
// its way to the screen instead of disappearing down a 
// pipeline or into an output file.
// Second, through the use of exit, which terminates the 
// program when called. The argument of exit is available to
// whatever process called this one.
#include <stdio.h>
#include <stdlib.h> // exit() is defined in the stdlib

int main(int argc, char *argv[]){
  FILE *fp;
  void filecopy(FILE *, FILE *);
  char *prog = argv[0]; // program name for errors

  if(argc==1) // no args, copy stdin
    filecopy(stdin, stdout);
  else{
    while(--argc > 0){
      if((fp=fopen(*++argv, "r")) == NULL){
        fprintf(stderr, "%s: can't open %s\n", prog, *argv);
        exit(1);
      }else{
        filecopy(fp, stdout);
        fclose(fp); 
      }
    }
  }

  if(ferror(stdout)){
    fprintf(stderr, "%s, error writing stdout\n", prog);
    exit(2);
  }
  exit(0);
}


// copy file ifp to file ofp
void filecopy(FILE *ifp, FILE *ofp){
  int c;
  while((c=getc(ifp)) != EOF)
    putc(c, ofp);
}
