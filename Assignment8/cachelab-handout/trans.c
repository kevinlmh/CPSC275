/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 *
 * Author: Kevin Liu
 * Date: Nov 11 2014
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

/*
 * transpose_64 - this function is designed specifically for
 *                optimizing 64 x 64 case
 */
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

/*
 * transpose_ireg - this function is designed to optimize irregular
 *                  cases
 */
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
