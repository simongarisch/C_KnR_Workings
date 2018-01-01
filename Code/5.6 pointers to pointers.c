#include <stdio.h>
#include <string.h>

#define MAXLINES 5000    // max # lines to be sorted
#define MAXLEN 1000      // max length of any input line
#define ALLOCSIZE 10000  // size of available space for alloc
char *lineptr[MAXLINES]; // array of pointers to text lines

// function prototypes
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
char *alloc(int n);
int getline2(char s[], int lim);
void qsort(char *v[], int left, int right);

int main(){
  int nlines; // number of input lines read
  if((nlines = readlines(lineptr, MAXLINES)) >= 0){
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return(0);
  }else{
    printf("error: input too big to sort\n");
    return(-1);
  }
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


/*C guarantees that zero is never a valid address
  the symbolic constant NULL is often used in place of zero
  as a mneumonic to indicate more clearly that this is a special 
  value for a pointer. NULL is defined in <stdio.h> */

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

// The getline() function is prototyped in the stdio.h header file
// Here we define our own getline2 function
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

void qsort(char *v[], int left, int right){
  int i, last;
  void swap(char *v[], int i, int j);
  
  if(left >= right) // do nothing if fewer than 2 elements
    return;

  swap(v, left, (left+right)/2);
  last = left;

  for(i=left+1; i<= right; i++){
    if(strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);

    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
  }
}

void swap(char *v[], int i, int j){
  char *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
