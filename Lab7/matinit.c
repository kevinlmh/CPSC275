/*
 * File: matinit.c
 * CPSC-275 Lab7 Exercise 1
 * Author: Courtney Driscoll and Kevin Liu
 * Date: Oct 27 2014
 */
#include <stdlib.h>

// function prototype
void init_mat_row(double*, int);
void init_mat_col(double*, int);

int main(int argc, char *argv[]) {
	int size = atoi(argv[1]);
	double *mat = (double *)malloc(sizeof(double) * size * size);
	//init_mat_row(mat, size);
	init_mat_col(mat, size);
}

void init_mat_row(double *mat, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			*(mat + i * size + j) = 1.0;
		}
	}
}

void init_mat_col(double *mat, int size) {
	int i, j;
	for (j = 0; j < size; j++) {
		for (i = 0; i < size; i++) {
			*(mat + i * size + j) = 1.0;
		}
	}
}
