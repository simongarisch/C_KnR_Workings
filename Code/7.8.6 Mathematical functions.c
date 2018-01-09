// there are a number of math functions declared in <math.h>

// sin(x) sine of x, x in radians
// sos(x) cosine of x, x in radians
// atan2(y,x) arctangent of y/x, in radians
// exp(x) exponential function e^(x)
// log(x) natural (base e) logarithm of x (x>0)
// log10(x) common (base 10) logarithm of x (x>0)
// pow(x, y) x^y
// sqrt(x) square root of x (x>=0)
// fabs(x) absolute value of x

// gcc "7.8.6 Mathematical functions.c" -lm -o a.out
#include <stdio.h>
#include <math.h>

int main(){
  int x=2, y=3;
  
  // pow(2,3)=8.00
  printf("pow(%d,%d)=%0.2f\n", x, y, pow(x,y));

  // sqrt(9)=3.00
  printf("sqrt(9)=%0.2f\n", sqrt(9));
  return(0);
}
