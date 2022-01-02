/* Calculates the performance of a given strategy for Robby */ 

#include <stdio.h>
#include   <stdlib.h>
#include   <math.h>
#include   <string.h>
#include   <sys/time.h>

#define    TRUE                    1
#define    FALSE                   0

#define    MBIG                    1000000000   /* used by knuth_random() */
#define    MSEED                   161803398
#define    FAC                     (1.0 / MBIG)

#define    DEBUG FALSE

#define NUM_ENVIRONMENT_ROWS 10
#define NUM_ENVIRONMENT_COLUMNS 10

/* Actions */ 
#define MOVE_NORTH 0
#define MOVE_SOUTH 1
#define MOVE_EAST 2
#define MOVE_WEST 3
#define STAY_PUT 4
#define PICK_UP 5
#define RANDOM_MOVE 6

#define NORTH_BASE 81    
#define SOUTH_BASE  27
#define EAST_BASE   9
#define WEST_BASE   3
#define CENTER_BASE 1

#define EMPTY 0
#define CAN 1
#define WALL 2

#define WALL_PENALTY -5   /* Points lost for crashing into a wall */
#define CAN_REWARD 10     /*  Points gained for picking up a can */
#define CAN_PENALTY -1    /* Points lost for trying to pick up a can in an empty cell */

#define CHROM_LENGTH 243

#define NUM_MOVES 200 
#define NUM_ENVIRONMENTS_FOR_PERFORMANCE 10000

typedef int bool;

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

int robby_row, robby_column;  /* Current location of robby */ 

int *chrom; 

int n_row, n_column, s_row, s_column, e_row, e_column, w_row, w_column, c_row, c_column; 

int state, action; 

/* Used by knuth_random() and seed_random() */
static int inext;
static int inextp;
static long ma[56];
long seed_random(long seed); 
double knuth_random(); 

void read_chrom();
void print_environment(); 

void calc_performance(int* chrom);
int calc_performance_one_environment(int* chrom);
void print_a_chromosome(int *chrom);
int perform_action(int action);
void init_environment(); 

/***********************************************************************/

main()
{
  /* Reads in chrom, and runs on NUM_ENVIRONMENTS_FOR_PERFORMANCE randomly generated environments
     for NUM_MOVES moves on each.  Returns average performance over these 
     NUM_ENVIRONMENTS_FOR_PERFORMANCE environments */

  int i, row, column;

  int performance_points = 0; 

  float environment_x1, environment_y1, environment_x2, environment_y2; 

  long ran_seed = 0, ran_seed_flag;

  float performance; 

  /* Seed random number generator */
  ran_seed = ran_seed_flag ? ran_seed_flag : 0;
  ran_seed = seed_random(ran_seed_flag);

  chrom = (int *) malloc(CHROM_LENGTH * sizeof(int));

  read_chrom();

  calc_performance(chrom); 

}

/*****************************************************************************************/

void
calc_performance(int* chrom)
/* Performance function: Environment is re-generated.  Chrom is run on
 *  environment for NUM_MOVES.  Performance is number of performance points it
 *  gets. */

{
  int environment_number, total_score = 0; 
  double performance = 0.0; 

  /* Run this individual on NUM_ENVIRONMENTS_FOR_PERFORMANCE different
     random enviornments.  Performance is sum of performance points. */ 

#if DEBUG
    printf("In calc_performance with chrom \n"); 
    print_a_chromosome(chrom); 
#endif

#if DEBUG
    printf("In calc_performance with chrom \n"); 
    print_a_chromosome(chrom); 
#endif

    for (environment_number = 1; environment_number <= NUM_ENVIRONMENTS_FOR_PERFORMANCE; environment_number++) {

#if DEBUG
    printf("On Environment %d\n", environment_number); 
#endif
      total_score = total_score + calc_performance_one_environment(chrom); 
    }

#if DEBUG
    printf("Total score is %d\n", total_score); 
#endif

    performance = (double) total_score / (double) NUM_ENVIRONMENTS_FOR_PERFORMANCE;   /* average */ 


    printf("Performance is: %f\n", performance); 

}

/***************************************************************************/

int
calc_performance_one_environment(int* chrom)
/* Environment is  randomly generated.  Chrom is run on
 *  environment for NUM_MOVES.  Function returns number of performance points the chromosome
 *  gets. */

{
  int site, move_number, action, performance_points = 0; 
  int n_row, n_column, s_row, s_column, e_row, e_column, w_row, w_column, c_row, c_column; 
  double robby_text_row_coord, robby_text_column_coord;  /* Where to draw robby */ 
  int state, smaller_state; 

  init_environment(); 

  /* Keep going for NUM_MOVES.  Performance is how many cans were
   * collected. */ 


  for (move_number = 1; move_number <= NUM_MOVES; move_number++) {

#if DEBUG
    printf("Move: %d\n", move_number); 
#endif

    state = 0; 

    /* Calculate integer representing state of neighborhood NSEWC.  It is in [0, 242]. 
       The contents of each of these five cells is represented by:  EMPTY = 0, CAN = 1, WALL = 2 */

    /* NORTH */ 
    n_row = environment[robby_row][robby_column].N_row; 
    n_column = environment[robby_row][robby_column].N_column; 

    if (((n_row < 0) || (n_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((n_column < 0) || (n_column >= NUM_ENVIRONMENT_COLUMNS))) 
      state = state + NORTH_BASE * WALL ; /* NORTH is a wall */ 
    else 
      if (environment[n_row][n_column].contains_soda_can) 
	state = state + NORTH_BASE * CAN;    /* NORTH cell has a can */ 
      else
	state = state + NORTH_BASE * EMPTY;  /* NORTH cell is empty */ 


#if DEBUG
    printf("After north, state is %d\n", state); 
#endif


    /* SOUTH */ 
    s_row = environment[robby_row][robby_column].S_row; 
    s_column = environment[robby_row][robby_column].S_column; 

    if (((s_row < 0) || (s_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((s_column < 0) || (s_column >= NUM_ENVIRONMENT_COLUMNS)))   
      state = state + SOUTH_BASE * WALL;     /* SOUTH is a wall */ 

    else 
      if (environment[s_row][s_column].contains_soda_can)
	state = state + SOUTH_BASE * CAN;    /* SOUTH cell has a can */ 
      else
	state = state + SOUTH_BASE * EMPTY;  /* SOUTH cell is empty */ 

#if DEBUG
    printf("After south, state is %d\n", state); 
#endif

    /* EAST */ 
    e_row = environment[robby_row][robby_column].E_row; 
    e_column = environment[robby_row][robby_column].E_column; 

    if (((e_row < 0) || (e_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((e_column < 0) || (e_column >= NUM_ENVIRONMENT_COLUMNS))) 
      state = state + EAST_BASE * WALL;     /* EAST is a wall */ 
    else 
      if (environment[e_row][e_column].contains_soda_can)
	state = state + EAST_BASE * CAN;    /* EAST cell has a can */ 
      else
	state = state + EAST_BASE * EMPTY;  /* EAST cell is empty */ 

#if DEBUG
    printf("After east, state is %d\n", state); 
#endif

    /* WEST */ 
    w_row = environment[robby_row][robby_column].W_row; 
    w_column = environment[robby_row][robby_column].W_column; 

    if (((w_row < 0) || (w_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((w_column < 0) || (w_column >= NUM_ENVIRONMENT_COLUMNS))) 
      state = state + WEST_BASE * WALL;     /* WEST is a wall */ 
    else 
      if (environment[w_row][w_column].contains_soda_can)
	state = state + WEST_BASE * CAN;    /* WEST cell has a can */ 
      else
	state = state + WEST_BASE * EMPTY;  /* WEST cell is empty */ 

#if DEBUG
    printf("After west, state is %d\n", state); 
#endif

    /* CENTER */ 
    c_row = environment[robby_row][robby_column].C_row;
    c_column = environment[robby_row][robby_column].C_column; 

    /* Skip test for wall, since center cell is not a wall. */ 

    if (environment[c_row][c_column].contains_soda_can)
      state = state + CAN;    /* CENTER cell has a can */ 
    else
      state = state + EMPTY;  /* CENTER cell is empty */ 

#if DEBUG
    printf("After center, state is %d\n", state); 
#endif

    action = chrom[state]; 

#if DEBUG
    printf("Action is %d\n", action); 
#endif


    /* Perform action corresponding to state */

#if DEBUG
    printf("Before perform action: current performance points: %d\n", performance_points); 
#endif

    performance_points = performance_points + perform_action(action); 
#if DEBUG
    printf("After perform action: current performance points: %d\n", performance_points); 
#endif

  }

#if DEBUG
  printf("Performance: %d\n", performance_points); 
#endif

  return (performance_points); 

}

/***************************************************************************/

int perform_action(int action)
{
  /* Perform given action, and return performance points */

  int n_row, n_column, s_row, s_column, e_row, e_column, w_row, w_column, c_row, c_column; 

  int reward, random_action; 

  double r; 

  reward = 0; 

#if DEBUG
  printf("In perform_action with action: %d\n", action); 
#endif

  /* If robby hits a wall, he bounces back to where he was, and loses 10 points.  
   * If robby succeeds in picking up a can, he wins 1 point.  
   * If robby tries to pick up a can in an empty space, he loses 1 point. */ 

  n_row = environment[robby_row][robby_column].N_row; 
  n_column = environment[robby_row][robby_column].N_column; 
  s_row = environment[robby_row][robby_column].S_row; 
  s_column = environment[robby_row][robby_column].S_column; 
  e_row = environment[robby_row][robby_column].E_row; 
  e_column = environment[robby_row][robby_column].E_column; 
  w_row = environment[robby_row][robby_column].W_row; 
  w_column = environment[robby_row][robby_column].W_column; 
  c_row = environment[robby_row][robby_column].C_row;
  c_column = environment[robby_row][robby_column].C_column; 

  switch (action) {

  case MOVE_NORTH: 

#if DEBUG
    printf("Action is NORTH\n"); 
#endif

    if (((n_row < 0) || (n_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((n_column < 0) || (n_column >= NUM_ENVIRONMENT_COLUMNS)))   /* Wall */ 
      reward = WALL_PENALTY; 
    else
      robby_row = robby_row - 1; 
    break; 

  case MOVE_SOUTH: 

#if DEBUG
    printf("Action is SOUTH\n"); 
#endif

    if (((s_row < 0) || (s_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((s_column < 0) || (s_column >= NUM_ENVIRONMENT_COLUMNS)))   /* Wall */ 
      reward = WALL_PENALTY; 
    else 
      robby_row = robby_row + 1; 
    break; 

	  
  case MOVE_EAST: 

#if DEBUG
    printf("Action is EAST\n"); 
#endif

    if (((e_row < 0) || (e_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((e_column < 0) || (e_column >= NUM_ENVIRONMENT_COLUMNS)))   /* Wall */ 
      reward = WALL_PENALTY; 
    else 
      robby_column = robby_column + 1; 
    break; 

  case MOVE_WEST: 

#if DEBUG
    printf("Action is WEST\n"); 
#endif

    if (((w_row < 0) || (w_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((w_column < 0) || (w_column >= NUM_ENVIRONMENT_COLUMNS)))   /* Wall */ 
      reward = WALL_PENALTY; 
    else 
      robby_column = robby_column - 1; 
    break; 

  case STAY_PUT: 

#if DEBUG
    printf("Action is STAY_PUT\n"); 
#endif
      /* Do nothing */
    break; 

  case PICK_UP: 

#if DEBUG
    printf("Action is PICK_UP\n"); 
#endif

    if (environment[robby_row][robby_column].contains_soda_can) {
      reward = CAN_REWARD; 
      environment[robby_row][robby_column].contains_soda_can = FALSE; 
    }
    else
      reward = CAN_PENALTY; 
    break; 

  case RANDOM_MOVE: 

#if DEBUG
    printf("Action is RANDOM_MOVE\n"); 
#endif
    
    r = knuth_random(); 
    random_action = (int) (r * (MOVE_WEST + 1)); 
    
    /* random_action is 0, 1, 2, or 3 */ 

#if DEBUG 
    printf("Random action: %d\n", random_action); 
    printf("About to call perform_action with that action\n"); 
#endif

    reward = perform_action(random_action); 
    break; 
  }

#if DEBUG
  printf("Reward %d\n", reward); 
#endif

  return(reward); 
}
  
  
/***************************************************************************/

void read_chrom()
{
  int i;
  
  char *chrom_string; 
  
  chrom_string = (char *) malloc(CHROM_LENGTH * sizeof(char));
  
  printf("Chromosome: ");
  scanf("%s", chrom_string); 
  
  
  for (i = 0; i < CHROM_LENGTH; i++) {
    if (chrom_string[i] == '0') chrom[i] = MOVE_NORTH;
    else if (chrom_string[i] == '1') chrom[i] = MOVE_SOUTH;
    else if (chrom_string[i] == '2') chrom[i] = MOVE_EAST;
    else if (chrom_string[i] == '3') chrom[i] = MOVE_WEST;
    else if (chrom_string[i] == '4') chrom[i] = STAY_PUT;
    else if (chrom_string[i] == '5') chrom[i] = PICK_UP; 
    else if (chrom_string[i] == '6') chrom[i] = RANDOM_MOVE; 
    else {
      printf("Non 0-6 in chromosome; exiting\n");
      exit(0);
    }
  }
  
}


/***************************************************************************/

double knuth_random()
     /* Knuth's subtractive-method portable random number generator, described in 
      * the first edition of Numerical Recipes in C, p. 212.  Returns a double between 0 and 1. 
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

/* Initializes the environment */
void init_environment()
{
  int row, column; 

#if FITNESS_DEBUG
  printf("About to initialize environment\n"); 
#endif

  /* Initialize the environment */
  for (row=0; row < NUM_ENVIRONMENT_ROWS; row++)
    for (column=0; column < NUM_ENVIRONMENT_COLUMNS; column++) {
      environment[row][column].C_row = row; 
      environment[row][column].C_column = column; 
      environment[row][column].N_row = row-1; 
      environment[row][column].N_column = column; 
      environment[row][column].S_row = row+1; 
      environment[row][column].S_column = column; 
      environment[row][column].E_row = row; 
      environment[row][column].E_column = column+1; 
      environment[row][column].W_row = row; 
      environment[row][column].W_column = column-1; 
      environment[row][column].contains_soda_can = (knuth_random() <= 0.5) ? TRUE : FALSE;
    }

  /* Put robby at starting square 0,0. */ 
  
  robby_row = 0; 
  robby_column = 0; 

#if FITNESS_DEBUG
  printf("About to print the environment\n"); 
  print_environment(); 
#endif

}
  
/***************************************************************************/

void print_environment()
{
  int row, column; 

  for (row=0; row < NUM_ENVIRONMENT_ROWS; row++) {
    for (column=0; column < NUM_ENVIRONMENT_COLUMNS; column++) {
      printf("(%d, %d): ", row, column); 
      if (environment[row][column].contains_soda_can) {
	printf ("C"); 
	if ((row == robby_row) && (column == robby_column))
	  printf("R"); 
      }
      else 
	if ((row == robby_row) && (column == robby_column))
	  printf("R"); 
	else  printf ("E"); 
      printf("    "); 
    }
  printf("\n"); 
  }
}

/***************************************************************************/

void print_a_chromosome(int *chrom)
/* Prints out a chromosome -- for debugging purposes */ 
{
    int i;

    for (i = 0; i < CHROM_LENGTH; i++)
      printf("%d", chrom[i]); 

    printf("\n");
}

/***************************************************************************/

