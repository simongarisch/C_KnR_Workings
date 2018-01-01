// the important advantage of the pointer array is that
// the rows of the array may be of different lengths
// by far the most frequent use of arrays of pointers is
// to store character strings of diverse lengths

#include <stdio.h>

int main(){
  char a[][15] = {
    "Illegal month",
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
  };

  char *b[] = {
    "Illegal month",
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
  };
  
  for(int i=0; i<13; i++)
    printf("%s, %s\n", a[i], b[i]);

  return(0);
}
