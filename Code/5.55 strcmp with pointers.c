#include <stdio.h>
#include <string.h>

int strcmp1(char *s, char *t); // function prototypes
int strcmp2(char *s, char *t);

int main(){
  char x[20], y[20];
  strcpy(x, "Test 1!");
  strcpy(y, "Test 2!");
  
  // result of strcmp is -1 as 1 is one character behind 2   
  printf("strcmp1: '%s' vs '%s' is %d\n", x, y, strcmp1(x, y));  
  printf("strcmp2: '%s' vs '%s' is %d\n", x, y, strcmp2(x, y));
  return(0);
}

// 1* strcmp1: return  <0 if s<t, 0 if s==t, >0 if s>t
// the value is obtained by subtracting the characters
// at the first position where s and t disagree
int strcmp1(char *s, char *t){
  int i;
  for(i=0; s[i]==t[i]; i++){
    if(s[i]=='\0'){
       return(0);
    }
  }
  return(s[i]-t[i]);
}

// a similar version with pointers
int strcmp2(char *s, char *t){
  for( ; *s == *t; s++, t++){
    if(*s == '\0'){
      return(0);
    }
  }
  return(*s - *t);
}
