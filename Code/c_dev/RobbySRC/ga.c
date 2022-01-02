/***************************************************************************/
/*                                                                         */
/*                           GA.C                                          */
/*                                                                         */
/*                        GA routines.                                     */
/*                                                                         */
/***************************************************************************/


#include    "definitions.h"
#include    "globals.h"
#include    "prototypes.h"

/***************************************************************************/

void perform_crossover_and_mutation(int parent1_index, int parent2_index, 
			       int nextpopindex)
/* Performs crossover between the given parents, and mutates the offspring */
{
    int    i,j, toggle, max_parent, site; 
    int   *crossover_template, *child_1, *child_2;
    struct element *new_top;
    
#if GA_DEBUG
    printf("In` perform_crossover_and_mutation with parent index: %d, %d\n", 
	   parent1_index, parent2_index); 

    print_a_chromosome(current_pop[parent1_index].chrom); 
    printf("\n"); 
    print_a_chromosome(current_pop[parent2_index].chrom); 
#endif

    child_1 = (void *)my_malloc(CHROM_LENGTH * sizeof(int));
    child_2 = (void *)my_malloc(CHROM_LENGTH * sizeof(int));
    crossover_template = (void *)my_malloc(CHROM_LENGTH * sizeof(int));

    /* initialize crossover_template */
    for (j = 0; j < CHROM_LENGTH; j++) 
	crossover_template[j] = ZERO;
      
    /* First decide whether or not to cross over */
    if (knuth_random() < CROSSOVER_RATE) {

#if GA_DEBUG
      printf("Decided to cross over\n"); 
#endif

      /* Put ones in the template array where there are crossover sites */
      for (j = 0; j < CROSSOVER_SITES; j++) {
	/* Definitely choose a site at which to cross over */
	site = (knuth_random() * (CHROM_LENGTH -1)) + 1;
	if (crossover_template[site]==ONE) 
	  j--;
	else
	    crossover_template[site] = ONE;
      }
    }
    else {

#if GA_DEBUG
      printf("Decided not to perform crossover\n"); 
#endif

      /* Make sure crossover template is all ZEROS */
      for (j=0; j < CHROM_LENGTH; j++)
	if (crossover_template[j] != ZERO) {

	  fprintf(stderr, "Error: Decided not to perform crossover, but crossover template has non-zero\n"); 

	  exit(1);
	}
    }

#if GA_DEBUG
    printf("Here is the crossover template\n"); 
    for (i=0; i < CHROM_LENGTH; i++)
      printf("%d", crossover_template[i]); 
    printf("\n"); 
#endif

    /* Begin crossing-over.  If it was decided not to cross over, then 
    * crossover_template is all zeros.  
     */
    
    toggle = 0;     /* this gets switched when we hit a crossover site */

    for (j = 0; j < CHROM_LENGTH; j++) {
      if (crossover_template[j]==ONE)
	toggle = toggle ? 0 : 1;
      if (toggle) 
	{
	  child_2[j] = current_pop[parent1_index].chrom[j];
	  child_1[j] = current_pop[parent2_index].chrom[j];
	}
      else  
	{
	  child_1[j] = current_pop[parent1_index].chrom[j];
	  child_2[j] = current_pop[parent2_index].chrom[j];
	}
    }

#if GA_DEBUG
    printf("After crossover (or not), here are the two children:\n"); 
    print_a_chromosome(child_1); 
    printf("\n"); 
    print_a_chromosome(child_2); 
#endif

    /* Perform mutation operator on the two */

    mutate_chromosome(child_1);

    mutate_chromosome(child_2);

#if GA_DEBUG
    printf("After mutation, here are the two children:\n"); 
    print_a_chromosome(child_1); 
    printf("\n"); 
    print_a_chromosome(child_2); 
    printf("\n We will put them at indices %d and %d\n", 
	   nextpopindex, nextpopindex+1); 
#endif

    
    /* We now have two fine children */

    /* Put child_1 in next_pop */
    for (j = 0; j < CHROM_LENGTH; j++) 
      next_pop[nextpopindex].chrom[j] = child_1[j]; 

    next_pop[nextpopindex].generation = current_generation+1;
    next_pop[nextpopindex].id = nextpopindex;
    
    nextpopindex++;

    /* Put child_2 in next_pop */
    for (j = 0; j < CHROM_LENGTH; j++)
      next_pop[nextpopindex].chrom[j] = child_2[j];
    
    next_pop[nextpopindex].generation = current_generation+1;
    next_pop[nextpopindex].id = nextpopindex; 
    
#if GA_DEBUG
    printf("Children have been put in next pop\n"); 
#endif


#if GA_DEBUG
    printf("About to free pointers\n"); 
#endif

    /* Free pointers */

    free(child_1);
    free(child_2);
    free(crossover_template);

}

/***************************************************************************/

void mutate_chromosome(int *chrom)
/* Mutate the given chromosome according to the mutation rate */ 
{
  int i; 
  double increment, ran; 

  increment = 1/ (double) NUM_ACTIONS; 

  for (i = 0; i < CHROM_LENGTH; i++) {
    if (knuth_random() < MUTATION_RATE) {
      /* Replace value with randomly chosen value */ 
      ran = knuth_random(); 
      if (ran <= increment)
	chrom[i] = MOVE_NORTH;
      else if (ran <= (increment * 2)) 
	chrom[i] = MOVE_SOUTH;
      else if (ran <= (increment * 3)) 
	chrom[i] = MOVE_EAST; 
      else if (ran <= (increment * 4)) 
	chrom[i] = MOVE_WEST; 
      else if (ran <= (increment * 5)) 
	chrom[i] = STAY_PUT; 
      else if (ran <= (increment * 6)) 
	chrom[i] = PICK_UP; 
      else 
	chrom[i] = RANDOM_MOVE; 
    }
   
  }
}

/***************************************************************************/

void update_population()
/* Move the new population to the current population */
{
  int i; 
  ga_rec   *temp;

    /* Now update populations */ 

    temp = next_pop;
    next_pop = current_pop;  /* This will get written over */
    current_pop = temp;  /* current_pop <- next_pop */

}

/***************************************************************************/

double mean_fitness()
/* Returns the mean of the fitness in current_pop */

{
    double total_fitness = 0.0;
    int   i;
    
    for (i = 0; i < POP_SIZE; i++)
        total_fitness = total_fitness + (current_pop[i].fitness);
    
    return (total_fitness / (double)POP_SIZE);
}

/***************************************************************************/

double fitness_stdev(double mean, int num_items)
/* Returns the standard deviation of the fitness in current_pop */
{
   double total_dev, diff;
   int i;

   if (num_items == 1) return(0);

   for (total_dev = 0.0, i = 0; i < num_items; i++)
   {
      diff = mean - current_pop[i].fitness;
      total_dev += diff * diff;
   }
   return(sqrt(total_dev/num_items));
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

int cmp_func(a, b)
   ga_rec *a, *b;
{
  if (b->fitness > a->fitness) return 1;
  else if (a->fitness > b->fitness) return -1;
  else return 0;
}

/***************************************************************************/

void sort_population() 
/* Sorts the population in order of fitness */
{
    qsort(current_pop, POP_SIZE, sizeof(ga_rec), cmp_func); 
}

/***************************************************************************/

