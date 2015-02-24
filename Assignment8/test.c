#include <stdio.h>

int main(void) {
	int N = 64;
	int M = 64;
	int i, j, k, l, p, q;
	for (i = 0; i < N; i += 8) {
		for (j = 0; j < M; j += 8) {
			for (k = i; k < i + 8; k += 4) {
				for (l = j; l < j + 8; l += 4) {
					for (p = k; p < k + 4; p++) {
						for (q = l; q < l + 4; q++) {
							//B[q][p] = A[p][q];
							printf("i=%d, j=%d, k=%d, l=%d, p=%d, q=%d\n", i,j,k,l,p,q);
						}
					}
				}
			}
		}
	}


}
