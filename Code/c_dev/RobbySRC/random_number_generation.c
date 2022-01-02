/***************************************************************************/
/*                                                                         */
/*                  RANDOM_NUMBER_GENERATION.C                             */
/*                                                                         */
/*              Random number generation routines                          */
/*                                                                         */
/***************************************************************************/

#include    "definitions.h"
#include    "globals.h"
#include    "prototypes.h"

double knuth_random()
/* Knuth's subtractive-method portable random number generator, described in 
 * the first edition of Numerical Recipes in C, p. 212.  
 * Returns a double between 0 and 1. 
 */
{
    long mj;
    
    if (++inext == 56)
	inext = 1;
    
    if (++inextp == 56)
	inextp = 1;

    mj = ma[inext] - ma[inextp];
    
    if (mj < 0)
	mj += MBIG;

    ma[inext] = mj;
    return mj * FAC;
}

/***************************************************************************/

long seed_random(long seed)
/* Returns a seed for the random number generator */
{
    long mj;
    long mk;
    register int i;
    register int k;
	
    if (seed < 1)
    {
	extern int gettimeofday();

	struct timeval tp;
	if (gettimeofday(&tp, (struct timezone *)0) == -1)
        {
	    fprintf(stderr, "Could not gettimeofday in knuth_srand().");
	    exit(1);
	}
	
	seed = tp.tv_usec;
    }
    
    if (seed >= MBIG)
    {
	fprintf(stderr, "Seed value too big (> %d) in knuth_srand().", MBIG);
	exit(1);
    }

    ma[55] = mj = seed;
    mk = 1;
    
    for (i = 1; i <= 54; i++)
    {
	register int ii = (21 * i) % 55;
	ma[ii] = mk;
	mk = mj - mk;
	if (mk < 0)
	    mk += MBIG;
	mj = ma[ii];
    }
    
    for (k = 0; k < 4; k++)
    {
	for (i = 1; i <= 55; i++)
        {
	    ma[i] -= ma[1 + (i + 30) % 55];
	    if (ma[i] < 0)
		ma[i] += MBIG;
	}
    }
    
    inext = 0;
    inextp = 31;
    
    return seed;
}

/***************************************************************************/





