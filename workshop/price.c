#include <stdio.h>
#include <float.h>

char *brands[] = {"", "Kleenex", "Charmin", "Delsey", "Generic"};
char *products[] = {"", "Tissue", "TP"};
char *stores[] = {"", "Shaw's", "Walmart", "BJ's", "Mom's"};

int main(void) {
	int count, i;
	int b_code, p_code, sheets, s_code, min_b_code, min_p_code, min_s_code;
	float length, width, price;
	float min = FLT_MAX;

	scanf("%d\n", &count);
	for (i=0; i < count; i++) {
		scanf("%d %d %f %f %d %d %f\n", &b_code, &p_code, &length, &width, &sheets, &s_code, &price);
		//printf("%d %d %f %f %d %d %f\n", b_code, p_code, length, width, sheets, s_code, price);
		float cost = price / (width * length * (float)sheets);
		if (cost < min) {
			min = cost;
			min_b_code = b_code;
			min_p_code = p_code;
			min_s_code = s_code;
		}
	}
	
	printf("Get %s %s at %s.\n", brands[min_b_code], products[min_p_code], stores[min_s_code]);
}
