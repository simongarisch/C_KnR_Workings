#include <stdio.h>

struct point{
  int x;
  int y;
};

struct point makepoint(int x, int y){
  struct point temp;
  temp.x = x;
  temp.y = y;
  return(temp);
}

int main(){
  struct point p = makepoint(20, 40);
  printf("Struct p has x=%d, y=%d\n", p.x, p.y);
  return(0);
}
