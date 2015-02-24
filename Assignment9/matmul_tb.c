/*
 * File: matmul_tb.c
 *
 * Author: Kevin Liu
 * Date: Nov 23 2014
 *
 * Blocked Matrix multiplication with pthreads
 *
 * Compile it with:
 *
 *    $ gcc -o matmul_tb matmul_tb.c -lpthread
 *
 * Run it with:
 * 
 *    $ ./matmul_tb <matrix dimension> <block size> <#threads>
 *
 * 				Performance table
 *				=================
 * Matrix size: 512
 * Block size: 32 (if applicable)
 * # of threads: 8 (if applicable)
 *
 * Sequential	Blocked		Threaded	Blocked and Threaded
 * 2.139s		2.165s		0.576s		0.592s
 *
 * Matrix size: 1024
 * Block size: 32 (if applicable)
 * # of threads: 8 (if applicable)
 *
 * Sequential	Blocked		Threaded	Blocked and Threaded
 * 26.723s		17.134s		6.932s		4.432s	
 *
 * Matrix size: 2048
 * Block size: 32 (if applicable)
 * # of threads: 16 (if applicable)
 *
 * Sequential	Blocked		Threaded	Blocked and Threaded
 * too long		2m9.884s	1m37.029s	1m6.4868s		
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>

double *a, *b, *c;
int numThreads, N, B;

void *mmul(void *id) {
  long myId = (long) id;
  int i, j, k, i1, j1, k1;

  // compute bounds for this threads
  int startrow = myId * N/numThreads;
  int endrow = (myId+1) * (N/numThreads) - 1;

  // matrix mult over the strip of rows for this thread
  for (i = startrow; i <= endrow; i += B) {
    for (j = 0; j < N; j += B) {
	  for (k = 0; k < N; k += B) {
	    for (i1 = i; i1 < i + B; i1++) {
	      for (j1 = j; j1 < j + B; j1++) {
		    for (k1 = k; k1 < k + B; k1++) {
		      c[i1*N+j1] += a[i1*N+k1] * b[k1*N+j1];
	        }
		  }
        }
	  }
	}
  }
}

int main(int argc, char *argv[]) {
  long i, j;
  pthread_t *threads;
	
  if (argc != 4) {
    printf("Usage: %s <matrix dimension> <block size> <#threads>\n", argv[0]);
    exit(1);
  }
  N = atoi(argv[1]); // matrix dimension
  B = atoi(argv[2]); // block size
  numThreads = atoi(argv[3]); // number of threads
  a = (double *) malloc (N*N*sizeof(double));
  b = (double *) malloc (N*N*sizeof(double));
  c = (double *) malloc (N*N*sizeof(double));
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      a[i*N+j] = i + j;
      b[i*N+j] = i + j;
    }

  // Allocate thread handles
  threads = (pthread_t *) malloc(numThreads * sizeof(pthread_t));

  // Create threads 
  for (i = 0; i < numThreads; i++) {
    pthread_create(&threads[i], NULL, mmul, (void *)(i));
  }

  // Wait for threads 
  for (i = 0; i < numThreads; i++) {
    pthread_join(threads[i], NULL);
  }
}
