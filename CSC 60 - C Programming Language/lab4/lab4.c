/* Victor Peraza                                       */
/* Lab 4                                           */
/* Figure the area of the top of a cylinder        */
/* and the volume of a cylinder                    */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILE_IN  "lab4.dat"
#define FILE_OUT "lab4.out"
//#define FILE_IN  "lab4sample.dat"

int main(void) {
	
	int count;
	double radius, height, area, volume;
	count = 1;

	FILE * data_in;
	FILE * data_out;

	  data_in = fopen ("lab4.dat", "r");
	if(data_in == NULL) {

		printf("Error on opening the input file \n");
		exit (EXIT_FAILURE);
	}
	
	  data_out = fopen ("lab4.out", "w");
	if(data_out == NULL) {
	
		printf("Error on opening the output file \n");
		exit (EXIT_FAILURE);
	}

        fprintf(data_out, "\nVictor Peraza.  Lab 4.\n");
	
	while ((fscanf(data_in, "%lf%lf", &radius, &height)) == 2) {

	area = M_PI * radius * radius;
	volume = M_PI * radius * radius * height;
	
	//count = 0;
	fprintf(data_out, "\nCylinder %1d", count);
	fprintf(data_out, "\nThe radius is:    %9.3f", radius);
	fprintf(data_out, "\nThe height is:    %9.3f", height);
	fprintf(data_out, "\nThe top area is:  %9.3f", area);
	fprintf(data_out, "\nThe volume is:    %9.3f\n", volume);
	count++;

	fprintf(data_out, "\n");

	}
	fclose(data_in);
	fclose(data_out);

	return EXIT_SUCCESS;

}

