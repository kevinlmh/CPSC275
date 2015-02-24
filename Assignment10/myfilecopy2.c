/*
 * =====================================================================================
 *
 *       Filename:  myfilecopy2.c
 *
 *    Description: 	CPSC-275 Assignment 10 1b 
 *
 *        Version:  1.0
 *        Created:  11/25/2014 01:18:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kevin Liu 
 *
 * =====================================================================================
 */

/* Performance table
 * =================
 * Myfilecopy1:
 * ------------
 * Buffer size		Time
 * 1				0.688s
 * 2				0.326s
 * 57				0.019s
 * 128				0.013s
 * 256				0.010s
 * 511				0.009s
 * 513				0.009s
 * 1024				0.008s
 *
 * myfilecopy2:		0.018s
 * ------------
 */
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage %s <infile> <outfile> \n", argv[0]);
		return 1;
	}

	FILE *infile, *outfile;
	int c;

	infile = fopen(argv[1], "r");
	outfile = fopen(argv[2], "w");
	if ((infile != NULL) && (outfile != NULL)) {
		while ((c = fgetc(infile)) != EOF)
			fputc(c, outfile);
	} else
		printf("\nfopen unsuccessful!\n");
	fclose(infile);
	fclose(outfile);
}
