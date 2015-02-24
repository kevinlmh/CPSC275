/*
 * Serial matrix multiplication
 *
 * Compile it with:
 *
 *    $ gcc -o matmul matmul.c 
 *
 * Run it with:
 * 
 *    $ ./matmul <matrix dimension> 
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
  int i, j, k, N;
  double *a, *b, *c, sum;

  N = atoi(argv[1]); // matrix dimension
  a = (double *) malloc (N*N*sizeof(double));
  b = (double *) malloc (N*N*sizeof(double));
  c = (double *) malloc (N*N*sizeof(double));
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      a[i*N+j] = i + j;
      b[i*N+j] = i + j;
    }

  // ijk-style matrix multiplication
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      sum = 0.0;
      for (k = 0; k < N; k++) {
	      sum = sum + a[i*N+k] * b[k*N+j];
      }
      c[i*N+j] = sum;
    }
  }
}
