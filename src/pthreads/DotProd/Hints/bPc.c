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

#define MAX_N 1000000000
#define MAX_THREADS 50

// shared variables
int nthreads;  // number of threads (not counting main())
int n;         // range to check for primeness
int nextbase;  // next sieve multiplier to be used
bool prime[MAX_N+1];  // in the end, prime[i] = 1 if i prime, else 0

// lock for the shared variable nextbase
pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;
// ID structs for the threads
pthread_t id[MAX_THREADS];

typedef struct
{
  int tid;
  int work;
} TID_WORK;
  

// "crosses out" all odd multiples of numbers in the range k, k+2, ..., k + 2 * (BaseMult - 1)
void crossout(int k, int tn)
{  int i;
   for (i = 3; k*i <= n; i += 2)  {
     // printf("Thread %d crosses out %d * %d \n", tn, i, k);
     prime[k*i] = 0;
   }
}

// each thread runs this routine
void *worker(void *ptr) // tn is the ptr to the thread number (0,1,...)
{  int lim, base, tn;

  // We malloc a cell so that we can pass it back after
  // our work is done. Passing a ref. to an automatic variable
  // after the function returns is not recommended.

  TID_WORK *Ptid_work = *((TID_WORK **) ptr);

  tn = Ptid_work->tid;
  
   // no need to check multipliers bigger than sqrt(n)
   lim = sqrt(n);
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

int main(int argc, char **argv)
{ int nprimes;  // number of primes found
  TID_WORK **Ptid_work;
  
  int i;

  n = atoi(argv[1]);
  nthreads = atoi(argv[2]);

   // mark all even numbers nonprime, and the rest "prime until
   // shown otherwise"
   for (i = 3; i <= n; i++)  {
      if (i%2 == 0) prime[i] = 0;
      else prime[i] = 1;
   }
   nextbase = 3;
   // get threads started

   Ptid_work = (TID_WORK **) malloc(sizeof(TID_WORK) * nthreads);

   for (i = 0; i < nthreads; i++)  {

     Ptid_work[i] = (TID_WORK *) malloc(sizeof(TID_WORK));
     Ptid_work[i]->tid = i;
     Ptid_work[i]->work = 0;

     pthread_create(&id[i], NULL, (void *) worker, (void *) &Ptid_work[i]);
   }

   // wait for all done
   for (i = 0; i < nthreads; i++)  {
      // this call says wait until thread number id[i] finishes
      // execution, and to assign the return value of that thread to our
      // local variable work here

     pthread_join(id[i], NULL);

     printf("Thread %d does %d amount of work\n", Ptid_work[i]->tid, Ptid_work[i]->work);
   }

   free(Ptid_work);
   
   // report results
   nprimes = 1;
   //printf("the primes found are:");
   for (i = 3; i <= n; i++)
      if (prime[i])  {
	//printf("%d ", i);
	nprimes++;
      }
   printf("\nthe number of primes found was %d\n",nprimes);

   return 0;
}


