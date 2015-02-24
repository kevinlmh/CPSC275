/* File: p2-66.c
 * Author: Kevin Liu
 * Data: Oct 6 2014
 */
#include <stdio.h>

// function prototype
int leftmost_one(int);

int main(void) {
	int x = 0x6600;
	printf("The leftmost mask for 0x%.4X is 0x%.4X.\n", x, leftmost_one(x)); 
}

int leftmost_one(int x) {
	x |= x >> 16;
	x |= x >> 8;
	x |= x >> 4;
	x |= x >> 2;
	x |= x >> 1;
	x ^= (x >> 1);
	return x;
}
