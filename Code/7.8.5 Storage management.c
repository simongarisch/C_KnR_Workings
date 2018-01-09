// the functions malloc and calloc obtain blocks of memory dynamically
// void malloc(size_t n) returns a pointer to n bytes of uninitialised
// storage, or NULL if the request cannot be satisfied
// void calloc(size_t n) returns a pointer to enough space for an array
// of n objects of the specified size, or NULL if the request cannot be
// satisfied
// free(p) frees the space pointed to by p, where p was originally 
// obtained by a call to malloc or calloc.
// If the previously allocated memory is insufficient or more than
// required, you can change the previously allocated memory size using
// realloc(ptr, newsize);

#include <stdio.h>
#include <stdlib.h>

int main(){
  int num, i, *ptr, sum=0;
  printf("Enter number of elements: ");
  scanf("%d", &num);

  ptr = (int *)malloc(num * sizeof(int));
  if(ptr == NULL){
    printf("Error! Memory not allocated!\n");
    exit(0);
  }
  
  printf("Enter elements of array:\n");
  for(i=0; i<num; ++i){
    scanf("%d", ptr+i);
    sum += *(ptr+i);
  }

  printf("Sum = %d\n", sum);
  free(ptr);
  return(0);
}
