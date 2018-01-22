#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "timer.h"

int A[1024]; // This array will be operated upon by many threads

int Pad;     // global that determines how far apart threads access mem

void* Thr_fn(void* rank);

int main(int argc, char **argv) {

  printf("argc : %d\n",argc);
  for(int i; i < argc; ++i)
    printf("argv %i : %s",i,argv[i]);

  printf("\nPlease provide thread padding and nthreads:\n");
  int Nthr;
  scanf("%d %d", &Pad, &Nthr);

  printf("Padding : %i Threads : %i \n", Pad, Nthr);

  pthread_t* thr_h = (pthread_t*) malloc (Nthr*sizeof(pthread_t));

  double start;
  GET_TIME(start);

  long thr; // Long in case of a 64-bit system
  for (thr = 0; thr < Nthr; ++thr)
    pthread_create(&thr_h[thr], NULL, Thr_fn, (void *)thr);

  for (thr = 0; thr < Nthr; ++thr)
    pthread_join(thr_h[thr], NULL);

  double finish;
  GET_TIME(finish);

  double elapsed = finish - start;
  printf("The elapsed time is %e seconds\n", elapsed);

  return 0;
}

void *Thr_fn(void *rank) {
  int my_rank = (long) rank;

  for (long i=0; i<1024*1048576; ++i) { // 2^20
    A[my_rank*Pad]++;
  }

  return NULL;
}
