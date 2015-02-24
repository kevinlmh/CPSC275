#include <stdlib.h>
#include <stdio.h>

// function prototype
void init_mat_row(double*, int);
void matmul_ijk_block(double*, double*, double*, int, int);

int main(int argc, char *argv[]) {
	int size = atoi(argv[1]);
	int bsize = atoi(argv[2]);
	double *A = (double *)malloc(sizeof(double) * size * size);
	double *B = (double *)malloc(sizeof(double) * size * size);
	double *C = (double *)malloc(sizeof(double) * size * size);
	init_mat_row(A, size);
	init_mat_row(B, size);
	matmul_ijk_block(A, B, C, size, bsize);
	free(A);
	free(B);
	free(C);
}

void init_mat_row(double *mat, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			*(mat + i * size + j) = 1.0;
		}
	}
}

void matmul_ijk_block(double *a, double *b, double *c, int n, int bsize) {
	int i, j, k, i1, j1, k1;
	for (i = 0; i < n; i+= bsize)
		for (j = 0; j < n; j += bsize)
			for (k = 0; k < n; k += bsize)
				/* bsize x bsize mini matrix multiplications */
				for (i1 = i; i1 < i + bsize; i1++)
					for (j1 = j; j1 < j + bsize; j1++)
						for (k1 = k; k1 < k + bsize; k1++)
							c[i1*n + j1] += a[i1*n + k1] * b[k1*n + j1];
}
