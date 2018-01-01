// when main is called it is called with two arguments
// The first (conventionally called argc, for argument count)
// is the number of command-line arguments the program was
// invoked with; the second (argv, for argument vector) is a 
// pointer to an array of character strings that contain arguments

// ./a.out hello world 
// ./a.out // program name is first argument
// hello
// world 

#include <stdio.h>

int main(int argc, char *argv[]){
  for(int i=0; i<argc; i++)
    printf("%s\n", argv[i]);

  return(0);
}
