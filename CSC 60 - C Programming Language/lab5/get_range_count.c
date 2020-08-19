/*****************/
/* Victor Peraza  */
/*lab 5 */

#include "lab5.h"

void get_range_count(int number_list[], int real_filesize, int *range_count) {
		
	*range_count = 0;  
	int n;	

	for(n = 0; n < real_filesize; n++) {
		if( number_list[n] >= 90 && number_list[n] <= 99) {
			(*range_count)++;		

		}
}	
	return;

}
