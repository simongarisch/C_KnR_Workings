// a common convention for C programs on UNIX systems is that an argument
// that begins with a minus sign introduces an optiona flag or parameter.
// -x (for except) to signal the inversion and
// -n (number) to request line numbering
// then find -x -n pattern 
// will print each line taht doesn't match the pattern
// preceeded by it's line number

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline2(char s[], int lim);

int main(int argc, char *argv[]){
  char line[MAXLINE];
  long lineno = 0;
  int c, except = 0, number = 0, found = 0;

  while(--argc > 0 && (*++argv)[0] == '-'){
    while(c = *++argv[0]){
      switch(c){
        case 'x':
          except = 1;
          break;
        case 'n':
          number = 1;
          break;
        default:
          printf("find: illegal option %c\n", c);
          argc = 0;
          found = -1;
          break;
      }
    }
  }

  if(argc != 1){
    printf("Usage: find -x -n pattern\n");
  }else{
    while(getline2(line, MAXLINE) > 0){
      if((strstr(line, *argv) != NULL) != except){
        // strstr(s,t), declared in <string.h> returns a pointer
        // to the first occurrence of the string t in the string s
        // or NULL is there is none
        if(number)
          printf("%ld:", lineno);
        printf("%s", line);
        found++;
      } 
    }
  }

  return(0);
}

// The getline() function is prototyped in the stdio.h header file
// Here we define our own getline2 function
int getline2(char s[], int lim){
  int c, i;
  for(i = 0; (i<lim-1 && (c=getchar())!=EOF && c!='\n'); ++i){
    s[i] = c;
  }
  if(c == '\n'){
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return(i);
}
