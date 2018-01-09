// Several functions from ctype.h perform character tests and conversions
// isalpha(c): non-zero if c is alphabetic, 0 if not
// isupper(c): non-zero if c is upper, 0 if not
// islower(c): non-zero if c is lower, 0 if not
// isdigit(c): non-zero if c is digit, 0 if not
// isalnum(c): non-zero if isalpha(c) or isdigit(c), 0 if not
// isspace(c): non-zero if c is blank, tab, newline, return, formfeed, vertical tab
// toupper(c): return c converted to upper case
// tolower(c): return c converted to lower case
#include <stdio.h>
#include <ctype.h>

int main(){
  char a='A', b='b', c=' ', d='3', e='9';
  
  // isalpha(c): non-zero if c is alphabetic, 0 if not
  // isalpha('A')=1, isplpha('b')=2, isalpha(' ')=0, isalpha('3')=0
  printf("isalpha('%c')=%d, isalpha('%c')=%d, isalpha('%c')=%d, isalpha('%c')=%d\n", a, isalpha(a), b, isalpha(b), c, isalpha(c), d, isalpha(d));
  
  // isupper(c): non-zero if c is upper, 0 if not
  // isupper('A')=1, usupper('b')=0, isupper(' ')=0, isupper('3')=0
  printf("isupper('%c')=%d, isupper('%c')=%d, isupper('%c')=%d, isupper('%c')=%d\n", a, isupper(a), b, isupper(b), c, isupper(c), d, isupper(d));
  
  // islower(c): non-zero if c is lower, 0 if not
  // islower('A')=0, islower('b')=2, islower(' ')=0, islower('3')=0
  printf("islower('%c')=%d, islower('%c')=%d, islower('%c')=%d, islower('%c')=%d\n", a, islower(a), b, islower(b), c, islower(c), d, islower(d));
  
  // isdigit(c): non-zero if c is digit, 0 if not
  // isdigit('A')=0, isdigit('b')=0, isdigit(' ')=0, isdigit('3')=1
  printf("isdigit('%c')=%d, isdigit('%c')=%d, isdigit('%c')=%d, isdigit('%c')=%d\n", a, isdigit(a), b, isdigit(b), c, isdigit(c), d, isdigit(d));
  
  // isalnum(c): non-zero if isalpha(c) or isdigit(c), 0 if not
  // isalnum('A')=1, isalnum('b')=2, isalnum(' ')=0, isalnum('3')=4
  printf("isalnum('%c')=%d, isalnum('%c')=%d, isalnum('%c')=%d, isalnum('%c')=%d\n", a, isalnum(a), b, isalnum(b), c, isalnum(c), d, isalnum(d));
  
  // isspace(c): non-zero if c is blank, tab, newline, return, formfeed, vertical tab
  // isspace('A')=0, isspace('b')=0, isspace(' ')=8, isspace('3')=0
  printf("isspace('%c')=%d, isspace('%c')=%d, isspace('%c')=%d, isspace('%c')=%d\n", a, isspace(a), b, isspace(b), c, isspace(c), d, isspace(d));
  
  // toupper(c): return c converted to upper case
  // toupper('A')='A', toupper('b')='B', toupper(' ')=' ', toupper('3')='3'
  printf("toupper('%c')=%c, toupper('%c')=%c, toupper('%c')=%c, toupper('%c')=%c\n", a, toupper(a), b, toupper(b), c, toupper(c), d, toupper(d));
  
  // tolower(c): return c converted to lower case
  // tolower('A')='a', tolower('b')='b', tolower(' ')=' ', tolower('3')='3'
  printf("tolower('%c')=%c, tolower('%c')=%c, tolower('%c')=%c, tolower('%c')=%c\n", a, tolower(a), b, tolower(b), c, tolower(c), d, tolower(d));
  
  return(0);
}