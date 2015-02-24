#include <stdio.h>

int mystrlen(char *s) {
	int count = 0;
	for (; *s != '\0'; s++)
		count++;
	return count;
}

int main(void) {
	printf("%d\n", mystrlen("This is a string."));
}
