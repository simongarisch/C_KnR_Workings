/***************************************************************************/
/*                                                                         */
/*                              MAIN.C                                     */
/*                                                                         */
/*                           Main program                                  */
/*                                                                         */
/***************************************************************************/

#include    "definitions.h"
#include    "globals.h"
#include    "prototypes.h"
#include    "params.h"


main(int argc, char *argv[])
{
  int i,j;
  long m, n, k; 

  if (argc > 1)
    parse_command_line(argc, argv);
  
  /* Initialize the parameters */
  init_params(PARAM_FILE_NAME);

#if MAIN_DEBUG
  printf("In main\n"); 
#endif

  /* Run GA */
  for (i=0; i < NUM_RUNS; i++) {

    /* Seed random number generator */
    ran_seed = ran_seed_flag ? ran_seed_flag : 0;
    ran_seed = seed_random(ran_seed_flag);
 
    run_num = serial_num();


#if MAIN_DEBUG
    printf("About to write header\n"); 
#endif

    write_header();   

#if MAIN_DEBUG
    printf("Run_num is %d\n", run_num); 
    printf("About to init fitness function\n"); 
#endif

    /* Initialize the fitness function */
    init_fitness_function();


#if MAIN_DEBUG
    printf("About to runga\n"); 
#endif

    runga(argc, argv); 

  }

}  

/**********************************************************************/

void init_params(char* fname)
/* Initializes parameters for this run (or set of runs) of the GA */
{
  int n; 

  if (!read_param_file(fname))
     exit(1);

  FITNESS_FUNCTION_NAME = string_param("FITNESS_FUNCTION_NAME");
  WALL_PENALTY = int_param("WALL_PENALTY"); 
  CAN_REWARD = int_param("CAN_REWARD"); 
  CAN_PENALTY = int_param("CAN_PENALTY"); 
  NUM_MOVES = int_param("NUM_MOVES"); 
  NUM_ENVIRONMENTS_FOR_FITNESS = int_param("NUM_ENVIRONMENTS_FOR_FITNESS"); 

  NUM_RUNS = int_param("NUM_RUNS");
  SELECTION_METHOD = string_param("SELECTION_METHOD");
  POP_SIZE = int_param("POP_SIZE");
  NUM_ELITE = int_param("NUM_ELITE");
  NUM_GENERATIONS = int_param("NUM_GENERATIONS");
  CHROM_LENGTH = int_param("CHROM_LENGTH");
  MUTATION_RATE = double_param("MUTATION_RATE");
  CROSSOVER_SITES = int_param("CROSSOVER_SITES");
  CROSSOVER_RATE = double_param("CROSSOVER_RATE");
  RANK_MAX_WEIGHT = double_param("RANK_MAX_WEIGHT");
  SIGMA_SCALING_MAX_WEIGHT = double_param("SIGMA_SCALING_MAX_WEIGHT");
  RUN_NUM_DIR = string_param("RUN_NUM_DIR");
  OUTPUT_DIR = string_param("OUTPUT_DIR");
  SNAPSHOT_INTERVAL = int_param("SNAPSHOT_INTERVAL");
  SHORT_PRINT = bool_param("SHORT_PRINT");
  BEST_PRINT = bool_param("BEST_PRINT");
  LONG_PRINT = bool_param("LONG_PRINT");
 
  max_id_length = (int) log10(POP_SIZE) + 1; 
  
}

/***************************************************************************/

void parse_command_line(int argc, char *argv[])
/* Reads and parses the command line for command-line options */
{
    int   length;
    
    if (argc > 3) {
	fprintf(stderr, "  USAGE:  %s <options>\n", argv[0]);
	fprintf(stderr, "\n");
	fprintf(stderr, "OPTIONS:  -r <path/filename> - restarts a run\n");
	fprintf(stderr, "          -s <(int)ran seed> - seeds with an int other than <run_num>\n");
	exit(0);
    }
    else if (strcmp(argv[1], "-s") == 0) {
	ran_seed_flag = atol(argv[2]);
	fprintf(stderr, "seeding with %ld\n", ran_seed_flag);
    }
    else {
	fprintf(stderr, "  USAGE:  %s <options>\n", argv[0]);
	fprintf(stderr, "\n");
	fprintf(stderr, "OPTIONS:  -r <path/filename> - restarts a run\n");
	fprintf(stderr, "          -s <(int)ran seed> - seeds with an int other than <run_num>\n");
	exit(0);
    }
}
/***************************************************************************/






