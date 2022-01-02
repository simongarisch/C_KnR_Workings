/***************************************************************************/
/*                                                                         */
/*                              RUNGA.C                                    */
/*                                                                         */
/*                      Routines for running GA                            */
/*                                                                         */
/***************************************************************************/

#include    "definitions.h"
#include    "globals.h"
#include    "prototypes.h"
#include    "params.h"

/***************************************************************************/

runga(int argc, char *argv[])
{  
  double fitness_sum, current_fitness=0.0, fitness_sum_squares, weight_sum; 

  int current_chrom, i, j, k, parent1_index, parent2_index, 
    next_pop_index, chrom, fitness;
  
  ga_rec parent1, parent2;
  
  /********************/
  /*  initialization  */
  /********************/
  
#if RUNGA_DEBUG
  printf("In runga\n"); 
#endif
  
  malloc_current_pop();
  malloc_next_pop();
  
#if RUNGA_DEBUG
  printf("About to generate population\n"); 
#endif
  
  current_generation = 1; 
  
  generate_population();
  
#if RUNGA_DEBUG
  printf("About to run for %d generations\n", NUM_GENERATIONS); 
#endif
  
  printf("Running the \"Robby the Robot\" genetic algorithm\n"); 

  for (current_generation=1; current_generation <= NUM_GENERATIONS; current_generation++) {
    fitness_sum = 0; 
    fitness_sum_squares = 0; 
    fitness_std_dev = 0;

    printf("Generation %d\n", current_generation); 
    
    
#if RUNGA_DEBUG
    printf("About to compute fitness of population\n"); 
#endif
    
    /* Compute the fitness of each individual */
    for (current_chrom = 0; current_chrom < POP_SIZE; 
	 current_chrom++)  {
      
#if RUNGA_DEBUG
      printf("\nAbout to compute fitness of chrom %d\n",current_chrom); 
#endif
      
      current_fitness = 
	current_pop[current_chrom].fitness = 
	calc_fitness(current_pop[current_chrom].chrom, current_chrom);
      
      fitness_sum += current_fitness;
      fitness_sum_squares += current_fitness * current_fitness; 
      
    } /* End of fitness calculation for this generation */
    
#if RUNGA_DEBUG
    printf("About to compute fitness statistics\n"); 
#endif
    
    /* Compute mean fitness */
    fitness_mean = fitness_sum / POP_SIZE;
    
    /* Compute standard deviation */
    fitness_std_dev 
      = sqrt((fitness_sum_squares - 
	      (double) (fitness_sum * fitness_sum) / POP_SIZE)
	     / POP_SIZE);
    
#if RUNGA_DEBUG
    printf("About to sort population\n"); 
#endif
    
    sort_population(); 
    
#if RUNGA_DEBUG
    printf("Here is the population\n"); 
#endif
    
#if RUNGA_DEBUG 
    print_current_population(); 
#endif
    
#if RUNGA_DEBUG 
    printf("About to do snapshots\n"); 
#endif
    
    
    if (SHORT_PRINT)
      short_snapshot();
    
    if (BEST_PRINT) {
      best_snapshot();
    }

    if (LONG_PRINT) 
      if ((current_generation == 1) 
	  || (current_generation == 50) 
	  || (current_generation == 200) 
	  || (current_generation == 500) 
	  || (current_generation == 1000)) 
	long_snapshot();
    
#if RUNGA_DEBUG 
    printf("About to reproduce, crossover, mutate \n"); 
#endif
    
    
    /* Assign weights to be used in selection */
    assign_weights_to_population(); 
    
    weight_sum = 0.0; 
    
    
    for (i=0; i < POP_SIZE; i++)
      weight_sum += current_pop[i].weight; 
    
#if RUNGA_DEBUG 
    printf("About to do selection \n"); 
#endif
    
    /* Select parents (with replacement) and create offspring via 
     * crossover and mutation
     */
    
    next_pop_index = 0;  /* Index for where to put offspring in next_pop */
    
    
    for (i=0; i < POP_SIZE/2; i++) { /* Create next population */
      
#if RUNGA_DEBUG
      printf("FOR DEBUGGING 4: Here is the current population\n"); 
      print_current_population(); 
      printf("\n\n"); 
#endif
      
      
#if RUNGA_DEBUG 
      printf("About to run roulette wheel to choose two parents \n"); 
#endif
      
      
      parent1_index = roulette_wheel(weight_sum);
      parent2_index = roulette_wheel(weight_sum);
      
      
#if RUNGA_DEBUG 
      printf("Parent1_index: %d, Parent2_index: %d\n", parent1_index, parent2_index); 
      printf("Here are the chromosomes: \n"); 
      print_a_chromosome(current_pop[parent1_index].chrom); 
      printf("\n"); 
      print_a_chromosome(current_pop[parent2_index].chrom); 
      printf("\n"); 
      
      printf("Before perform crossover and mutation\n"); 
#endif
      
      
      perform_crossover_and_mutation(parent1_index,parent2_index, 
				     next_pop_index);
#if RUNGA_DEBUG 
      printf("After perform crossover and mutation\n"); 
#endif
      
      next_pop_index += 2;
    }
    
    update_population();
    
  }
	 	 

  free(current_pop);
  free(next_pop);
}
  
  
/***************************************************************************/

print_current_population()
{
  int    a, b;
  
  printf("\nCurrent population: \n");
  printf("generation: %d\n", current_generation);
  
  for (a = 0; a < POP_SIZE; a++) {
    print_id(stdout, current_pop[a].id, current_pop[a].generation);
    printf("\t"); 
    for (b = 0; b < CHROM_LENGTH; b++) 
      printf("%d", current_pop[a].chrom[b]); 
    printf("\t%f",current_pop[a].fitness); 
    printf("\n"); 
  }
}

/***************************************************************************/

print_next_population() 
{
  int    a, b;
  
  printf("\nNext population: \n");
  printf("generation: %d\n", current_generation);
  
  for (a = 0; a < POP_SIZE; a++) {
    print_id(stdout, next_pop[a].id, next_pop[a].generation);
    for (b = 0; b < CHROM_LENGTH; b++) 
      printf("%d", next_pop[a].chrom[b]); 
    printf("\n"); 
  }
  printf("\n");
}

/***************************************************************************/

/* Generates POP_SIZE 243-character chromosomes.  Each "character"
   (really, an integer in [0,5]) gives an action (go-north, go-south,
   go-east, go-west, go-center, pick-up) corresponding to the current
   neighborhood state of the robot, where a state is "NSEWC" (contents
   of North, South, East, West, Center).  The content of a cell  is
   empty = 0, can = 1, or wall = 2.
*/

generate_population()
{
  register int    i, j;
  double increment, ran; 
  
  increment = 1/ (double) NUM_ACTIONS; 

  for (i = 0; i < POP_SIZE; i++)  {
    for (j = 0; j < CHROM_LENGTH; j++) {
      ran = knuth_random(); 
      if (ran <= increment)
	current_pop[i].chrom[j] = MOVE_NORTH;
      else if (ran <= (increment * 2)) 
	current_pop[i].chrom[j] = MOVE_SOUTH;
      else if (ran <= (increment * 3)) 
	current_pop[i].chrom[j] = MOVE_EAST; 
      else if (ran <= (increment * 4)) 
	current_pop[i].chrom[j] = MOVE_WEST; 
      else if (ran <= (increment * 5)) 
	current_pop[i].chrom[j] = STAY_PUT; 
      else if (ran <= (increment * 6)) 
	current_pop[i].chrom[j] = PICK_UP; 
      else 
	current_pop[i].chrom[j] = RANDOM_MOVE; 
    }
    
    current_pop[i].generation = 1;
    current_pop[i].id = i;
    current_pop[i].fitness = -99.99;
    current_pop[i].weight = -99.99; 
  }
}

/***************************************************************************/

assign_weights_to_population()
{
  register int i; 
  
  if (strcmp (SELECTION_METHOD, "elite") == 0)
    assign_elite_weights(); 
  else if (strcmp (SELECTION_METHOD, "linear rank") == 0)
    assign_linear_rank_weights(); 
  else if (strcmp (SELECTION_METHOD, "pure rank") == 0)
    assign_pure_rank_weights(); 
  else if (strcmp (SELECTION_METHOD, "fitness proportionate") == 0)
    assign_fitness_proportionate_weights(); 
  else if (strcmp (SELECTION_METHOD, "sigma scaling") == 0)
    assign_sigma_scaling_weights(); 
  else {
    fprintf(stderr, "ERROR: invalid selection method\n");
    exit(1); 
  }
  
  /* Check to make sure weights aren't negative */
  for (i=0; i < POP_SIZE; i++) {
    /*     printf("%d.%d: %f\n", current_generation, current_pop[i].id, current_pop[i].weight); */ 
    if (current_pop[i].weight < 0) { 
      fprintf(stderr, "Error: In assign_linear_rank_weights with %d.%d's weight < 0\n", 
	      current_generation, current_pop[i].id); 
      exit(1); 
    }
  }
}

/***************************************************************************/

assign_elite_weights()
{
  int i;
  
  for (i=0; i < NUM_ELITE; i++)
    current_pop[i].weight = 1.0; /* Equal weight to each elite string */
  
  for (i=NUM_ELITE; i < POP_SIZE; i++)
    current_pop[i].weight = 0.0; 
}

/***************************************************************************/

assign_linear_rank_weights()
{
  int i;
  
  current_pop[0].weight = RANK_MAX_WEIGHT; 
  
  for (i=0; i < POP_SIZE; i++)
    current_pop[i].weight = RANK_MAX_WEIGHT 
      - ((2.0 * i * (RANK_MAX_WEIGHT-1)) 
	 / POP_SIZE); 
  
}
/***************************************************************************/

assign_pure_rank_weights()
{
  int i;
  
  for (i=0; i < POP_SIZE; i++) {
    current_pop[i].weight = (double) (POP_SIZE - i); 
    /*     printf("gen = %d, i = %d, weight = %f\n", current_generation, i, current_pop[i].weight);  */
  }
}
/***************************************************************************/


/* assign_linear_rank_weights()
{
  int i;
  
  current_pop[0].weight = RANK_MAX_WEIGHT; 
  
  for (i=0; i < POP_SIZE; i++)
    current_pop[i].weight = POP_SIZE - i; 
}*/ 

/***************************************************************************/

assign_fitness_proportionate_weights()
{
  int i;
  
  for (i=0; i < POP_SIZE; i++)
    if (current_pop[i].fitness > 0)
      current_pop[i].weight = current_pop[i].fitness;
    else /* Assign small weight */
      current_pop[i].weight = 0.001; 
}

/***************************************************************************/

assign_sigma_scaling_weights()
{
  int i; 
  
  for (i=0; i < POP_SIZE; i++) {
    if (fitness_std_dev < 0.0001)
      current_pop[i].weight = 1; /* all equal weights if std. dev. zero or 
				    very low */
    else
      current_pop[i].weight = 1 + ((current_pop[i].fitness - fitness_mean) 
				   / (2 * fitness_std_dev));
    
    if (current_pop[i].weight < 0)
      current_pop[i].weight = 0.0;
    
    if (SIGMA_SCALING_MAX_WEIGHT > 0) {
      if (current_pop[i].weight > SIGMA_SCALING_MAX_WEIGHT)
	current_pop[i].weight = SIGMA_SCALING_MAX_WEIGHT; 
    }
  }
}

/***************************************************************************/

int roulette_wheel(double weight_sum)
     /* Returns index of chosen parent. */
{
  int i, index=-1; 
  double r, sum=0;
  
  if (weight_sum == 0) {
    fprintf(stderr, "Error: In roulette_wheel with weight_sum = 0\n"); 
    exit(1);
  }
  
  r = knuth_random() * weight_sum; 
  
  while (sum < r) {
    index++;
    sum += current_pop[index].weight;
  }
  
  return(index); 
  
}

/***************************************************************************/


