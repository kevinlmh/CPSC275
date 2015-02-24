/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void transpose_32(int M, int N, int A[N][M], int B[M][N]);
void transpose_64(int M, int N, int A[N][M], int B[M][N]);
void transpose_ireg(int M, int N, int A[N][M], int B[M][N]);
void trans(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
	if (M == 32 && N == 32)
		transpose_32(M, N, A, B);
	else if (M == 64 && N == 64)
		transpose_64(M, N, A, B);
	else
		transpose_ireg(M, N, A, B);
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

/*
 * transpose_32 - This function is designed specifically for 32 x 32 case
 */
void transpose_32(int M, int N, int A[N][M], int B[M][N]) {
	int bsize = 8;
	int diag;
	int i, j, k, l;

	for (i = 0; i < N; i += bsize) {
		for (j = 0; j < M; j += bsize) {
			for (k = i; k < i + bsize; k++) {
				for (l = j; l < j + bsize; l++) {
					if (i == j && k == l)
						diag = A[k][l];
					else
						B[l][k] = A[k][l];
				}
				if (i == j)
					B[k][k] = diag;
			}
		}
	}
}

void transpose_64(int M, int N, int A[N][M], int B[M][N]) {
	int i, j, k, l;
    int t0, t1, t2, t3, t4, t5, t6, t7;

	/*  _______
	 * | A | B |     
	 * |___|___|
	 * | C | D |
	 * |___|___|
	 *
	 * each 8 x 8 block is divided into four 4 x 4 blocks
	 * labeled A, B, C, D
	 */
	 
    /* diagonal blocks except (7, 7)
     * use higher half of block(0, 7) as buffer
     * i.e. use (0, 56) to (3, 63) as buffer
     */ 
    for(i = 0; i < N; i += 8) {
    	for(j = 0; j < M; j += 8) {
            if (i == j && i != 56) {
        		// copy A and B to Matrix B 8 misses
                for (k = i; k < i + 4; k++) {
                    t0 = A[k][j];
                    t1 = A[k][j+1];
                    t2 = A[k][j+2];
                    t3 = A[k][j+3];
                    t4 = A[k][j+4];
                    t5 = A[k][j+5];
                    t6 = A[k][j+6];
                    t7 = A[k][j+7];

                    B[k][j] = t0;
                    B[k][j+1] = t1;
                    B[k][j+2] = t2;
                    B[k][j+3] = t3;
                    B[k][j+4] = t4;
                    B[k][j+5] = t5;
                    B[k][j+6] = t6;
                    B[k][j+7] = t7;

                    // copy B to left half of buffer, first time 4 miss, otherwise 0 miss.
                    B[k - i][56] = t4;
                    B[k - i][57] = t5;
                    B[k - i][58] = t6;
                    B[k - i][59] = t7;
                }
                // transpose A in Matrix B
                for (k = i; k < i + 4; k++) {
                    for (l = k; l < j + 4; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[l][k];
                        B[l][k] = t0;
                    }
                }

                // copy C and D to Matrix B 8 misses
                for (k = i + 4; k < i + 8; k++) {
                    t0 = A[k][j];
                    t1 = A[k][j+1];
                    t2 = A[k][j+2];
                    t3 = A[k][j+3];
                    t4 = A[k][j+4];
                    t5 = A[k][j+5];
                    t6 = A[k][j+6];
                    t7 = A[k][j+7];

                    B[k][j] = t0;
                    B[k][j+1] = t1;
                    B[k][j+2] = t2;
                    B[k][j+3] = t3;
                    B[k][j+4] = t4;
                    B[k][j+5] = t5;
                    B[k][j+6] = t6;
                    B[k][j+7] = t7;

                    // copy C to right half of buffer, first time 4 misses, otherwise 0 miss
                    B[k - i - 4][60] = t0;
                    B[k - i - 4][61] = t1;
                    B[k - i - 4][62] = t2;
                    B[k - i - 4][63] = t3;
                }

                // transpose D in Matrix B
                for (k = i + 4; k < i + 8; k++) {
                    for (l = k; l < j + 8; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[l][k];
                        B[l][k] = t0;
                    }
                }

                // transpose B and C in buffer
                for (k = 0; k < 4; k++) {
                    for (l = 56 + k; l < 60; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[l - 56][k + 56];
                        B[l - 56][k + 56] = t0;
                    }
                }

                for (k = 0; k < 4; k++) {
                    for (l = 60 + k; l < 64; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[l - 60][k + 60];
                        B[l - 60][k + 60] = t0;
                    }
                }

                // copy B from buffer to Matrix B
                for (k = i + 4; k < i + 8; k++) {
                    for (l = j; l < j + 4; l++) {
                        B[k][l] = B[k - i - 4][56 + l - j];
                    }
                }
                // copy C from buffer to Matrix B
                for (k = i; k < i + 4; k++) {
                    for (l = j + 4; l < j + 8; l++) {
                        B[k][l] = B[k - i][60 + l - j - 4];
                    }
                }
            }
        }
    }

	/* Non-diagonal blocks
	 * 
	 */
    for(i = 0; i < N; i += 8) {
        for(j = 0; j < M; j += 8) {
            if ( i != j ) {       
                // copy A and B to Matrix B
                for (k = 0; k < 4; k++) {
                    t0 = A[i + k][j];
                    t1 = A[i + k][j+1];
                    t2 = A[i + k][j+2];
                    t3 = A[i + k][j+3];
                    t4 = A[i + k][j+4];
                    t5 = A[i + k][j+5];
                    t6 = A[i + k][j+6];
                    t7 = A[i + k][j+7];

                    B[j + k][i] = t0;
                    B[j + k][i+1] = t1;
                    B[j + k][i+2] = t2;
                    B[j + k][i+3] = t3;
                    B[j + k][i+4] = t4;
                    B[j + k][i+5] = t5;
                    B[j + k][i+6] = t6;
                    B[j + k][i+7] = t7;
                }
                
                // transpose A in Matrix B
                for (k = j; k < j + 4; k++) {
                    for (l = i + k - j; l < i + 4; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[j + l - i][i + k - j];
                        B[j + l - i][i + k - j] = t0;
                    }
                }
                
                // Copy C and D to Matrix B
                for (k = 0; k < 4; k++) {
               		// copy C and B to lower left
                    t0 = B[j + k][i + 4];
                    t1 = B[j + k][i + 5];
                    t2 = B[j + k][i + 6];
                    t3 = B[j + k][i + 7];

                    t4 = A[i + 4 + k][j];
                    t5 = A[i + 4 + k][j+1];
                    t6 = A[i + 4 + k][j+2];
                    t7 = A[i + 4 + k][j+3]; // 4 misses

                    B[j + k][i + 4] = t4;
                    B[j + k][i + 5] = t5;
                    B[j + k][i + 6] = t6;
                    B[j + k][i + 7] = t7; // 0 miss

                    B[j + 4 + k][i] = t0;
                    B[j + 4 + k][i+1] = t1;
                    B[j + 4 + k][i+2] = t2;
                    B[j + 4 + k][i+3] = t3; // 4 misses
                    
					// copy D to Matrix B
                    t0 = A[i + 4 + k][j + 4];
                    t1 = A[i + 4 + k][j + 5];
                    t2 = A[i + 4 + k][j + 6];
                    t3 = A[i + 4 + k][j + 7]; // 0 miss

                    B[j + 4 + k][i + 4] = t0;
                    B[j + 4 + k][i + 5] = t1;
                    B[j + 4 + k][i + 6] = t2;
                    B[j + 4 + k][i + 7] = t3; // 0 miss
                }
				
				// transpose D in Matrix B
                for (k = j + 4; k < j + 8; k++) {
                    for (l = i + k - j; l < i + 8; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[j + l - i][i + k - j];
                        B[j + l - i][i + k - j] = t0;
                    }
                }

				// transpose C in Matrix B
                for (k = j + 4; k < j + 8; k++) {
                    for (l = i + k - j - 4; l < i + 4; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[j + 4 + l - i][i + k - j - 4];
                        B[j + 4 + l - i][i + k - j - 4] = t0;
                    }
                } // 0 miss

				// transpose B in Matrix B
                for (k = j; k < j + 4; k++) {
                    for (l = i + 4 + k - j; l < i + 8; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[j + l - i - 4][i + 4 + k - j];
                        B[j + l - i - 4][i + 4 + k - j] = t0;
                    }
                } // 4 misses
                
            } 
            
            /* Last diagonal block (7, 7)
             *
             */
            else if (i == j && i == 56) {
                // copy A and B to Matrix B
                for (k = i; k < i + 4; k++) {
                    t0 = A[k][j];
                    t1 = A[k][j+1];
                    t2 = A[k][j+2];
                    t3 = A[k][j+3];
                    t4 = A[k][j+4];
                    t5 = A[k][j+5];
                    t6 = A[k][j+6];
                    t7 = A[k][j+7];

                    B[k][j] = t0;
                    B[k][j+1] = t1;
                    B[k][j+2] = t2;
                    B[k][j+3] = t3;
                    B[k][j+4] = t4;
                    B[k][j+5] = t5;
                    B[k][j+6] = t6;
                    B[k][j+7] = t7;
                }
                
                // transpose A in Matrix B
                for (k = i; k < i + 4; k++) {
                    for (l = k; l < j + 4; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[l][k];
                        B[l][k] = t0;
                    }
                }
				
				// transpose B in Matrix B
                for (k = i; k < i + 4; k++) {
                    for (l = k + 4; l < j + 8; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[l - 4][k + 4];
                        B[l - 4][k + 4] = t0;
                    }
                }

                // copy C and D to Matrix B
                for (k = i + 4; k < i + 8; k++) {
                    t0 = A[k][j];
                    t1 = A[k][j+1];
                    t2 = A[k][j+2];
                    t3 = A[k][j+3];
                    t4 = A[k][j+4];
                    t5 = A[k][j+5];
                    t6 = A[k][j+6];
                    t7 = A[k][j+7];

                    B[k][j] = t0;
                    B[k][j+1] = t1;
                    B[k][j+2] = t2;
                    B[k][j+3] = t3;
                    B[k][j+4] = t4;
                    B[k][j+5] = t5;
                    B[k][j+6] = t6;
                    B[k][j+7] = t7;
                }

				// transpose D in Matrix B
                for (k = i + 4; k < i + 8; k++) {
                    for (l = k; l < j + 8; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[l][k];
                        B[l][k] = t0;
                    }
                }

				// transpose C in Matrix B
                for (k = i + 4; k < i + 8; k++) {
                    for (l = j + k - i - 4; l < j + 4; l++) {
                        t0 = B[k][l];
                        B[k][l] = B[l + 4][k - 4];
                        B[l + 4][k - 4] = t0;
                    }
                }

                // exchange B and C in Matrix B
                for (k = 0; k < 4; k++) {
                    t4 = B[i + 4 + k][j];
                    t5 = B[i + 4 + k][j+1];
                    t6 = B[i + 4 + k][j+2];
                    t7 = B[i + 4 + k][j+3];
                    t0 = B[i + k][j+4];
                    t1 = B[i + k][j+5];
                    t2 = B[i + k][j+6];
                    t3 = B[i + k][j+7];

                    B[i + k][j+4] = t4;
                    B[i + k][j+5] = t5;
                    B[i + k][j+6] = t6;
                    B[i + k][j+7] = t7;
                    B[i + 4 + k][j] = t0;
                    B[i + 4 + k][j+1] = t1;
                    B[i + 4 + k][j+2] = t2;
                    B[i + 4 + k][j+3] = t3;
                }
            }
        }
    }

}


void transpose_64_version2(int M, int N, int A[N][M], int B[M][N]) {
	int i, j, k, l;
	int t0, t1, t2, t3, t4, t5, t6, t7;
			
	/*  _______
	 * | A | B |     
	 * |___|___|
	 * | C | D |
	 * |___|___|
	 *
	 * each 8 x 8 block is divided into four 4 x 4 blocks
	 * labeled A, B, C, D
	 */
	for (i = 0; i < N; i += 8) {
		for (j = 0; j < M; j += 8) {
			/* Lower triangular blocks
			 * use block (0,7) as buffer
			 * i.e. (0, 56) to (3, 63)
			 */
			if (i < j) { 
				// first four lines [A B]
				for (k = i; k < i + 4; k++) {	
					// transpose A directly
					B[j][k] = A[k][j];
					B[j+1][k] = A[k][j+1];
					B[j+2][k] = A[k][j+2];
					B[j+3][k] = A[k][j+3];

					// save B to right half of buffer
					t4 = A[k][j+4];
					t5 = A[k][j+5];
					t6 = A[k][j+6];
					t7 = A[k][j+7];
					B[k-i][60] = t4;
					B[k-i][61] = t5;
					B[k-i][62] = t6;
					B[k-i][63] = t7;
				}

				// bottom four lines [C D]
				for (k = i + 4; k < i + 8; k++) {
					// save C to left half of buffer	
					t0 = A[k][j];
					t1 = A[k][j+1];
					t2 = A[k][j+2];
					t3 = A[k][j+3];

					B[k-i-4][56] = t0;
					B[k-i-4][57] = t1;
					B[k-i-4][58] = t2;
					B[k-i-4][59] = t3;

					// transpose D directly
					B[j+4][k] = A[k][j+4];
					B[j+5][k] = A[k][j+5];
					B[j+6][k] = A[k][j+6];
					B[j+7][k] = A[k][j+7];
				}

				// transpose B
				for (l = 0; l < 4; l++) {
					t4 = B[l][60];
					t5 = B[l][61];
					t6 = B[l][62];
					t7 = B[l][63];

					B[j+4+l][k] = t4;
					B[j+4+l][k+1] = t5;
					B[j+4+l][k+2] = t6;
					B[j+4+l][k+3] = t7;
				}

				// transpose C
				for (l = 0; l < 4; l++) {
					t0 = B[l][56];
					t1 = B[l][57];
					t2 = B[l][58];
					t3 = B[l][59];

					B[j+l][k+4] = t0;
					B[j+l][k+5] = t1;
					B[j+l][k+6] = t2;
					B[j+l][k+7] = t3;
				}
			}

			// upper triangular blocks
			if (i > j) {
			  	/* if block is in first row
			  	 * use another buffer area
			  	 * use upper half of block (7, 7) as buffer
			  	 * i.e. (56, 56) to (59, 63)
				 */
				if (i == 0) {
					// first four lines [A B]
					for (k = i; k < i + 4; k++) {	
						// transpose A directly
						B[j][k] = A[k][j];
						B[j+1][k] = A[k][j+1];
						B[j+2][k] = A[k][j+2];
						B[j+3][k] = A[k][j+3];

						// save B to right half of buffer
						t4 = A[k][j+4];
						t5 = A[k][j+5];
						t6 = A[k][j+6];
						t7 = A[k][j+7];
						B[k-i+56][60] = t4;
						B[k-i+56][61] = t5;
						B[k-i+56][62] = t6;
						B[k-i+56][63] = t7;
					}

					// bottom four lines [C D]
					for (k = i + 4; k < i + 8; k++) {
						// save C to left half of buffer	
						t0 = A[k][j];
						t1 = A[k][j+1];
						t2 = A[k][j+2];
						t3 = A[k][j+3];

						B[k-i-4+56][56] = t0;
						B[k-i-4+56][57] = t1;
						B[k-i-4+56][58] = t2;
						B[k-i-4+56][59] = t3;

						// transpose D directly
						B[j+4][k] = A[k][j+4];
						B[j+5][k] = A[k][j+5];
						B[j+6][k] = A[k][j+6];
						B[j+7][k] = A[k][j+7];
					}

					// transpose B
					for (l = 0; l < 4; l++) {
						t4 = B[l+56][60];
						t5 = B[l+56][61];
						t6 = B[l+56][62];
						t7 = B[l+56][63];

						B[j+4+l][k] = t4;
						B[j+4+l][k+1] = t5;
						B[j+4+l][k+2] = t6;
						B[j+4+l][k+3] = t7;
					}

					// transpose C
					for (l = 0; l < 4; l++) {
						t0 = B[l+56][56];
						t1 = B[l+56][57];
						t2 = B[l+56][58];
						t3 = B[l+56][59];

						B[j+l][k+4] = t0;
						B[j+l][k+5] = t1;
						B[j+l][k+6] = t2;
						B[j+l][k+7] = t3;
					}

				}
				/* block is not in first row
				 * safe to use block(0, 0) as buffer
				 * i.e. (0, 0) to (3, 7)
				 */
				else {
					// first four lines [A B]
					for (k = i; k < i + 4; k++) {	
						// transpose A directly
						B[j][k] = A[k][j];
						B[j+1][k] = A[k][j+1];
						B[j+2][k] = A[k][j+2];
						B[j+3][k] = A[k][j+3];

						// save B to right half of buffer
						t4 = A[k][j+4];
						t5 = A[k][j+5];
						t6 = A[k][j+6];
						t7 = A[k][j+7];
						B[k-i][4] = t4;
						B[k-i][5] = t5;
						B[k-i][6] = t6;
						B[k-i][7] = t7;
					}

					// bottom four lines [C D]
					for (k = i + 4; k < i + 8; k++) {
						// save C to left half of buffer	
						t0 = A[k][j];
						t1 = A[k][j+1];
						t2 = A[k][j+2];
						t3 = A[k][j+3];

						B[k-i-4][0] = t0;
						B[k-i-4][1] = t1;
						B[k-i-4][2] = t2;
						B[k-i-4][3] = t3;

						// transpose D directly
						B[j+4][k] = A[k][j+4];
						B[j+5][k] = A[k][j+5];
						B[j+6][k] = A[k][j+6];
						B[j+7][k] = A[k][j+7];
					}

					// transpose B
					for (l = 0; l < 4; l++) {
						t4 = B[l][4];
						t5 = B[l][5];
						t6 = B[l][6];
						t7 = B[l][7];

						B[j+4+l][k] = t4;
						B[j+4+l][k+1] = t5;
						B[j+4+l][k+2] = t6;
						B[j+4+l][k+3] = t7;
					}

					// transpose C
					for (l = 0; l < 4; l++) {
						t0 = B[l][0];
						t1 = B[l][1];
						t2 = B[l][2];
						t3 = B[l][3];

						B[j+l][k+4] = t0;
						B[j+l][k+5] = t1;
						B[j+l][k+6] = t2;
						B[j+l][k+7] = t3;
					}


				}

			} // end of upper triangular blocks

			/* diagonal blocks except (7, 7)
			 * use lower half block (7, 7) as buffer
			 * i.e. (60, 56) to (63, 63)
			 */
			if (i == j && i != 56) {
				// copy A and B to buffer
				for (k = i; k < i + 4; k++) {
					t0 = A[k][j];
					t1 = A[k][j+1];
					t2 = A[k][j+2];
					t3 = A[k][j+3];
					t4 = A[k][j+4];
					t5 = A[k][j+5];
					t6 = A[k][j+6];
					t7 = A[k][j+7];

					B[k-i+60][56] = t0;
					B[k-i+60][57] = t1;
					B[k-i+60][58] = t2;
					B[k-i+60][59] = t3;
					B[k-i+60][60] = t4;
					B[k-i+60][61] = t5;
					B[k-i+60][62] = t6;
					B[k-i+60][63] = t7;
				}

				// transpose A and B
				for (k = i; k < i + 4; k++) {
					t0 = B[k-i+60][56];
					t1 = B[k-i+60][57];
					t2 = B[k-i+60][58];
					t3 = B[k-i+60][59];
					t4 = B[k-i+60][60];
					t5 = B[k-i+60][61];
					t6 = B[k-i+60][62];
					t7 = B[k-i+60][63];

					B[j][k] = t0;
					B[j+1][k] = t1;
					B[j+2][k] = t2;
					B[j+3][k] = t3;
					B[j+4][k] = t4;
					B[j+5][k] = t5;
					B[j+6][k] = t6;
					B[j+7][k] = t7;
				}

				// copy C and D to buffer
				for (k = i + 4; k < i + 8; k++) {
					t0 = A[k][j];
					t1 = A[k][j+1];
					t2 = A[k][j+2];
					t3 = A[k][j+3];
					t4 = A[k][j+4];
					t5 = A[k][j+5];
					t6 = A[k][j+6];
					t7 = A[k][j+7];

					B[k-i-4+60][56] = t0;
					B[k-i-4+60][57] = t1;
					B[k-i-4+60][58] = t2;
					B[k-i-4+60][59] = t3;
					B[k-i-4+60][60] = t4;
					B[k-i-4+60][61] = t5;
					B[k-i-4+60][62] = t6;
					B[k-i-4+60][63] = t7;
				}

				// transpose C and D
				for (k = i + 4; k < i + 8; k++) {
					// transpose C
					t0 = B[k-i-4+60][56];
					t1 = B[k-i-4+60][57];
					t2 = B[k-i-4+60][58];
					t3 = B[k-i-4+60][59];
				
					B[j][k] = t0;
					B[j+1][k] = t1;
					B[j+2][k] = t2;
					B[j+3][k] = t3;

					// transpose D 
					t4 = B[k-i-4+60][60];
					t5 = B[k-i-4+60][61];
					t6 = B[k-i-4+60][62];
					t7 = B[k-i-4+60][63];
					
					B[j+4][k] = t4;
					B[j+5][k] = t5;
					B[j+6][k] = t6;
					B[j+7][k] = t7;
				}

			}

			/* the last block (7, 7)
			 * I have to accept the penalties sadly
			 */
			if (i == j && i == 56) {
				// transpose the diagonal elements of A and D
				t0 = A[i][j];
				t1 = A[i+1][j+1];
				t2 = A[i+2][j+2];
				t3 = A[i+3][j+3];
				t4 = A[i+4][j+4];
				t5 = A[i+5][j+5];
				t6 = A[i+6][j+6];
				t7 = A[i+7][j+7];

				B[j][i] = t0;
				B[j+1][i+1] = t1;
				B[j+2][i+2] = t2;
				B[j+3][i+3] = t3;
				B[j+4][i+4] = t4;
				B[j+5][i+5] = t5;
				B[j+6][i+6] = t6;
				B[j+7][i+7] = t7;
				
				// transpose the diagonal elements of B and C
				t0 = A[i][j+4];
				t1 = A[i+1][j+5];
				t0 = A[i+2][j+6];
				t0 = A[i+3][j+7];
				t4 = A[i+4][j];
				t5 = A[i+5][j+1];
				t6 = A[i+6][j+2];
				t7 = A[i+7][j+3];

				B[j+4][i] = t0;
				B[j+5][i+1] = t1;
				B[j+6][i+2] = t2;
				B[j+7][i+3] = t3;
				B[j][i+4] = t4;
				B[j+1][i+5] = t5;
				B[j+2][i+6] = t6;
				B[j+3][i+7] = t7;

				// transpose everything else directly
				for (k = i; k < i + 8; k++) {
					for (l = j; l < j + 8; l++) {	
						if (k != l && k != l + 4 && k != l - 4) {
							B[l][k] = A[k][l];
						}

					}
				}
			}


		} // end of j loop
	} // end of i loop

}


void transpose_64_version1(int M, int N, int A[N][M], int B[M][N]) {
	int diag;
	int i, j, k, l, p, q;
			
	for (i = 0; i < N; i += 8) {
		for (j = 0; j < M; j += 8) {
			for (k = i; k < i + 8; k += 4) {
				for (l = j; l < j +8; l += 4) {
					for (p = k; p < k +4; p++) {
						for (q = l; q < l + 4; q++) {
							if (i == j) {
								// upper left and lower right
								if (k == l) {
									if (p == q)
										diag = A[p][q];
									else
										B[q][p] = A[p][q];
								}
								// upper right
								else if (k == l - 4) {
									if (q == p + 4)
										diag = A[p][q];
									else
										B[q][p] = A[p][q];
								}
								// lower left
								else {
									if (q == p - 4)
										diag = A[p][q];
									else
										B[q][p] = A[p][q];
								}
							} else {
								B[q][p] = A[p][q];
							}
						}

						if (i == j) {
							if (k == l)
								B[p][p] = diag;
							else if (k == l - 4)
								B[p+4][p] = diag;
							else
								B[p-4][p] = diag;
						}
					}
				}
			}
		}
	} 

}

void transpose_ireg(int M, int N, int A[N][M], int B[M][N]) {
	int a = 16, b = 4;
	int diag;
	int i, j, k, l;

	for (i = 0; i < N; i += a) {
		for (j = 0; j < M; j += b) {
			for (k = i; k < ((i + a < N) ? (i + a) : N); k++) {
				for (l = j; l < ((j + b < M) ? (j + b) : M); l++) {
					if (i == j && k == l)
						diag = A[k][l];
					else
						B[l][k] = A[k][l];
				}
				if (i == j)
					B[k][k] = diag;
			}
		}
	}
}
