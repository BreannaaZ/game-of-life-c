#include "board.h"
#include <stdio.h>
#include <stdlib.h>

// update_board function will take in the current state of the board and return a pointer to a Board reflecting the
// state after one timestep
Board* update_board(Board *b){
// We want to iterate through for each cell. For each one we check the various conditions, depending on the cells initial status to determine which checks to do:
// Too much exposure: A healthy cell with 4 or more infected neighbors becomes infected
// Overcrowding: An infected cell with 6+ alive neighbors dies from overcrowding
// Birth: A dead cell with exactly 3 alive neighbors becomes alive with the state of the majority of its alive neighbors
// Existing: Any other cells continue to exist with their current state (healthy / infected / dead)
// The grid is periodic to determine neighbord for edge cells (wraps around). 
// 	Cells in first column use cells in the last column as their left neighbors
// 	Cells in the last column use cells in the first column for their right neighbors
// 	Cells in the first row use cells in the last row as their top neighbors
// 	Cells in the last row use cells in the top row as their bottom neighbors
// 	Corners involve wrapping both columns and rows at the same time
// Side note: Only one case can occur for each cell at a single timestep.


// REMEMBER: For accessing the array, use pointer arithmetic. Can't use [] notation.
// 	*(b + i * ncols + j) will give the [i][j] element for i row, j col (remember starts at 0)

// Because all the cells update simultaneously, we will want to create a new temp board to hold all the updates. If we update the current board it will affect how the other cells are updated.
char *tempBoard;
tempBoard = (char *) malloc(sizeof(char)*b->numElements);

// Loop through for each element of the board
for (int i = 0; i < b->nrows; i++) {
	for (int j = 0; j < b->ncols; j++){
	// Firstly, we will set the temporary board cell to be the same as the current board
	*(tempBoard + i * b->ncols + j) = *(b->grid + i * b->ncols + j);
	// For each element, we want to count it's number of alive, infected, and healthy neighbors
	int healthy = 0; // reset the count of healthy at the start of each loop
	int infected = 0; // reset the count of infected at the start of each loop
	// We can use the amount (healthy + infected) to determine the number of alive neighbors
	// Approach to access the neighbors to the current cell (with wrapping):
	// 	The row and column index of the current cell will be i,j
	// 	We can use nested for loops to iterate through the 3z3 grid centered around i,j
	// 		The neighbor to the left of an element will be at row i, column j-1. 
	// 		The neigbor to the right of an element will be at row i, column j+1.
	// 		The neighbor above will be row i-1, column j.
	// 		The neighbor below will be row i+1, column j.
	// 		The neighbor at the upper left will be at row i-1, j-1
	// 		The neighbor at the upper right will be at row i-1, j+1
	// 		The neighbor at the lower left will be at row i+1, j-1
	// 		The neighbor at the lower right will be at row i+1, j+1
	
	// COUNT THE ADJACENT NEIGHBORS
	int i3, j3, neighborI, neighborJ; // i3 and j3 will loop through for the row, col indices of the 3x3 grid around
					  // the current element i,j
					  // neighborI and neighborJ will represent the row, col index of the 
					  // neighboring elements, considering the wrapping around the board
	// Loop through the 3x3 grid around the current element i,j
	for (i3 = -1; i3 <= 1; i3++){
		for (j3 = -1; j3 <= 1; j3++){
		// We can calculate the indices of the neighbors while considering wrapping around the board by using modular arithmetic; if an index goes out of bounds, we use modular arithmetic to wrap around
		// the board by using the remainder from modular arithmetic with the number of colimns/rows
		neighborI = (i + i3 + b->nrows) % b->nrows;
		neighborJ = (j + j3 + b->ncols) % b->ncols;

		// Now we have an index of the neighborl (neighborI, neighborJ). We can check the status of this cell and add to our count.
		// We do not want to count the (i,j) cell so we check for that first.
		// if (i3 != i || j3 != j){ // Make sure we are not counting the i,j current cell as one of the neighboring ones
		// Now we check the status of the cell and add it to our counts
			if (*(b->grid + neighborI * b->ncols + neighborJ) == 'h'){
				healthy++;
			}
			if (*(b->grid + neighborI * b->ncols + neighborJ) == 'i'){
				infected++;
			}
		//}
		}
	}
	// Now we have the counts of neighboring healthy and infected cells to the current cell. We can then update the board based on our rules.
	
	// Firstly, check rule #1: too much exposure (Healthy cell with 4+ infected neighbors becomes infected)
	if ((*(b->grid + i * b->ncols + j) == 'h') && infected >= 4){
		// Change the current cell in the temporary grid to infected
		*(tempBoard + i * b->ncols + j) = 'i';
		} else if ((*(b->grid + i * b->ncols + j) == 'i') && (healthy + infected) > 6){ // check rule #2 overcrowding
		// Change the current cell in the temporary grid to dead
		*(tempBoard + i * b->ncols + j) = 'x';
		} else if ((*(b->grid + i * b->ncols + j) == 'x') && (healthy + infected) == 3){ // Check rule #3 birth
		// Change the current cell in the temporary grid to the majority
		if (healthy > infected){
		*(tempBoard + i * b->ncols + j) = 'h';
		} else if (infected > healthy){
		*(tempBoard + i * b->ncols + j) = 'i';
		}

	}
} // end outer for loop
} // end inner for loop

// Copy the temporary board back into our original grid
	for (int i = 0; i < b->nrows; i++) {
		for (int j = 0; j < b->ncols; j++) {
			*(b->grid + i * b->ncols + j) = *(tempBoard + i * b->ncols + j); // set the cell in b.grid to the one in tempBoard
		}
	}

// Free temporary board
	free(tempBoard);
	return b;
} // end main
