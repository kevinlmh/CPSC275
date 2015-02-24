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
double diffmat(double *a[n], double *b[n], double *c[n], int n) 
{
	double x[n], y[n], z[n], sum;
	int i, j;

	// generate a random vector
	for (i = 0; i < n; i++)
		x[i] = (double)(rand()) / RAND_MAX; 

	// z = C*x
	for (i = 0; i < n; i++) {
		sum = 0.;
		for (j = 0; j < n; j++)
			sum += c[i][j] * x[j];
		z[i] = sum;
	}

	// y = B*x
	for (i = 0; i < n; i++) {
		sum = 0.;
		for (j = 0; j < n; j++)
			sum += b[i][j] * x[j];
		y[i] = sum;
	}

	// x = A*y
	for (i = 0; i < n; i++) {
		sum = 0.;
		for (j = 0; j < n; j++)
			sum += a[i][j] * y[j];
		x[i] = sum;
	}

	// compute the difference
	sum = 0.;
	for (i = 0; i < n; i++) 
		sum += abs(x[i] - z[i]);

	return sum;
}
