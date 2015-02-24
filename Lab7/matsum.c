/*
 * File: matsum.c
 * CPSC-275 Lab7 Exercise 2
 * Author: Courtney Driscoll and Kevin Liu
 * Date: Oct 27 2014
 */
#include <stdlib.h>
#include <stdio.h>

// function prototype
void init_mat_row(double*, int);
double sum_row(double*, int); 
double sum_col(double*, int); 

int main(int argc, char *argv[]) {
	int size = atoi(argv[1]);
	double *mat = (double *)malloc(sizeof(double) * size * size);
	init_mat_row(mat, size);
	double result;
	//result = sum_row(mat, size);
	result = sum_col(mat, size);
	printf("Sum = %.2f", result);
}

void init_mat_row(double *mat, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			*(mat + i * size + j) = 1.0;
		}
	}
}

double sum_row(double *mat, int size) {
	int i, j;
	double sum = 0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			sum += *(mat + i * size + j);
		}
	}
	return sum;
}

double sum_col(double *mat, int size) {
	int i, j;
	double sum = 0;
	for (j = 0; j < size; j++) {
		for (i = 0; i < size; i++) {
			sum += *(mat + i * size + j);
		}
	}
	return sum;
}
