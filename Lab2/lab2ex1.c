/* CPSC-275 Lab2 Exercise 1
 * Nicholas Wray & Kevin Liu
 * Sep 15 2014
 */
 
#include <stdio.h>

int main(void)
{
	double d = 1.0;
	int i = 2;
	char ch = 'a';

	double *pd;
	pd = &d;
	int *pi;
	pi = &i;
	char *pch;
	pch = &ch;

	printf("%p\t%.1f\t%d\n", pd, d, sizeof(d));
	printf("%p\t%d\t%d\n", pi, i, sizeof(i));
	printf("%p\t%c\t%d\n", pch, ch, sizeof(ch));

	printf("%p\t%p\t%d\n", &pd, pd, sizeof(pd));
	printf("%p\t%p\t%d\n", &pi, pi, sizeof(pi));
	printf("%p\t%p\t%d\n", &pch, pch, sizeof(pch));

	return 0;
}