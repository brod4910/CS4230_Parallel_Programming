// Adapted from Chapter 1 of http://heather.cs.ucdavis.edu/parprocbook
// Thread-based program to find the number of primes between 2 and n;
// uses the Sieve of Eratosthenes, deleting all multiples of 2, all
// multiples of 3, all multiples of 5, etc.

// Mainly for illustration
// Compilation:  gcc -g -o iP iP.c -lpthread -lm

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <limits.h>

#define MAX_THREADS 50
#define MAX_N 1000000000

// shared variables

// problem size
int n;         // range to check for primeness

// divide and conquer
int nthreads;  // number of threads (not counting main())

// algorithm specific
int nextbase;  // next sieve multiplier to be used

// solution storage
bool prime[MAX_N+1];  // in the end, prime[i] = 1 if i prime, else 0

// lock for the shared variable nextbase
pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;

// ID structs for the threads
pthread_t id[MAX_THREADS];

typedef struct {
  int tid;
  int work;
} TID_WORK;


// "crosses out" all odd multiples of numbers in the range k, k+2, ..., k + 2 * (BaseMult - 1)
void crossout(int k, int tn) {
    printf("%i\n", tn); // functionally un-used variable
    for (int i = 3; k*i <= n; i += 2)  {
      printf("i : %d, k : %d, k*i : %d \n", i, k, k*i);
      printf("Thread %d crosses out %d * %d \n", tn, i, k);
      prime[k*i] = 0;
   }
}

// each thread runs this routine
void *worker(void *ptr)
{
  // We malloc a cell so that we can pass it back after our work is done.
  // Passing a ref. to an automatic variable after the function returns is not recommended.

  TID_WORK *Ptid_work = *((TID_WORK **) ptr);

  // tn is the ptr to the thread number (0,1,...)
  int tn = Ptid_work->tid;

  // no need to check multipliers bigger than sqrt(n)
  int lim = sqrt(n);

  int base;

    do  {
      // Get next sieve multiplier, avoiding duplication across threads
      // There are many issues surrounding this lock.
      pthread_mutex_lock(&nextbaselock);
      base = nextbase;
      nextbase += 2;
      // unlock
      pthread_mutex_unlock(&nextbaselock);

      //if (Ptid_work->tid == 0) nanosleep(&ts, NULL);
      //if (Ptid_work->tid == 1) nanosleep(&ts, NULL);
      //if (Ptid_work->tid == 2) nanosleep(&ts, NULL);

      if (base <= lim) {
	// don't bother crossing out if base known composite
	if (prime[base])  {
	  crossout(base, tn);
	  //printf("work for thread %d is being ++\n",(Ptid_work->tid));
	  Ptid_work->work++;
	}
      }
      else pthread_exit(NULL);
   } while (1);
}

int main(int argc, char **argv){

  printf("argc : %i\n",argc);
  for (int i = 0; i < argc; i++) {
    printf("argv[%d] : %s\n", i, argv[i] );
  }

  TID_WORK **Ptid_work;

  // global variables loaded my main thread
  n        = atoi(argv[1]);
  nthreads = atoi(argv[2]);

  // mark all even numbers nonprime, and the rest "prime until shown otherwise"
  for (int i = 3; i <= n; i++)  {
      if (i%2 == 0) prime[i] = 0;
      else prime[i] = 1;
  }
  nextbase = 3;

  // get threads started
  Ptid_work = (TID_WORK **) malloc(sizeof(TID_WORK) * nthreads);

  for (int i = 0; i < nthreads; i++)  {
    Ptid_work[i] = (TID_WORK *) malloc(sizeof(TID_WORK));
    Ptid_work[i]->tid = i;
    Ptid_work[i]->work = 0;
    pthread_create(&id[i], NULL, (void *) worker, (void *) &Ptid_work[i]);
  }

  // wait for all done
  for (int i = 0; i < nthreads; i++)  {
    // this call says wait until thread number id[i] finishes
    // execution, and to assign the return value of that thread to our
    // local variable work here

    pthread_join(id[i], NULL);

    printf("Thread %d does %d amount of work\n", Ptid_work[i]->tid,Ptid_work[i]->work);
   }

   free(Ptid_work);

  // number of primes found
  int nprimes = 1;

   //printf("the primes found are:");
   for (int i = 3; i <= n; i++)
      if (prime[i])  {
        //printf("%d ", i);
	       nprimes++;
      }

   printf("\nthe number of primes found was %d\n",nprimes);
   return 0;
}
