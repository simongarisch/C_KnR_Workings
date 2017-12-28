#include <stdio.h>

void shellsort(int v[], int n);

int main(){
  int arr[10] = {1, 3, 2, 4, 6, 5, 8, 7, 10, 9};
  shellsort(arr, 10);
  for(int i=0; i<10; i++)
    printf("%d,", arr[i]);
  printf("\n");
  return(0);
}

void shellsort(int v[], int n){
  int gap, i, j, temp;

  for(gap=n/2; gap>0; gap/=2){
    for(i=gap; i<n; i++){
      for(j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap){
        temp = v[j];
        v[j] = v[j+gap];
        v[j+gap] = temp;
      }
    }
  }
}
