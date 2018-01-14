#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "timer.h"

int A[1024]; // This array will be operated upon by many threads
int padding; // Another that determines how far apart threads access memory

void *Thr_fn(void *rank) {
  int my_rank = (long) rank;
  printf("Thread : %i\n", my_rank);
  for (long i = 0; i < 1024*1048576; i++) {
    printf("my_rank %i ", my_rank);
    printf("padding %i\n", padding);
    printf("my_rank * padding %i\n", my_rank * padding);
    printf("address %p data %i ", &A[my_rank*Pad], A[my_rank*Pad] );
    A[my_rank*padding]++;
    printf("--> address %p data %i \n", &A[my_rank*Pad], A[my_rank*Pad] );
  }
  return NULL;
}

int main(int argc, char const *argv[]) {

  // avoid any unused variable, also visual check of the user preferences
  printf("argc %d\n", argc);
  for (size_t i = 0; i < count; i++)
    printf("argv[%d] %s\n", i, argv[i]);
  }

  // obtain user preferences
  padding = argv[0];
  num_threads = argv[1];

  // create posix thread object
  pthread_t* thr_h = (pthread_t*) malloc(num_threads * sizeof(pthread_t));

  // start timer
  double start;
  GET_TIME(start);

  // spawn number of threads
  for (size_t i = 0; i < num_threads; i++) {
    pthread_create(&thr_h[thr], NULL, Thr_fn, (void*)thr);
  }

  // join all the threads
  pthread_join(thr_h,NULL);

  // stop timer
  double finish;
  GET_TIME(finish);

  // obtain time spent
  double elapsed = finish - start;
  printf("time elapsed %e seconds\n", elapsed);

  return 0;
}
