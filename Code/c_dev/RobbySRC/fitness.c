/***************************************************************************/
/*                                FITNESS.C                                */
/*                                                                         */
/*                        Fitness function routines.                        */
/*                                                                         */
/***************************************************************************/

#include    "definitions.h"
#include    "prototypes.h"
#include    "globals.h"

/***************************************************************************/
void init_fitness_function()
{
  /* Right now this doesn't do anything */ 
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


double
calc_fitness(int* chrom, int chrom_num)
/* Fitness function: Environment is re-generated.  Chrom is run on
 *  environment for NUM_MOVES.  Fitness is number of fitness points it
 *  gets. */

{
  int environment_number, total_score = 0; 
  double fitness = 0.0; 

  /* Run this individual on NUM_ENVIRONMENTS_FOR_FITNESS different
     random enviornments.  Fitness is sum of fitness points. */ 


#if FITNESS_DEBUG
    printf("In calc_fitness with chrom \n"); 
    print_a_chromosome(chrom); 
#endif

#if FITNESS_DEBUG_SHORT
    printf("In calc_fitness with chrom \n"); 
    print_a_chromosome(chrom); 
#endif

    for (environment_number = 1; environment_number <= NUM_ENVIRONMENTS_FOR_FITNESS; environment_number ++) {

#if FITNESS_DEBUG
    printf("On Environment %d\n", environment_number); 
#endif

      total_score = total_score + calc_fitness_one_environment(chrom, chrom_num); 
    }

    fitness = (double) total_score / (double) NUM_ENVIRONMENTS_FOR_FITNESS;   /* average */ 


#if FITNESS_DEBUG
    printf("Fitness is: %f\n", fitness); 
#endif

#if FITNESS_DEBUG_SHORT
    printf("Fitness is: %f\n", fitness); 
#endif

    return (fitness); 

}

/***************************************************************************/

int
calc_fitness_one_environment(int* chrom, int chrom_num)
/* Environment is  randomly generated.  Chrom is run on
 *  environment for NUM_MOVES.  Function returns number of fitness points the chromosome
 *  gets. */

{
  int site, move_number, action, fitness_points = 0; 
  int n_row, n_column, s_row, s_column, e_row, e_column, w_row, w_column, c_row, c_column; 
  double robby_text_row_coord, robby_text_column_coord;  /* Where to draw robby */ 
  int state, smaller_state; 

  init_environment(); 

  /* Keep going for NUM_MOVES.  Fitness is how many cans were
   * collected. */ 


  for (move_number = 1; move_number <= NUM_MOVES; move_number++) {

#if FITNESS_DEBUG
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


#if FITNESS_DEBUG
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

#if FITNESS_DEBUG
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

#if FITNESS_DEBUG
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

#if FITNESS_DEBUG
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

#if FITNESS_DEBUG
    printf("After center, state is %d\n", state); 
#endif

    action = chrom[state]; 

#if FITNESS_DEBUG
    printf("State is %d, Action is %d\n", state, action); 
#endif


    /* Perform action corresponding to state */

#if FITNESS_DEBUG
    printf("Before perform action: current fitness points: %d\n", fitness_points); 
#endif

    fitness_points = fitness_points + perform_action(action); 
#if FITNESS_DEBUG
    printf("After perform action: current fitness points: %d\n", fitness_points); 
#endif

  }

#if FITNESS_DEBUG
  printf("Fitness: %d\n", fitness_points); 
#endif

  return (fitness_points); 

}

/***************************************************************************/

int perform_action(int action)
{
  /* Perform given action, and return fitness points */

  int n_row, n_column, s_row, s_column, e_row, e_column, w_row, w_column, c_row, c_column; 

  int reward, random_action; 

  double r; 

  reward = 0; 

#if FITNESS_DEBUG
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

#if FITNESS_DEBUG
    printf("Action is NORTH\n"); 
#endif

    if (((n_row < 0) || (n_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((n_column < 0) || (n_column >= NUM_ENVIRONMENT_COLUMNS)))   /* Wall */ 
      reward = WALL_PENALTY; 
    else
      robby_row = robby_row - 1; 
    break; 

  case MOVE_SOUTH: 

#if FITNESS_DEBUG
    printf("Action is SOUTH\n"); 
#endif

    if (((s_row < 0) || (s_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((s_column < 0) || (s_column >= NUM_ENVIRONMENT_COLUMNS)))   /* Wall */ 
      reward = WALL_PENALTY; 
    else 
      robby_row = robby_row + 1; 
    break; 

	  
  case MOVE_EAST: 

#if FITNESS_DEBUG
    printf("Action is EAST\n"); 
#endif

    if (((e_row < 0) || (e_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((e_column < 0) || (e_column >= NUM_ENVIRONMENT_COLUMNS)))   /* Wall */ 
      reward = WALL_PENALTY; 
    else 
      robby_column = robby_column + 1; 
    break; 

  case MOVE_WEST: 

#if FITNESS_DEBUG
    printf("Action is WEST\n"); 
#endif

    if (((w_row < 0) || (w_row >= NUM_ENVIRONMENT_ROWS)) 
	|| ((w_column < 0) || (w_column >= NUM_ENVIRONMENT_COLUMNS)))   /* Wall */ 
      reward = WALL_PENALTY; 
    else 
      robby_column = robby_column - 1; 
    break; 

  case STAY_PUT: 

#if FITNESS_DEBUG
    printf("Action is STAY_PUT\n"); 
#endif
      /* Do nothing */
    break; 

  case PICK_UP: 

#if FITNESS_DEBUG
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

#if FITNESS_DEBUG
    printf("Action is RANDOM_MOVE\n"); 
#endif
    
    r = knuth_random(); 
    random_action = (int) (r * (MOVE_WEST + 1)); 
    
    /* random_action is 0, 1, 2, or 3 */ 

#if FITNESS_DEBUG 
    printf("Random action: %d\n", random_action); 
    printf("About to call perform_action with that action\n"); 
#endif

    reward = perform_action(random_action); 
    break; 
  }

#if FITNESS_DEBUG
  printf("Reward %d\n", reward); 
#endif

  return(reward); 
}
