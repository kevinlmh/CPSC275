/*
 * File: matmul.c
 * CPSC-275 Lab7 Exercise 4
 * Author: Courtney Driscoll and Kevin Liu
 * Date: Oct 27 2014
 */
#include <stdlib.h>
#include <stdio.h>

// function prototype
void init_mat_row(double*, int);
void matmul_ijk(double*, double*, double*, int);
void matmul_kij(double*, double*, double*, int);
void matmul_kji(double*, double*, double*, int);

int main(int argc, char *argv[]) {
	int size = atoi(argv[1]);
	double *A = (double *)malloc(sizeof(double) * size * size);
	double *B = (double *)malloc(sizeof(double) * size * size);
	double *C = (double *)malloc(sizeof(double) * size * size);
	init_mat_row(A, size);
	init_mat_row(B, size);
	matmul_ijk(A, B, C, size);
}

void init_mat_row(double *mat, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			*(mat + i * size + j) = 1.0;
		}
	}
}

void matmul_ijk(double *A, double *B, double *C, int size) {
	int i, j, k;
	double sum;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			sum = 0;
			for (k = 0; k < size; k++) {
				sum += *(A + i * size + k) * *(B + k * size +j);
			}
			*(C + i * size + j) = sum;
		}
	}
}

// best case
void matmul_kij(double *A, double *B, double *C, int size) {
	int i, j, k;
	double r;
	for (k = 0; k < size; k++) {
		for (i = 0; i < size; i++) {
			r = *(A + i * size + k);
			for (j = 0; j < size; j++) {
				*(C + i * size + j) += *(B + k * size + j) * r;
			}
		}
	}
}
// worst case
void matmul_kji(double *A, double *B, double *C, int size) {
	int i, j, k;
	double r;
	for (k = 0; k < size; k++) {
		for (j = 0; j < size; j++) {
			r = *(B + k * size + j);
			for (i = 0; i < size; i++) {
				*(C + i * size + j) += *(A + i * size + k) * r;
			}
		}
	}
}


