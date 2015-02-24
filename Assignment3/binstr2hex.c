/*
 * Program: vsm.c
 *
 * Purpose: Convert 16-bit binary strings to hexadecimal
 *
 * Author:	Kevin Liu
 * Date:	9/20/2014
 */

#include <stdio.h>
#include <math.h>

typedef long long int LLONG;

// function prototypes
void binToHex(LLONG);
void printHexDigit(LLONG);

int main(void) {
	LLONG n;
	while (scanf("%lld\n", &n) != EOF) {
		binToHex(n);
	}
	return 0;
}

/*
 * Function: binToHex
 * Purpose:  Convert a binary string to hexadecimal
 *
 * Returns: nothing
 */
void binToHex(LLONG bin) {
	printHexDigit(bin / 1000000000000);
	bin = bin % 1000000000000;
	printHexDigit(bin / 100000000);
	bin = bin % 100000000;
	printHexDigit(bin / 10000);
	bin = bin % 10000;
	printHexDigit(bin);
	printf("\n");
}

/*
 * Function: printHexDigit
 * Purpose:  Convert a 4-bit binary string to hexadecimal and print it out
 *
 * Returns: nothing
 */
void printHexDigit(LLONG digit) {
	char c;
	switch(digit) {
		case 0:		c = '0';
					break;
		case 1:		c = '1';
					break;
		case 10:	c = '2';
					break;
		case 11:	c = '3';
					break;
		case 100:	c = '4';
					break;
		case 101:	c = '5';
					break;
		case 110:	c = '6';
					break;
		case 111:	c = '7';
					break;
		case 1000:	c = '8';
					break;
		case 1001:	c = '9';
					break;
		case 1010:	c = 'A';
					break;
		case 1011:	c = 'B';
					break;
		case 1100:	c = 'C';
					break;
		case 1101:	c = 'D';
					break;
		case 1110:	c = 'E';
					break;
		case 1111:	c = 'F';
					break;
		default:	printf("*** Invalid Input: Not Hexadecimal! ***\n");
	}
	printf("%c", c);
}

