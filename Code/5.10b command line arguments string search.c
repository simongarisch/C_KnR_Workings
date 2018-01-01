#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline2(char s[], int lim);

int main(int argc, char *argv[]){
  char line[MAXLINE];
  int found = 0;
  
  if(argc != 2){
    printf("Usage: find pattern\n");
  }else{
    while(getline2(line, MAXLINE) > 0){
      if(strstr(line, argv[1]) != NULL){
        // strstr(s,t), declared in <string.h> returns a pointer
        // to the first occurrence of the string t in the string s
        // or NULL is there is none
        printf("%s", line);
        found++;
      } 
    }
  }
  return(found);
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
