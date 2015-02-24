/*
 * matmul_block.c - This program block-multiplies two matrices.
 *
 * Written by <your name>
 * Nov. 2, 2012
 *
 * Compile with:
 *
 *   gcc -o matmul_block matmul_block.c -D N=<dimension> -D p=<#blocks>
 *
 * Run with:
 *
 *   ./matmul_block
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bSize	N/p		// block size

// functions used
void genmat(double **);
void mmul(double **, double **, double **);
double diffmat(double **, double **, double **);
void blockmat(double **, double **, double **, int, int, int);

void main()
{
	double *a[N], *b[N], *c[N];
	int i;
	time_t start, end;

	// allocate space for matrices, one row at a time
	for (i = 0; i < N; i++) {
		a[i] = (double *) malloc(N*sizeof(double));
		b[i] = (double *) malloc(N*sizeof(double));
		c[i] = (double *) malloc(N*sizeof(double));
	}

	// get random matrices
	genmat(a);
	genmat(b);

	// start the timer
	start = time(NULL);

	// C = A * B
	mmul(a, b, c);

	// start the timer
	end = time(NULL);

	// print the accuracy of the solution and the timing result
    printf("The difference between A*B and C = %f\n", diffmat(a, b, c));
    printf("The running time was %ld seconds.\n", end - start);

	// free up the space
	for (i = 0; i < N; i++) {
  		free(a[i]);
   		free(b[i]);
		free(c[i]);
	}
}

/*
 * genmat - This function generates an N-by-N random matrix.
 */
void genmat(double *a[N])
{
	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++) 
			a[i][j] = (double)(rand()) / RAND_MAX; 
}

/*
 * blockmat - This function multiplies two submatrices of A and B, A_im and B_mj,
 *            respectively.
 */
void blockmat(double *a[N], double *b[N], double *c[N], int i, int m, int j)
{
	// YOUR CODE GOES HERE





}


/*
 * mmul - This function multiplies A and B with the ijk ordering.
 */
void mmul(double *a[N], double *b[N], double *c[N])
{
	// YOUR CODE GOES HERE





}


/*
 * diffmat - This function returns the difference of A*B and C
 *
 *  Basic strategy:
 *    1. Compute a random vector x.
 *    2. Compute z = C*x.
 *    3. Compute y = B*x.
 *    4. Compute x = A*y.
 *    5. Compute the difference between x and z.
 */ 

double diffmat(double *a[N], double *b[N], double *c[N]) 
{
	double x[N], y[N], z[N], sum;
	int i, j;

	// generate a random vector
	for (i = 0; i < N; i++)
		x[i] = (double)(rand()) / RAND_MAX; 

	// z = C*x
	for (i = 0; i < N; i++) {
		sum = 0.;
		for (j = 0; j < N; j++)
			sum += c[i][j] * x[j];
		z[i] = sum;
	}

	// y = B*x
	for (i = 0; i < N; i++) {
		sum = 0.;
		for (j = 0; j < N; j++)
			sum += b[i][j] * x[j];
		y[i] = sum;
	}

	// x = A*y
	for (i = 0; i < N; i++) {
		sum = 0.;
		for (j = 0; j < N; j++)
			sum += a[i][j] * y[j];
		x[i] = sum;
	}

	// compute the difference
	sum = 0.;
	for (i = 0; i < N; i++) 
		sum += abs(x[i] - z[i]);

	return sum;
}
