/* CPSC-275 Lab1
 * Phongpol Punyagupta & Kevin Liu
 * Sep 8 2014
 */

#include <stdio.h>
#define GRID_SIZE 100

int grid[GRID_SIZE][GRID_SIZE];

void placeSquare(int num, int size, int x, int y) {
	int i,j;
	for(i=0; i<size; i++) {
		for(j=0; j<size; j++) {
			grid[y-1+i][x-1+j] = num;
		}
	}
}

int main(void) {
	int i,j;
	for(i=0; i<GRID_SIZE; i++) {
		for(j=0; j<GRID_SIZE; j++) {
			grid[i][j] = 0;
		}
	}
	int num,num_squares, size, x, y;
	scanf("%d", &num_squares);
	int visable[num_squares];
	int k;
	for(k=0; k<num_squares; k++) {
		visable[k] = 0;
	}	
	for(num=1; num<num_squares+1; num++) {
		scanf("%d %d %d", &size, &x, &y);
		placeSquare(num, size, x, y);
	}
	for(i=0; i<GRID_SIZE; i++) {
		for(j=0; j<GRID_SIZE; j++) {
			if(grid[i][j] != 0) {
				visable[grid[i][j]-1] = 1;
			}
		}
	}
	int l;
	for(k=0; k<num_squares; k++) {
		if(visable[k] == 1)
			printf("%d ",k+1);
	}
	printf("\n");
	return 0;
}
