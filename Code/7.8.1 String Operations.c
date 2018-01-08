// Covering some of what is available in string.h
#include <stdio.h>
#include <string.h>
#define MAXLEN 30

int main(){
  char s1[MAXLEN], s2[MAXLEN];
  
  // strcat(s, t) concatenate to end of s
  // strcat('Hello ', 'Simon!') produces 'Hello Simon!'
  strcpy(s1, "Hello ");
  strcpy(s2, "Simon!");
  printf("strcat('%s', '%s') produces ", s1, s2);
  strcat(s1, s2);
  printf("'%s'\n", s1);   
 
  // strncat(s, t, n) concatenate max n # characters from t
  // strncat('M', 'mmmmmmmmmmmmmm', 5) produces 'Mmmmmm'
  // to the end of s
  strcpy(s1, "M");
  strcpy(s2, "mmmmmmmmmmmmmm");
  printf("strncat('%s', '%s', 5) produces ", s1, s2);
  strncat(s1, s2, 5);
  printf("'%s'\n", s1);

  // strcmp(s, t) return negative (s < t), 
  // zero (s == t) or positive (s > t)
  // strcmp('AAA', 'BBB') produces -1
  // strcmp('AAA', 'AAA') produces 0
  // strcmp('BBB', 'AAA') produces 1
  strcpy(s1, "AAA");
  strcpy(s2, "BBB");
  printf("strcmp('%s', '%s') produces %d\n", s1, s2, strcmp(s1, s2));
  printf("strcmp('%s', '%s') produces %d\n", s1, s1, strcmp(s1, s1));
  printf("strcmp('%s', '%s') produces %d\n", s2, s1, strcmp(s2, s1));

  // strlen(s) returns the lentgh of s
  // strlen('AAA') is 3, strlen('BBBB') is 4
  strcpy(s1, "AAA");
  strcpy(s2, "BBBB");
  // %lu is the correct format for unsigned long
  printf("strlen('%s') is %lu, strlen('%s') is %lu\n", s1, strlen(s1), s2, strlen(s2));

  // other string operations
  // strncmp(s, t, n): same as strcmp, but only for the first n chars
  // strcpy(s, t): copy t to s
  // strncpy(s, t, n): copy at most n characters to s
  // strchr(s, c): return pointer to first c in s, or NULL if not present
  // strrchr(s, c): return pointer to last c in s, or NULL if not present

  return(0);
}

