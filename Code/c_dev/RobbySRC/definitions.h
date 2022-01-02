/**********************************************************************************/
/*                                                                                */
/*                       DEFINITIONS.H                                            */
/*                                                                                */
/*          Defines constants and declares external variabls.                     */
/*                                                                                */
/**********************************************************************************/


#include   <stdio.h>
#include   <stdlib.h>
#include   <math.h>
#include   <string.h>
#include   <sys/time.h>

#define PARAM_FILE_NAME "params"

#define    TRUE                    1
#define    FALSE                   0
#define    ONE                     1
#define    ZERO                    0

/*implemented by various routines */

#define    MBIG                    1000000000   /* used by knuth_random() */
#define    MSEED                   161803398
#define    FAC                     (1.0 / MBIG)

#define    MAIN_DEBUG    FALSE
#define    RUNGA_DEBUG   FALSE
#define    GA_DEBUG      FALSE
#define    FITNESS_DEBUG FALSE
#define    FITNESS_DEBUG_SHORT FALSE


/***************************************************************************/

typedef int bool;

#define EXTERN

/***************************************************************************/

/* The following parameters are defined in the params file */

/* ga parameters */

EXTERN char* FITNESS_FUNCTION_NAME;
EXTERN int WALL_PENALTY; 
EXTERN int CAN_REWARD; 
EXTERN int CAN_PENALTY; 
EXTERN int NUM_MOVES; 
EXTERN int NUM_ENVIRONMENTS_FOR_FITNESS; 

EXTERN int NUM_RUNS; 
EXTERN int MAX_NUM_FUNCTION_EVALS;
EXTERN char* SELECTION_METHOD;
EXTERN int POP_SIZE;
EXTERN int NUM_GENERATIONS; 
EXTERN int CHROM_LENGTH;
EXTERN double MUTATION_RATE;
EXTERN int CROSSOVER_SITES;
EXTERN double CROSSOVER_RATE;
EXTERN double RANK_MAX_WEIGHT; 
EXTERN double SIGMA_SCALING_MAX_WEIGHT; 
EXTERN int NUM_ELITE;


/***************************************************************************/

/* i/o */

EXTERN char* RUN_NUM_DIR;
EXTERN char* OUTPUT_DIR;
EXTERN int SNAPSHOT_INTERVAL;
EXTERN bool SHORT_PRINT;
EXTERN bool BEST_PRINT;
EXTERN bool LONG_PRINT;

/***************************************************************************/
/* For Robby-the-robot fitness function */ 

#define NUM_ACTIONS 7

/* Actions */ 
#define MOVE_NORTH 0
#define MOVE_SOUTH 1
#define MOVE_EAST 2
#define MOVE_WEST 3
#define STAY_PUT 4
#define PICK_UP 5
#define RANDOM_MOVE 6

#define EMPTY 0
#define CAN 1
#define WALL 2

/* We're encoding states using base 3, since there are 3 possible
   entries for a given site.  A state of Robby is NorthContent * NORTHBASE + 
   SouthContents * SOUTHBASE + etc. 
*/ 

#define NORTH_BASE 81    
#define SOUTH_BASE  27
#define EAST_BASE   9
#define WEST_BASE   3
#define CENTER_BASE 1

#define NUM_ENVIRONMENT_ROWS 10
#define NUM_ENVIRONMENT_COLUMNS 10

