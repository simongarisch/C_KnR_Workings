// a union is a variable that may hold (at different times)
// objects if different types and sizes
// they are analogous to variant records in pascal
// the purpose of union: a single variable that can
// legitimately hold any one of several types
#include <stdio.h>

typedef struct{ // holds several variables
  int x;
  float y;
}myStruct, *myStructPtr;

typedef union{ // one variable that can hold several types
  int x;
  float y;
}myUnion, *myUnionPtr;

typedef struct{
  int a;
  int b;
  union{
    int i;
    float j;
  }u;
}myStruct2, *myStruct2Ptr;


int main(){
  myStruct s;
  myStructPtr ps = &s;
  s.x = 1;
  s.y = 2.4;
  printf("Struct x=%d, y=%0.2f\n", ps->x, ps->y); // Struct x=1, y=2.40
  
  myUnion u;
  myUnionPtr pu = &u;
  u.x = 1;
  printf("Union x initialised as %d\n", pu->x); // Union x initialised as 1
  
  u.y = 2.3; // the x value gets overwritten as they are sharing memory space
  // unions allocate space equal to the largest type
  // it's up to the programmer to track the last input into union 
  printf("Union x=%d, y=%0.2f\n", pu->x, pu->y); // Union x=1075000115, y=2.30, ...x is nonsense
  
  myStruct2 ms2;
  myStruct2Ptr pms2 = &ms2;
  ms2.a = 1;
  ms2.b = 2;
  ms2.u.j = 2.4;
  printf("myStruct2: a=%d, b=%d, u.j=%0.2f\n", pms2->a, pms2->b, pms2->u.j); // myStruct2: a=1, b=2, u.j=2.40

  return(0);
}
