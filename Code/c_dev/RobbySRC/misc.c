/***************************************************************************/
/*                                                                         */
/*                            MISC.C                                       */
/*                                                                         */
/*           Miscellaneous routines for memory management                  */
/*                                                                         */
/***************************************************************************/


#include    "definitions.h"
#include    "globals.h"
#include    "prototypes.h"

void *my_malloc(int size)
/* Malloc with error checking */ 
{
    void *space;

    /* Allocate space. Print error message on error and exit */
   
    if ((space = (void *)malloc(size)) == NULL)  
    {
        fprintf(stderr, "Error: Out of memory\n");
        exit(1);
    }

    return(space);
}

/***************************************************************************/

void malloc_current_pop()
/* Mallocs current_pop */ 
{
    register int    i;
    
    current_pop = (ga_rec *) my_malloc(POP_SIZE * sizeof(ga_rec));

    for (i = 0; i < POP_SIZE; i++)
	current_pop[i].chrom = (int *) my_malloc(CHROM_LENGTH * sizeof(int));

}

/***************************************************************************/

void malloc_next_pop()
/* Mallocs next_pop */ 
{
    register int    i;

    next_pop = (ga_rec *)my_malloc(POP_SIZE * sizeof(ga_rec));

    for (i = 0; i < POP_SIZE; i++)  
        next_pop[i].chrom = (int *) my_malloc(CHROM_LENGTH * sizeof(int));
}

/***************************************************************************/






