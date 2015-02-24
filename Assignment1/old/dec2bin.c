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
 * Returns: n in binary
 */
void decToBin(int n) {
	char bin[100];
	int i = -1;
	do {
		bin[++i] = n%2==1? '1' : '0';
		n /= 2;
	} while (n > 0);
	for(i; i >= 0; i--)
		printf("%c",bin[i]);
	printf("\n");
} //decToBin()

int main() {
	int dec;
	scanf("%d", &dec);
	decToBin(dec);
	return 0;
}
