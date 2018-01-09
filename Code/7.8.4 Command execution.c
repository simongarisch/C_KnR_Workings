// the function system(char *s) executes the command
// in the character string s
#include <stdlib.h> // need stdlib for function system

int main(){
  char s[] = "date";
  system(s); // 'Wednesday 10 January  06:34:16 AEDT 2018' printed in output
  return(0);
}
