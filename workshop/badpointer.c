#include <stdio.h>

void f();

int main(void)
{
	f();

	return 0;
}

void f()
{
	int *p = 0;

	printf("%d\n", *p);
}
