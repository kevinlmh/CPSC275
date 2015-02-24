/* 
 * matvecmul2.c - computes matrix-vector multiplication, b = Ax.
 *
 * Author: Peter Yoon
 *
 * Date: September 23, 2013
 *
 */

#include <stdio.h>

#define N 32

double computeDot(double *, double *, int);

int main(void)
{
   double a[N][N], x[N];  // matrix and vector to be multiplied
   double b[N];  // result 
   int i, j;

   // initialize vectors
   for (i = 0; i < N; i++) {
      x[i] = 1.0d;
      for (j = 0; j < N; j++)
         a[i][j] = (double)(i + 1);
   }

   // compute each component of b
   for (i = 0; i < N; i++) 
      b[i] = computeDot(a[i], x, N);

   for (i = 0; i < N; i++) 
      printf("%f\n", b[i]);

   return 0;
}

/*
 * computeDot - computes the dot product of two n-vectors a and b.
 */
double computeDot(double *a, double *b, int n)
{
   double sum = 0.0d;
   int i;

   for (i = 0; i < n; i++)
      sum += ((*a++) * (*b++));
   return sum;
}


