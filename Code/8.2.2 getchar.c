#include <stdio.h>
#include <unistd.h>

int main(){
  int c;

  c = getchar();
  printf("Using getchar: c = %c\n", c);
  
  c = getchar1();
  printf("Using getchar1: c = %c\n", c);
  
  c = getchar2();
  printf("Using getchar2: c = %c\n", c);
  
  return(0);
}

int getchar1(void){
  char c;
  return((read(0, &c, 1)==1)? (unsigned char)c : EOF);
}

int getchar2(void){
  static char buf[BUFSIZ];
  static char *bufp = buf;
  static int n=0;
  
  if(n==0){ // buffer is empty
    n = read(0, buf, sizeof(buf));
	bufp = buf;
  }
  return((--n >= 0)? (unsigned char)*bufp++: EOF);
}