// a table lookup
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist{
  struct nlist *next; // next entry in the chain
  char *name; // defined name
  char *defn; // replacement text 
};

static struct nlist *hashtab[HASHSIZE]; // pointer table

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
char *strdup2(char *s);


int main(){
  install("One", "1");
  install("Two", "2");

  struct nlist *p1 = lookup("One");
  printf("%s %s\n", p1->name, p1->defn);

  struct nlist *p2 = lookup("Two");
  printf("%s %s\n", p2->name, p2->defn);

  return(0);
}


char *strdup2(char *s){ // make a duplicate of s
  char *p;
  p = (char *)malloc(strlen(s)+1); // +1 for '\0'
  if (p!=NULL)
    strcpy(p, s);
  return(p);
}

// form hash value for string s
unsigned hash(char *s){
  unsigned hashval;
  for(hashval=0; *s!='\0'; s++)
    hashval = *s + 31 * hashval;
  return(hashval % HASHSIZE);
}

// look for s in hashtab
struct nlist *lookup(char *s){
  struct nlist *np;
  for(np = hashtab[hash(s)]; np!=NULL; np=np->next){
    if(strcmp(s, np->name) == 0)
      return(np); // found
  }
  return(NULL);
}

// put name, defn in hashtab
struct nlist *install(char *name, char *defn){
  struct nlist *np;
  unsigned hashval;

  if((np=lookup(name)) == NULL){
    np = (struct nlist *)malloc(sizeof(*np));
    if(np == NULL || (np->name = strdup2(name)) == NULL)
      return(NULL);
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }else{ // already there
    free((void *)np->defn); // free previous defn
  }

  if((np->defn = strdup2(defn)) == NULL)
    return(NULL);
  return(np);
}
