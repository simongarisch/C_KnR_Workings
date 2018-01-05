#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

// It is illegal for a structure to contain an instance of itself
// but struct tnode *left declares left to be a pointer to a tnode, not tnode itself.
struct tnode{ // the tree node
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *strdup2(char *s);
int getword(char *, int);

int main(){
  struct tnode *root;
  char word[MAXWORD];
  
  root = NULL;
  while(getword(word, MAXWORD) != EOF){
    if(isalpha(word[0]))
      root = addtree(root, word);
  }
  treeprint(root);
  return(0);
}

// add a node with w, at or below p
struct tnode *addtree(struct tnode *p, char *w){
  int cond;
  if(p==NULL){
    p = talloc();
	p->word = strdup2(w);
	p->count = 1;
	p->left = p->right = NULL;
  }else if((cond = strcmp(w, p->word)) == 0){
    p->count++; // repeated word
  }else if(cond < 0){ // less than into left subtree
    p->left = addtree(p->left, w);
  }else{ // greater than into right subtree
    p->right = addtree(p->right, w);
  }
  return(p);
}

// in-order print of tree p
void treeprint(struct tnode *p){
  if(p != NULL){
    treeprint(p->left);
	printf("%4d %s\n", p->count, p->word);
	treeprint(p->right);
  }
}

struct tnode *talloc(void){
  return((struct tnode *)malloc(sizeof(struct tnode)));
}

char *strdup2(char *s){ // make a duplicate of s
  char *p;
  p = (char *)malloc(strlen(s)+1); // +1 for '\0'
  if (p!=NULL)
    strcpy(p, s);
  return(p);
}

//-----------------------------------------
// the function getword finds a word, which is copied 
// into the array named as its first argument
int getword(char *word, int lim){
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while(isspace(c = getch()))
    ;
  if(c != EOF)
    *w++ = c;
  if(!isalpha(c)){
    *w = '\0';
    return(c);
  }
  for( ; --lim > 0; w++){
    if(!isalnum(*w = getch())){
      ungetch(*w);
      break;
    }
  }
  *w = '\0';
  return(word[0]); 
}

// getch and ungetch from chap 4
#define BUFSIZE 100
char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0;      // next free position in buf

int getch(void){
  return((bufp > 0) ? buf[--bufp] : getchar());
}

void ungetch(int c){
  if(bufp >= BUFSIZE){
    printf("ungetch: too many characters\n");
  }else{
    buf[bufp++] = c;
  }
}