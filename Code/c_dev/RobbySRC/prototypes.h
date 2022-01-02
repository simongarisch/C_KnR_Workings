/***************************************************************************/
/*                                                                         */
/*                           PROTOTYPES.H                                  */
/*                                                                         */
/*                    Listing of all function names                        */
/*                                                                         */
/***************************************************************************/


/* main.c */
void init_params(char* fname);
void parse_command_line(int argc, char *argv[]); 

/* files.c */
/* FILE   *my_open();
void write_header(); 
void short_snapshot(); 
void long_snapshot(); 
int serial_num(); 
void print_id(FILE *ofp, int id, int gen); 
*/

/* ga.c   */
int cmp_func();
void sort_population(); 
void perform_crossover_and_mutation(int parent1_index, int parent2_index, 
				    int next_pop_index); 
void mutate_chromosome(int *chrom); 
void update_population(); 
double mean_fitness(); 
double fitness_stdev(double mean, int num_items); 
void print_a_chromosome(int *chrom); 

/* misc.c */
void   *my_malloc();
void malloc_current_pop();
void malloc_next_pop(); 

/* random_number_generation.c */
double knuth_random();
long seed_random(long seed); 

/* fitness.c */
void init_fitness_function(); 
void init_environment(); 
void cleanup_fitness_function();
void draw_environment(); 
double calc_fitness(); 
int calc_fitness_one_environment(int* chrom, int chrom_num); 
void print_environment(); 
int perform_action(int action); 
