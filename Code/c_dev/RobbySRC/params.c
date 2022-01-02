/***************************************************************************/
/*                                                                         */
/*                           PARAMS.C                                      */
/*                                                                         */
/* Functions to handle a file of parameters. Each parameter is written as  */
/*                          name  value                                    */
/* on a single line.  The case of name doesn't matter.  Leading and        */
/* trailing whitespace is removed from value, unless it is enclosed in     */
/* quotes.  (Quotes also prevent # from being interpreted as a comment     */
/* character.)   If no value is specified, the value is the                */
/* empty string "".  Anything from # to the end of the line is a comment.  */
/* Multiple definitions are not warned about, and only the first is used.  */ 
/*                                                                         */
/* Note: \" is not supported in strings!  Nor are any other escape chars.  */
/*                                                                         */
/* Written by JBA, 10/93                                                   */
/***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "params.h"

typedef struct {
  char* name;
  char* value;
} Param;

typedef int bool;

/* double strtod(char*, char**); */

int n_params, param_size;
Param* param = 0;

int lineno;

bool display_params_with_quotes;

static Param* lookup_param(char* name)
{
  int i;

  for (i = 0; i < n_params; i++) {
    if (strcasecmp(name, param[i].name) == 0)
      return &param[i];
  }
  return NULL;
}

static Param* lookup_param_force(char *name)
{
  Param* p = lookup_param(name);
  if (!p) {
    fprintf(stderr, "error: parameter %s not found\n", name);
    exit(1);
  } else
    return p;
}
    

bool param_defined(char* name)
{
  return (lookup_param(name) != NULL);
}

char* string_param(char* name)
{
  Param* p = lookup_param_force(name);
  return p->value;
}

int int_param(char* name)
{
  Param* p = lookup_param_force(name);
  char *s;
  long l = strtol(p->value, &s, 10);
  if (s == p->value || *s != '\0') {
    fprintf(stderr, "error: bad int parameter %s = %s\n",
	    p->name, p->value);
    exit(1);
  } else
    return (int) l;
}
  

double double_param(char* name)
{
  Param* p = lookup_param_force(name);
  char* s;
  double d = strtod(p->value, &s);
  if (s == p->value || *s != '\0') {
    fprintf(stderr, "error: bad double parameter %s = %s\n",
	    p->name, p->value);
      exit(1);
  } else
    return d;
}


bool bool_param(char* name)
{
  Param* p = lookup_param_force(name);
  if (strcasecmp(p->value, "TRUE") == 0 || strcmp(p->value, "1")==0)
    return 1;
  else if (strcasecmp(p->value, "FALSE")==0 || strcmp(p->value, "0")==0)
    return 0;
  else {
    fprintf(stderr, "error: bad Boolean parameter %s = %s\n",
	    p->name, p->value);
    exit(1);
  }
}

/********************** Reading a Parameter File **********************/

static char* read_line(FILE* fp);
static char* clean_line(char* line);
static void add_param(char* name, char* value);

bool read_param_file(char* fname)
/* returns FALSE if problems occurred */
{
  FILE *fp;
  char* line;

  if (param != 0)
    free_params();
  n_params = 0;
  lineno = 0;
  
  if ((fp = fopen(fname, "r")) == NULL) {
    fprintf(stderr, "error opening param file %s\n", fname);
    return 0;
  }
  
  while (line = read_line(fp)) {
    line = clean_line(line);
    if (*line) {
      char* p = line;
      while (!isspace(*p) && *p != '\0') p++;
      /* from line to p is the name of the param */
      if (*p == '\0')
	add_param(line, "");
      else {
	*p = '\0';
	p++;
	while (isspace(*p)) p++;
	/* from p on is the value; or '\0' if no value was specified */
	add_param(line, p);
      }
    }
  }
  fclose(fp);
  return 1;
}
      
#define BUFLEN 500

static char* read_line(FILE* fp)
{
  static char buf[BUFLEN];

  lineno++;
  if (fgets(buf, BUFLEN, fp) == NULL)
    return NULL;
  else if (buf[strlen(buf)-1] != '\n' && !feof(fp)) {
    fprintf(stderr, "line %d of param file too long (> %d)\n", lineno, BUFLEN);
    exit(1);
  } else
    return buf;
}

static char* clean_line(char* line)
  /* remove whitespace, comments */
{
  char* start = line;
  char* end, *comstart;
  bool in_string;

  /* remove leading whitespace */
  while (isspace(*start)) start++;
  
  /* remove # to end of line */ 
  in_string = 0;
  for (comstart = start; *comstart != '\0'; comstart++) {
    if (*comstart == '#' && !in_string) {
      *comstart = '\0';
      break;
    } else if (*comstart == '"')
      in_string = !in_string;
  }

  /* remove trailing whitespace */
  if (*start != '\0') {
    end = start + strlen(start) - 1;
    while (isspace(*end)) end--;
    *(end+1) = '\0';
  }
  return start;
}



static void add_param(char* name, char* value)
{
  /*   static Param* lookup_param(char* name); */ 

  if (param == 0) {
    param_size = 20;
    param = malloc(param_size*sizeof(Param));
  } else if (n_params >= param_size) {
    param_size *= 2;
    param = realloc(param, param_size*sizeof(Param));
  }
  assert(n_params < param_size);

  /* if name is present, warn and ignore */
  if (lookup_param(name)) {
    fprintf(stderr, 
	    "warning: duplicate param %s; only the first will be used\n",
	    name);
  } else {
    param[n_params].name = strdup(name);

    /* remove surrounding quotation marks from value */
    if (*value == '"')
      value++;
    if (value[strlen(value)-1] == '"')
      value[strlen(value)-1] = '\0';

    param[n_params].value = strdup(value);
    n_params++;
  }
}

void free_params()
{
  int i;

  for (i = 0; i < n_params; i++) {
    free(param[i].name);
    free(param[i].value);
  }
  free(param);
  param = 0;
}

void print_params(FILE* fp)
{
  int i;

  for (i = 0; i < n_params; i++) {
    fprintf(fp, "%s: ", param[i].name);
    if (display_params_with_quotes)
      fprintf(fp, "`%s'\n", param[i].value);
    else
      fprintf(fp, "%s\n", param[i].value);
  }
}

/************************* Retrieving Params *****************************/


/*******************************************************************/
#ifdef TEST

main(int argc, char** argv)
{
  if (argc != 2) {
    fprintf(stderr, "usage: params filename\n");
    exit(1);
  }
  if (read_param_file(argv[1])) {
    print_params(stdout);
    for (;;) {
      char type;
      char name[100], line[100];

      printf("> ");
      gets(line);
      if (sscanf(line, "%c %s", &type, name) != 2) return;
      switch (type) {
        case 's': printf("%s\n", string_param(name)); break;
	case 'b': printf("%d\n", bool_param(name)); break;
	case 'i': printf("%d\n", int_param(name)); break;
	case 'd': printf("%lf\n", double_param(name)); break;
	default: printf("unknown type %c\n", type);
      }
    }
  }
}

    
#endif

    
    

