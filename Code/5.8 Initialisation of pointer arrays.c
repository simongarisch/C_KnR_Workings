#include <stdio.h>
#include <string.h>

char *month_name(int n); // function prototype

int main(){
  for(int i=-2; i<=15; i++)
    printf("The month for int %d is %s\n", i, month_name(i));
  return(0);
}

// return name of n-th month
// this is the ideal application for an internal static array
char *month_name(int n){
  static char *name[] = {
    "Illegal month",
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
  };
  return(n<1 || n>12) ? name[0] : name[n];
}
