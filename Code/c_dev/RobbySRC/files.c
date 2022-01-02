/***************************************************************************/
/*                                FILES.C                                  */
/*                                                                         */
/*                              I/O routines                               */
/*                                                                         */
/***************************************************************************/

#include    <stdio.h>
#include    <time.h>
#include    "definitions.h"
#include    "globals.h"
#include    "prototypes.h"

FILE
*my_open(char *file_name, open_mode mode)
/* Opens files with error checking */
{
   FILE *mfp;
   int file_type;
 
   switch (mode)
   {
    case append:
      mfp = fopen(file_name, "a"); break;
    case read:
      mfp = fopen(file_name, "r"); break;
    case write:
      mfp = fopen(file_name, "w"); break;
   }
 
   if (mfp == NULL)
   {
      fprintf(stderr, "Error: Unable to access %s\n", file_name);
      exit(1);
   }
 
   return(mfp);
}

/***************************************************************************/

void print_id(FILE *ofp, int id, int gen)
/* Prints id for an individual in the population, with leading zeros */
{
  int i, id_length, num_zeros; 
  if (id == 0) id_length = 1;
  else id_length = (int) log10(id) + 1; 
  num_zeros = max_id_length - id_length; 
  fprintf(ofp, "%d.", gen); 
  for (i=0; i < (max_id_length - id_length); i++)
    fprintf(ofp, "0"); 
  fprintf(ofp, "%d",id); 
}

/***************************************************************************/

void write_header()
/* Writes out the header file for a run of the GA */
{
    char   *suffix = ".header", *file;
    /*    char   *hostname; */
    int    length = 0;
    FILE    *ofp;

    length += 10;
    length += strlen(suffix);

    file = (void *) my_malloc(length * sizeof(char));

    sprintf(file, "%d%s", run_num, suffix);

    ofp = my_open(file, append);

    free(file);

    fprintf(ofp, "# RUN NUMBER: %d\n", run_num);
    fprintf(ofp, "# RANDOM SEED: %ld\n", ran_seed);

    fprintf(ofp, "# FITNESS FUNCTION: %s\n", FITNESS_FUNCTION_NAME);
    fprintf(ofp, "# NUM ENVIRONMENT ROWS: %d\n", NUM_ENVIRONMENT_ROWS);
    fprintf(ofp, "# NUM ENVIRONMENT COLUMNS: %d\n", NUM_ENVIRONMENT_COLUMNS);
    fprintf(ofp, "# WALL_PENALTY: %d\n", WALL_PENALTY);
    fprintf(ofp, "# CAN_REWARD: %d\n", CAN_REWARD);
    fprintf(ofp, "# CAN_PENALTY: %d\n", CAN_PENALTY);
    fprintf(ofp, "# NUM_MOVES: %d\n", NUM_MOVES);

    fprintf(ofp, "# SELECTION METHOD: %s\n", SELECTION_METHOD);
    fprintf(ofp, "# CHROM LENGTH: %d\n", CHROM_LENGTH);
    fprintf(ofp, "# POPULATION SIZE: %d\n", POP_SIZE);
    fprintf(ofp, "# NUM GENERATIONS: %d\n", NUM_GENERATIONS);
    

    if (strcmp(SELECTION_METHOD, "elite") == 0)
	fprintf(ofp, "# NUM ELITE: %d\n", NUM_ELITE);

    if (strcmp(SELECTION_METHOD, "linear rank") == 0)
	fprintf(ofp, "# RANK MAX WEIGHT: %f\n", RANK_MAX_WEIGHT);

    if (strcmp(SELECTION_METHOD, "sigma scaling") == 0)
	fprintf(ofp, "# SIGMA SCALING MAX WEIGHT : %f\n", SIGMA_SCALING_MAX_WEIGHT);
    fprintf(ofp, "# CROSSOVER RATE: %f\n", CROSSOVER_RATE);
      
    fprintf(ofp, "# MUTATION RATE: %f\n", MUTATION_RATE);

    fclose(ofp);
}

/***************************************************************************/

void short_snapshot()
/* Writes out a line of the .short file for a run of the GA.  Each
 *  line summarizes a generation. 
 */
{
    char   *suffix = ".short", *file;
    int    length = 0;
    double  best_fitness, pop_fitness, std_dev, elite_fitness, elite_std_dev;
    FILE   *ofp;

    length += strlen(OUTPUT_DIR);
    length += 10;
    length += strlen(suffix);

    file = (void *)my_malloc(length * sizeof(char));
    sprintf(file, "%s%d%s", OUTPUT_DIR, run_num, suffix);
    ofp = my_open(file, append);
    free(file);

    if (current_generation == 1)  
        fprintf(ofp, "# %s\t%s\n", 
		     "gen","best fitness");

    fprintf(ofp, "   %d\t %4.1f\n", 
	    current_generation, 
	    current_pop[0].fitness);

    fclose(ofp);
}

/***************************************************************************/

void best_snapshot() 
/* Writes out the best chromosome at the current generation. 
 */
{
    int    i, j, length = 0;
    FILE   *ofp;
    char   *suffix = ".best", *file;
    struct element *new_top;
    double  tmp;

    length += strlen(OUTPUT_DIR);
    length += 10;
    length += strlen(suffix);
    
    file = (void *)my_malloc(length * sizeof(char));
    sprintf(file, "%s%d%s", OUTPUT_DIR, run_num, suffix);
    ofp = my_open(file, append);
    free(file);

    fprintf(ofp, "%4d ", current_generation);
    print_id(ofp, current_pop[0].id, current_pop[0].generation); 
    fprintf(ofp, " %8.2f\t", current_pop[0].fitness);

    for (j = 0; j < CHROM_LENGTH; j++)
      fprintf(ofp, "%d", current_pop[0].chrom[j]);

    fprintf(ofp, "\n");

    fclose(ofp);
}


/***************************************************************************/

void long_snapshot() 
/* Writes out a line of the .long file for a run of the GA.  Each
 *  line gives details for a generation. 
 */
{
    int    i, j, length = 0;
    FILE   *ofp;
    char   *suffix = ".long", *file;
    struct element *new_top;
    double  tmp;

    length += strlen(OUTPUT_DIR);
    length += 10;
    length += strlen(suffix);
    
    file = (void *)my_malloc(length * sizeof(char));
    sprintf(file, "%s%d%s", OUTPUT_DIR, run_num, suffix);
    ofp = my_open(file, append);
    free(file);

    for (i = 0; i < POP_SIZE; i++) 
    {
        fprintf(ofp, "%4d ", current_generation);
	print_id(ofp, current_pop[i].id, current_pop[i].generation); 
        fprintf(ofp, " %8.2f\t", current_pop[i].fitness);

        for (j = 0; j < CHROM_LENGTH; j++)
            fprintf(ofp, "%d", current_pop[i].chrom[j]);

	fprintf(ofp, "\n");

    }
    fclose(ofp);
}


/***************************************************************************/

int serial_num()
/* The file run_num contains an integer value which serves as
 * a run number for each run.  This routine increments 
 * this value each time the routine is run, and returns the value as an int. 
 */
{
  int     num, length = 0;
  FILE    *ifp;
  char    *file, *name = "run_num";

  length += strlen(RUN_NUM_DIR);
  length += strlen(name);

  file = (void *)my_malloc(length * sizeof(char));
  sprintf(file, "%s%s", RUN_NUM_DIR, name);
    
  /* open and read the file, if it exists */
  if ((ifp = fopen(file, "r+")) == NULL)  
    {
      fprintf(stderr, "ERROR: Unable to read %s\n", file);
      exit(1);
    }

  
  /* Read run_num or return error */
  if (fscanf(ifp, "%d", &num) == EOF)
    printf("Error: run_num not read\n"); 

  /* reset pointer to the begining of the file and write incremented value */
  fseek(ifp, 0, 0);

  fprintf(ifp, "%d", num + 10);

  fclose(ifp);
  free(file);
  return num;
}

/***************************************************************************/



