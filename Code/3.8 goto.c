#include <stdio.h>

int main(){
  
  int disaster = 0;

  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      if(i==5 && j==5){
        disaster = 1;
        goto error;
      }
    }
  }
  return(0);

error:
  printf("Disaster struck!\n");
  return(-1);
}
