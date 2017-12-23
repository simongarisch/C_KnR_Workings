#include <stdio.h>

int main(){

  int c;
  c = getchar();
  while(c != EOF){  // EOF is an integer defined in <stdio.h>
    putchar(c);     // The actual value of EOF is system-dependent, but is commonly -1
    c = getchar();  // One can use Ctrl+D to send EOT character which will force function return -1
  }

}
