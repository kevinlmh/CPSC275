#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("Hi.\n");
	fork();
	printf("Bye.\n");
	exit(0);
}
