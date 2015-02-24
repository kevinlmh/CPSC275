
void transpose_64(int M, int N, int A[N][M], int B[M][N]) {
	int diag;
	int i, j, k, l, p, q;
	//int c[4];
			
	for (i = 0; i < N; i += 8) {
		for (j = 0; j < M; j += 8) {
			
			if (i == j) {
				for (k = i; k < i + 8; k += 4) {
					for (l = j; k < j +8; l += 4) {
						// upper left and lower right
						if (k == l) {
							for (p = k; p < k + 4; p++) {
								for (q = l; q < l + 4; q++) {
									if (p == q)	
										diag = A[p][q];	
									else
										B[q][p] = A[p][q];
								}
								B[p][p] = diag;
							}
						} 
						// upper right
						else if (k == l - 4) {
							for (p = k; p < k + 4; p++) {
								for (q = l; q < l + 4; q++) {
									if (q == p + 4)
										diag = A[p][q];
									else
										B[q][p] = A[p][q];
								}
								B[p+4][p] = diag;
							}
						}
						// lower left
						else {
							for (p = k; p < k + 4; p++) {
								for (q = l; q < l + 4; q++) {
									if (q == p - 4)
										diag = A[p][q];
									else
										B[q][p] = A[p][q];
								}
								B[p-4][p] = diag;
							}
						}


					}
				}
			} else
				for (p = i; p < i + 8; p++)
					for (q = j; q < j + 8; q++)
						B[q][p] = A[p][q];	
		
		
		}
	} 

}


