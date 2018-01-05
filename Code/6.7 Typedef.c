#include <stdio.h>

typedef char *String;  // a string synonym for char *

typedef struct{
  int x;
  int y;
} myStruct, *myStructPtr; // myStruct is a struct
//*sptr is a pointer to a this struct

int main(){
  // typedef for a char pointer
  char s[] = "Some string!";
  String ps = s;

  while(*ps != '\0'){
    printf("%c.", *ps); // S.o.m.e. .s.t.r.i.n.g.!.
    ps++;
  }
  printf("\n");

  myStruct m;
  m.x = 1;
  m.y = 2;
  myStructPtr p = &m;
  printf("x=%d, y=%d\n", p->x, p->y); // x=1, y=2

  return(0);
}
