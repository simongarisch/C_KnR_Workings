/**********************************************************************************/
/*                                                                                */
/*                       GLOBALS.H                                                */
/*                                                                                */
/*           Defines data structures for GA and declares some                     */
/*           global variables.                                                    */
/*                                                                                */
/**********************************************************************************/


struct {
  int C_row; 
  int C_column; 
  int N_row;
  int N_column;
  int S_row;
  int S_column;
  int E_row;
  int E_column;
  int W_row;
  int W_column;
  bool contains_soda_can; 
} environment[NUM_ENVIRONMENT_ROWS][NUM_ENVIRONMENT_COLUMNS];  

struct  {
  int row; 
  int column; 
} robby; 

int robby_row, robby_column;  /* Current location of robby */ 

/* The struct for the ga; a population is an array of these */

typedef struct ga_rec_type {
    int  *chrom;
    double fitness;
    double weight; 
    int    generation;
    int    id;
} ga_rec;

ga_rec   *current_pop, *next_pop;

/* Various globals implemented for convenience */
FILE     *fp;

int      run_num; 
int      current_generation;
long     current_function_eval;
int      working_generation;
long     ran_seed, ran_seed_flag; /* if set, is set to random seed value */


double fitness_mean, fitness_std_dev; 

typedef enum {append, read, write } open_mode; /* used by my_open */

int max_id_length;  /* max length of id numbers */


/* used by knuth_random() and seed_random() */
static int inext;
static int inextp;
static long ma[56];






