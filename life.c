#include <stdio.h>
#include <stdlib.h>
#include "board.h"
			 
int main(void){
	
	Board *b; // Pointer to Board 
	b = (Board *) malloc(sizeof(Board)); // Allocate space for Board b
	b->nrows = 0; // Setting board to 4 rows for now (testing purposes before taking input)
	b->ncols = 0; // Setting board to 4 cols for now (testing purposes before taking input)
	
	// Take input for the number of rows and columns, and number of steps
	scanf("%d %d", &b->nrows, &b->ncols);  

	b->numElements = (b->nrows * b->ncols); // Find total possible number of elements in the board
	b->grid = (char *) malloc(sizeof(char)*b->numElements); // Allocate space for grid
	int nsteps = 0;
	int nHealthy = 0;
	int nInfected = 0;

	scanf("%d", &nsteps); // Take input from 2nd line, for number of steps (num times to call update_board function)
			      //
	// Now, loop through b.grid to take input for the board
	for (int i = 0; i < b->nrows; i++){
		for (int j = 0; j < b->ncols; j++){
			scanf(" %c", (b->grid + i * b->ncols + j));
		}
	}
	
	// Now call the update_board function nsteps times
	for (int u = 0; u < nsteps; u++)
	{
		// print the board before the call for testing purposes
	//printf("Board before calling update_board: ");
	//for (int i = 0; i < b->nrows; i++){
	//	for (int j = 0; j < b->ncols; j++){
	//		printf(" %c", *(b->grid + i * b->ncols + j));
	//	}
	//}


	b = update_board(b);

	// print the board after the call for testing purposes
	//printf("Board after calling update_board: ");
	//for (int i = 0; i < b->nrows; i++){
	//	for (int j = 0; j < b->ncols; j++){
	//		printf(" %c", *(b->grid + i * b->ncols + j));
	//}
	//}	
	
	}

	// Outputs the total amount of healthy and infected cells on the board
	// Loop through the board to count number of healthy and infected
	for (int i = 0; i < b->nrows; i++){
		for (int j = 0; j < b->ncols; j++){
			if (*(b->grid + i * b->ncols + j) == 'h'){
				nHealthy++;
			}
			else if (*(b->grid + i * b->ncols + j) == 'i'){
				nInfected++;
			}
		}
	}

	// Now output final results
	printf("healthy: %d, infected: %d", nHealthy, nInfected);

	free(b->grid); // Free the memory when done using it
	free(b);
	return 0;
}
