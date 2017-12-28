#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void){
  int arr[] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55};
  int x, n;

  printf("%d\n", binsearch(8, arr, 10));
  return(0);
}


int binsearch(int x, int v[], int n){
  int low, high, mid;
  low = 0;
  high = n-1;

  while(low < high){
    mid = (low + high) / 2;
    if(x < v[mid]){
      high = mid - 1;
    }else if(x > v[mid]){
      low = mid + 1;
    }else{
      return(mid);
    }
  }
  return(-1);
}
