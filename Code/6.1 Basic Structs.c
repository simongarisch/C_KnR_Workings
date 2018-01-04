#include <stdio.h>

struct point{
  int x;
  int y;
}; // with structs don't forget to end with a semicolon

int main(){
  struct point p = {100, 120};
  printf("For struct p x is %d and y is %d\n", p.x, p.y);
  printf("**********\n");
  
  // and dealing with struct pointers
  struct point *pp = &p;
  printf("For struct p x is %d and y is %d\n", (*pp).x, (*pp).y);
  printf("For struct p x is %d and y is %d\n", pp->x, pp->y);
}
