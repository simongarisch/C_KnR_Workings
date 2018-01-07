// the standard header <stdarg.h> contains a set of
// macro definitions that define how to step through an argument list
// the type va_list is used to declare a variable that will refer to each argument in turn
#include <stdio.h>
#include <stdarg.h> 

void minprintf(char *fmt, ...);

int main(){
  int i=3;
  float f=3.2;
  char s[] = "some string!";
  minprintf("i=%d, f=%f, s=%s\n", i, f, s);
  return(0);
}

// minimal printf with variable argument list
void minprintf(char *fmt, ...){
  va_list ap;  // variable argument list
  char *p, *sval;
  int ival;
  double dval;
  
  va_start(ap, fmt); // make ap point to 1st unnamed arg
  for(p=fmt; *p; p++){
    if(*p!='%'){
      putchar(*p);
      continue;
    }
    switch(*++p){
      case 'd':
        ival = va_arg(ap, int);
        printf("%d", ival);
        break;
      case 'f':
        dval = va_arg(ap, double);
        printf("%f", dval);
        break;
      case 's':
        for(sval = va_arg(ap, char *); *sval; sval++)
          putchar(*sval);
        break;
      default:
        putchar(*p);
        break;      
    } 
  }
  va_end(ap); // clean up when done
}
