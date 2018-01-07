#include <stdio.h>

// This defines a variable called flags that contains three l-bit fields
// The number following the colon represents the field width in bits

struct {
unsigned int is_keyword : 1;
unsigned int is_extern : 1;
unsigned int is_static : 1;
} flags;

int main(){
  flags.is_extern = flags.is_static = 1;
  flags.is_extern = flags.is_static = 0;
  printf("flags.is_extern=%d, flags.is_static=%d\n", flags.is_extern, flags.is_static);
  return(0);
}
