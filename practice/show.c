#include <stdio.h>
typedef struct {
	double x;
	double y;
} Point;

void show(Point s) {
	printf("x: %g\n", s.x);
	printf("y: %g\n", s.y);
}

int main(void) {
	Point test = {.25, .75};
	show(test);
	return 0;
}
