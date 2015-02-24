#include <stdio.h>

int main(void) {
	printf("1 << 32: %d\n", (1 << 31) << 1);
	unsigned f = 0xFFFFFFFF;
	printf("(0xFFFFFFFF >> 31) << 31 is %u\n", (f >> 31) << 31);
}
