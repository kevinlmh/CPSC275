#include <stdio.h>
#define true 1
#define false 0

int has_zero(int a[], int n) {
	for (int i = 0; i< n; i++)
		if (a[i] == 0)
			return true;
		else
			return false;
}

int main(void) {
	int a[5] = {1, 2, 0, 4, 5};
	printf("%d\n", has_zero(a, 5));
}
