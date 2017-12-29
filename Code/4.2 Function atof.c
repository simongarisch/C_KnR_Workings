#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

double atof2(char s[]);
int getline2(char s[], int lim);

int main(){
  double sum = 0;
  char line[MAXLINE];
  
  while(getline2(line, MAXLINE) > 0)
    printf("\t%g\n", sum += atof2(line));
  return(0);
}


double atof2(char s[]){
  double val, power;
  int i, sign;

  for(i=0; isspace(s[i]); i++){
    ;
  }
  sign = (s[i] == '-')? -1 : 1;
  
  if(s[i] == '+' || s[i] == '-')
    i++;

  for(val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.')
    i++;

  for(power = 1.0; isdigit(s[i]); i++){
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0; 
  }
  
  return(sign * val / power);
}


int getline2(char s[], int lim){
  int c, i;
  i = 0;

  while(--lim>0 && (c=getchar())!=EOF && c!='\n'){
    s[i++] = c;
  }

  if(c == '\n'){
    s[i++] = c;
  }
  s[i] = '\0';
  return(i);
}


