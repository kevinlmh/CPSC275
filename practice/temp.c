#include <stdio.h>

int main() {
	int f,c;
	printf("Please input temp in F: ");
	scanf("%d", &f);
	c = (5.0/9.0)*(f-32);
	printf("Temperature in C: %d\n", c);
	return 0;
}
