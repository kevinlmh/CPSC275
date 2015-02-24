/*
 * Block matrix multiplication
 *
 * Compile it with:
 *
 *    $ gcc -o matmul_block matmul_block.c 
 *
 * Run it with:
 * 
 *    $ ./matmul_block <matrix dimension> <Block size>
 *
 */
#include <stdio.h>
#include <stdlib.h>

void init_mat_row(double *, int);
void matmul_block(double *, double *, double *, int, int);

int main(int argc, char *argv[])
{
	int i, j, k;
	double *a, *b, *c;
	int N = atoi(argv[1]);
	int bsize = atoi(argv[2]);

	a = (double *)malloc(N*N*sizeof(double));
	b = (double *)malloc(N*N*sizeof(double));
	c = (double *)malloc(N*N*sizeof(double));

	init_mat_row(a, N);
	init_mat_row(b, N);
	matmul_block(a, b, c, N, bsize);
}

void init_mat_row(double *mat, int n)
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			mat[i*n+j] = 1.0;
}

/* Multiply n x n matrices a and b */
void matmul_block(double *a, double *b, double *c, int n, int B) 
{
 int i, j, k, i1, j1, k1;
 for (i = 0; i < n; i+=B)
	for (j = 0; j < n; j+=B)
 		for (k = 0; k < n; k+=B)
			/* B x B mini matrix multiplications */
 			for (i1 = i; i1 < i+B; i1++)
 				for (j1 = j; j1 < j+B; j1++)
 					for (k1 = k; k1 < k+B; k1++)
 						c[i1*n + j1] += a[i1*n + k1]*b[k1*n + j1];
}

