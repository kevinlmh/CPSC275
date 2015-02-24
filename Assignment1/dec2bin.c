/*
 * Program: dec2bin.c 
 * Purpose: Convert a positive decimal integer to binary
 * Author:  Kevin Liu
 * Date:    9/5/2014
 */

#include <stdio.h>

/*
 * Function: decToBin()
 * Purpose:  Convert a decimal int to binary and print it out
 *
 * Parameters:
 *    n: a positive integer
 *
 * Returns: no return value 
 */
void decToBin(n) {
	if(n == 0 | n == 1)
		printf("%d", n);
	else {
		decToBin(n / 2);
		printf("%d", n % 2);
	}
}

int main(void) {
	int n;
	scanf("%d", &n);
	decToBin(n);
	printf("\n");
}
