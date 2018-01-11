// with lseek it is possible to treat files more or less
// like large arrays, at the price of slower access

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int get(int fd, long pos, char *buf, int n);

int main(int argc, char *argv[]){
  int f1;
  char buf[BUFSIZ];
  
  if(argc != 2)
    printf("Specify file to read\n");
  if((f1 = open(argv[1], O_RDONLY, 0)) == -1)
	printf("Can't open %s\n", argv[1]);

  if(get(f1, 3, buf, 2) == -1)
    printf("Can't read from file\n");
  else
    printf("%s\n", buf);
  
  
  return(0);
}

int get(int fd, long pos, char *buf, int n){
  if(lseek(fd, pos, 0) >= 0)
    return(read(fd, buf, n));
  else
    return(-1);
}