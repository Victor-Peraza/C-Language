/*  Victor Peraza                        */
/*  Lab 7 - Olympic woman's javelin throw  */

#define NCOMPETITORS 4
#define N_TRIES 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUT_FILENAME "lab7.out"
//#define OUT_FILENAME "lab7sample.out"

#define IN_FILENAME "lab7.dat"
//#define IN_FILENAME "lab7sample.dat"

//Enter your two structures here

typedef struct {
	char name[20];
	double tries[N_TRIES];
	double best_throw;
	double deviation;
} thrower_t;
	
typedef struct {
	double average_of_best;
	double winning_throw;
} stats_t;

 

/* FUNCTION PROTOTYPES */
/* get_data is a function to get and read data */
void get_data (char *filename,                      /* input  */ 
	       thrower_t throw_list[NCOMPETITORS] );  /* output */

/* open_out_file is a function to open the output file */
FILE * open_out_file (void);
		
/* get_stats is a function to do figure the best throw for each     */
/* thrower, compute the all-over average of the best throws, and     */
/* find the longest throw  on the track and each thrower's deviation */
/* from that winning long throw                                     */
void get_stats(thrower_t throw_list[NCOMPETITORS], /* in & out */
 	       stats_t *throw_stats);                  /* output   */

				
/*  print_all is a function to print things out.
    all of its arguments are input  */
void print_all(FILE * out_file,
	           thrower_t throw_list[NCOMPETITORS],
	           stats_t *throw_stats);				 
         

/*-----------------------------------------------------------*/
int main(void)
{
    thrower_t throw_list[NCOMPETITORS]; 
    stats_t throw_stats = {0.0, 0.0};	
	
    FILE * out_file;    /* file pointer for the output file  */
			
    out_file = open_out_file ();
	
    get_data(IN_FILENAME, throw_list);
 
    get_stats(throw_list, &throw_stats); 
		      
    print_all(out_file, throw_list, &throw_stats);
	
    return EXIT_SUCCESS;
}
/*----------------------------------------------------------*/
/* This function will open the output file and return the   */
/* file pointer name to the main program.                   */

FILE * open_out_file (void)
{
    FILE * outfile;

    outfile = fopen(OUT_FILENAME, "w");
    if (outfile == NULL)
    {
	printf("Error on fopen of %s \n", OUT_FILENAME);
	exit(EXIT_FAILURE);
    }
    fprintf(outfile, "\nVictor Peraza, Lab 7 output. \n");

    return outfile;
}

/*-----------------------------------------------------------*/
/* This function will open and read data into an array.      */
/* It will return the value of the real length of the array. */

void get_data (char *filename,                      /* input  */ 
	       thrower_t throw_list[NCOMPETITORS] )   /* output */
{
    int n, c;
    FILE *in_file;

    /* Open the data file and read in the array */
    in_file = fopen(filename, "r");
    if (in_file == NULL)
    {
	printf("Error on fopen of %s \n", filename);
	exit(EXIT_FAILURE);
    }
	
    /* Read the competitor's names first. */

    for (n=0; n < NCOMPETITORS; n++)	/* "n" for names of throwers */
    {
	/* "fgets" gets a string including the new line attached */
	fgets(throw_list[n].name, 19, in_file); 

    	/* strings require that the last character is NULL */
	throw_list[n].name[19] = 0;

	/* This code removes the attached new line */
	/* It will find the new line embedded in the name which it 
	   then sets to NULL.  */

	char *new_line_position = strchr(throw_list[n].name, '\n') ;
	if (new_line_position != NULL)
	    *new_line_position = 0;
    }

    /* Read the sets of tries */
    for (c=0; c < N_TRIES; c++) 
  	for(n = 0; n < NCOMPETITORS; n++)
	    fscanf(in_file, "%lf", &throw_list[n].tries[c]); 
	
    fclose(in_file);
    return;
}

/*-------------------------------------------------------------------*/
/* get_stats is a function to do figure the best throw for each      */
/* thrower, compute the all-over average of the best throws, and     */
/* find the longest throw  on the track and each thrower's deviation */
/* from the winning throw                                            */

void get_stats(thrower_t throw_list[NCOMPETITORS], /* in & out */
 	           stats_t *throw_stats) { 	     	   /* output   */
		
	int r,c;

	throw_stats->average_of_best = 0;
	throw_stats->winning_throw = 0;

	for (r = 0; r < NCOMPETITORS; r++) {
	
	throw_list[r].best_throw = throw_list[r].tries[0];

	for (c = 1; c < N_TRIES; c++) {
		if (throw_list[r].best_throw < throw_list[r].tries[c])
	
	throw_list[r].best_throw = throw_list[r].tries[c];
	
	}
	
	throw_stats->average_of_best += throw_list[r].best_throw;
	
	for (c = 0; c < N_TRIES; c++) {
		if (throw_list[r].best_throw > throw_stats-> winning_throw)
		
		throw_stats->winning_throw = throw_list[r].best_throw;
	}
}
	throw_stats->average_of_best = throw_stats->average_of_best / NCOMPETITORS;

	for (r = 0; r < NCOMPETITORS; r++) {
		throw_list[r].deviation = throw_stats->winning_throw - throw_list[r].best_throw;

	}
	return;
}








/*--------------------------------------------------------*/
/*  print_all is a function to print things out.
	all of its arguments are input  */

void print_all(FILE * out_file,
	       thrower_t throw_list[NCOMPETITORS],
	       stats_t *throw_stats)		 
{
    int r,c;

    fprintf(out_file, "\nTrack Results");

    fprintf(out_file,"\n\nName               Try 1   Try 2   Try 3   Try 4  "
		"Best throw  Deviation");
    fprintf(out_file,  "\n----------------   -----   -----   -----   -----  "
		"---------   ---------\n");

    for (r = 0; r< NCOMPETITORS; r++)
    {
	fprintf(out_file, "%-16s  ", throw_list[r].name);
	for (c = 0; c < N_TRIES; c++)
	    fprintf(out_file, "%6.2f  ", throw_list[r].tries[c] );
		
	fprintf(out_file, "  %6.2f   ", throw_list[r].best_throw );
	fprintf(out_file, "  %6.2f   \n", throw_list[r].deviation );
    }

    fprintf(out_file, "\n\nBest Throw Average  = %6.2f meters ", throw_stats->average_of_best);
    fprintf(out_file, "\n\nWinning Throw       = %6.2f meters\n\n", throw_stats->winning_throw);

    return;
}
/*--------------------------------------------------------*/
