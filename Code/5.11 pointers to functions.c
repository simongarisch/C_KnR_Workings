#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000    // max #lines to be sorted
#define MAXLEN 1000
#define ALLOCSIZE 10000
char *lineptr[MAXLINES]; // pointers to text lines

// function prototypes
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort2(void *v[], int left, int right, int(*comp)(void *, void *));
int numcmp(char *s1, char *s2);
int getline2(char s[], int lim);
char *alloc(int n);

int main(int argc, char *argv[]){
  int nlines;
  int numeric = 0;

  if(argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;
  if((nlines = readlines(lineptr, MAXLINES)) >= 0){
    qsort2((void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcmp));
    writelines(lineptr, nlines);
    return(0); 
  }else{
    printf("Input too big to sort\n");
    return(-1);
  }
  return(0);
}

// read input lines
int readlines(char *lineptr[], int maxlines){
  int len, nlines;
  char *p, line[MAXLEN];
  
  nlines = 0;
  while((len = getline2(line, MAXLEN)) > 0){
    if(nlines >= maxlines || (p = alloc(len)) == NULL)
      return(-1);
    else{
      line[len-1] = '\0'; // delete newline
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return(nlines);
}


// write output lines
void writelines(char *lineptr[], int nlines){
  int i;
  for(i=0; i<nlines; i++)
    printf("%s\n", lineptr[i]);
}

// int (*comp)(void *, void *) which says that 
// comp is a pointer to a function that has two
// void arguments and returns int.
// (*comp)(v[i], v[left]) is the call to the function
void qsort2(void *v[], int left, int right, 
           int(*comp)(void *, void *)){
  int i, last;
  void swap(void *v[], int, int);

  if(left > right)
    return; // do nothing if fewer than 2 elements

  swap(v, left, (left+right)/2);
  last = left;
  for(i=left+1; i<=right; i++){
    if((*comp)(v[i], v[left]) <0)
      swap(v, ++last, i);
  }

  swap(v, left, last);
  qsort2(v, left, last-1, comp);
  qsort2(v, last+1, right, comp);
}


// compare s1 and s2 numerically
int numcmp(char *s1, char *s2){
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if(v1 < v2)
    return(-1);
  else if(v1 > v2)
    return(1);
  else
    return(0);
}

void swap(void *v[], int i, int j){
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}


int getline2(char s[], int lim){
  int c, i;
  for(i = 0; (i<lim-1 && (c=getchar())!=EOF && c!='\n'); ++i){
    s[i] = c;
  }
  if(c == '\n'){
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return(i);
}


static char allocbuf[ALLOCSIZE]; // storage for alloc 
static char *allocp = allocbuf;  // next free position

char *alloc(int n){ // return pointer to n characters
  if(allocbuf + ALLOCSIZE - allocp >= n){
    allocp += n;
    return(allocp - n); // old p
  }else{ // not enough room
    return(0);
  }
}
