#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "timer.h"

int A[1024]; // This array will be operated upon by many threads

int Pad;     // global that determines how far apart threads access mem

void* Thr_fn(void* rank);

int main(int argc, char **argv) {
  
  printf("argc %d\n",argc);
  for(int i; i < argc; ++i)
    printf("argv %i %s",i,argv[i]);

  int Nthr;
  long thr; // Long in case of a 64-bit system
  
  double start, finish, elapsed; // timing vars
  
  printf("\nPlease provide thread padding, nthreads:\n");
  scanf("%d %d", &Pad, &Nthr);
  
  pthread_t* thr_h = (pthread_t*) malloc (Nthr*sizeof(pthread_t));
  
  GET_TIME(start);
  
  for (thr = 0; thr < Nthr; ++thr)
    pthread_create(&thr_h[thr], NULL, Thr_fn, (void *)thr);
  
  for (thr = 0; thr < Nthr; ++thr)
    pthread_join(thr_h[thr], NULL);
  
  GET_TIME(finish);
  
  elapsed = finish - start;
  printf("The elapsed time is %e seconds\n", elapsed);

  return 0;
}

void *Thr_fn(void *rank) {
  int my_rank = (long) rank;
  printf("Thread %i : Start Increment\n",my_rank);
  for (long i=0; i<1024*1048576; ++i) { // 2^20
    A[my_rank*Pad]++;
  }
  printf("Thread %i : Completed Increment\n",my_rank);

  return NULL;
}
