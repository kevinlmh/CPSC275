/*
 * Matrix multiplication example with pthreads
 *
 * Compile it with:
 *
 *    $ gcc -o matmul_threaded matmul_threaded.c -lpthread
 *
 * Run it with:
 * 
 *    $ ./matmul_threaded <matrix dimension> <#threads>
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>

double *a, *b, *c;
int numThreads, N;

void *mmul(void *id) {
  long myId = (long) id;
  int i, j, k;
  double sum;

  // compute bounds for this threads
  int startrow = myId * N/numThreads;
  int endrow = (myId+1) * (N/numThreads) - 1;

  // matrix mult over the strip of rows for this thread
  for (i = startrow; i <= endrow; i++) {
    for (j = 0; j < N; j++) {
      sum = 0.0;
      for (k = 0; k < N; k++) {
	      sum = sum + a[i*N+k] * b[k*N+j];
      }
      c[i*N+j] = sum;
    }
  }
}

int main(int argc, char *argv[]) {
  long i, j;
  pthread_t *threads;

  N = atoi(argv[1]); // matrix dimension
  numThreads = atoi(argv[2]); // number of threads
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
