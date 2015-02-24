/* CPSC275 Lab1
 * Phongpol Punyagupta & Kevin Liu
 * Sep 8 2014
 * 
 * Time table
 *
 * size			time
 * 100000		0.013
 * 200000		0.021
 * 300000		0.028
 * 500000		0.035
 * 1000000	0.048
 * 1100000	0.055
 * 1300000	0.060
 * size larger than 1310000 results in segmentation fault
 */

#include <stdio.h>
#define N 1310000

int main(void) {
	float x[N], y[N];
	int i;
	for(i=0; i<N; i++) {
		x[i] = y[i] = 1.0;
	}
	float dotprod = 0;
	for(i=0; i<N; i++) {
		dotprod += x[i]*y[i];
	}

	return 0;
}
