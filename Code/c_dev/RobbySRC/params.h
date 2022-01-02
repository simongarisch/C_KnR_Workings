/***************************************************************************/
/*                                                                         */
/*                        PARAMS.H                                         */
/*                                                                         */
/*         Functions to support storing parameters in a file.              */
/*                   Written by JBA, 10/93                                 */
/***************************************************************************/

#ifndef _PARAMS_H
#define _PARAMS_H

#include <stdio.h>

int read_param_file(char* fname);
void free_params(void);
void print_params(FILE*);
extern int display_params_with_quotes;

int param_defined(char* name);

/* These exit the program if the parameter is not defined, or if it is
   an illegal value (e.g. abc for an int).  One might want to  define
   more generous versions of these routines.
*/

char* string_param(char* name);
int bool_param(char* name);
int int_param(char* name);
double double_param(char* name); 

#endif

