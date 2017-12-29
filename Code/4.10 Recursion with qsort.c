#include <stdio.h>

void qsort(int v[], int left, int right);

int main(){
  int v[] = {4, 0, 2, 5, 1, 3};
  qsort(v, 0, 5);

  printf("Sorted values: ");
  for(int i=0; i<6; i++)
    printf("%d", v[i]);
  printf("\n");

  return(0);
}


void qsort(int v[], int left, int right){
  int i, last;
  void swap(int v[], int i, int j);
  
  if(left >= right)
    return; // do nothing if less than 2 elements 
      
  swap(v, left, (left+right)/2);
  last = left;
  for(i = left+1; i <= right; i++){
    if(v[i] < v[left])
      swap(v, ++last, i);
  }
  
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}


void swap(int v[], int i, int j){
  int temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
