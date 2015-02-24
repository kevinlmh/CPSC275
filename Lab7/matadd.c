/*
 * File: matadd.c
 * CPSC-275 Lab7 Exercise 3
 * Author: Courtney Driscoll and Kevin Liu
 * Date: Oct 27 2014
 */
#include <stdlib.h>
#include <stdio.h>

// function prototype
void init_mat_row(double*, int);
void matadd_row(double*, double*, double*, int);
void matadd_col(double*, double*, double*, int);

int main(int argc, char *argv[]) {
	int size = atoi(argv[1]);
	double *A = (double *)malloc(sizeof(double) * size * size);
	double *B = (double *)malloc(sizeof(double) * size * size);
	double *C = (double *)malloc(sizeof(double) * size * size);
	init_mat_row(A, size);
	init_mat_row(B, size);
	//matadd_row(A, B, C, size);
	matadd_col(A, B, C, size);
}

void init_mat_row(double *mat, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			*(mat + i * size + j) = 1.0;
		}
	}
}

void matadd_row(double *A, double *B, double *C, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			*(C + i * size + j) = *(A + i * size + j) + *(B + i * size +j);
		}
	}
}

void matadd_col(double *A, double *B, double *C, int size) {
	int i, j;
	for (j = 0; j < size; j++) {
		for (i = 0; i < size; i++) {
			*(C + i * size + j) = *(A + i * size + j) + *(B + i * size +j);
		}
	}
}












