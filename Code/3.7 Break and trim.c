#include <stdio.h>
#include <string.h>

int trim(char s[]);

int main(){
  char s[50];
  strcpy(s, "Some string  \t\n");
  trim(s);

  printf("The trimmed string is %s.\n", s);
  return(0);
}


// removes trailing blanks, tabs and newlines
int trim(char s[]){
  int n;
  for(n=strlen(s)-1; n>=0; n--){
    if(s[n] != ' ' && s[n] != '\t' && s[n]!='\n'){
      break;
    }
  }

  s[n+1] = '\0';
  return(n);
}
