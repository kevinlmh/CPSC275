/* 
 * dotprod1.c - computes the dot product of two vectors using a function.
 *
 * Author: Peter Yoon
 *
 * Date: September 16, 2013
 *
 */

#include <stdio.h>

double computeDot(double [], double [], int);

#define N 512

int main(void)
{
   double x[N], y[N];  // two arrays
   double result; 
   int i;

   // initialize vectors
   for (i = 0; i < N; i++) 
      x[i] = y[i] = 1.0d;

   result = computeDot(x, y, N);
   printf("%f\n", result);

   return 0;
}

/*
 * computeDot - computes the dot product of two n-vectors a and b.
 */
double computeDot(double a[], double b[], int n)
{
   double sum = 0.0d;
   int i;

   for (i = 0; i < n; i++)
      sum += (a[i] * b[i]);
   return sum;
}


