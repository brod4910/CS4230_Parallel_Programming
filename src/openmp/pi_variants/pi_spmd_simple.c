/*

NAME: PI SPMD ... a simple version.

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The program was parallelized using OpenMP and an SPMD 
algorithm.  The following OpenMP specific lines were 
added: 

(1) A line to include omp.h -- the include file that 
contains OpenMP's function prototypes and constants.

(2) A pragma that tells OpenMP to create a team of threads
with an integer variable i being created for each thread.

(3) two function calls: one to get the thread ID (ranging
from 0 to one less than the number of threads), and the other
returning the total number of threads.

(4) A cyclic distribution of the loop by changing loop control
expressions to run from the thread ID incremented by the number 
of threads.  Local sums accumlated into sum[id].

Note that this program will show low performance due to 
false sharing.  In particular, sum[id] is unique to each
thread, but adfacent values of this array share a cache line
causing cache thrashing as the program runs.

History: Written by Tim Mattson, 11/99.

*/

#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 16

static long num_steps = 100000000;
double step;
int main ()
{
	  int i,j;
	  double pi, full_sum = 0.0;
	  double start_time, run_time;
	  double sum[MAX_THREADS];

	  step = 1.0/(double) num_steps;


   for (j=1;j<=MAX_THREADS ;j++) {

      omp_set_num_threads(j);
      full_sum=0.0;
      start_time = omp_get_wtime();

      #pragma omp parallel
      {
        int i;
	  int id = omp_get_thread_num();
	  int numthreads = omp_get_num_threads();
	  double x;

	  sum[id] = 0.0;

        if (id == 0) 
             printf(" num_threads = %d",numthreads);

	  for (i=id;i< num_steps; i+=numthreads){ 
		  x = (i+0.5)*step;
		  sum[id] = sum[id] + 4.0/(1.0+x*x);
	  }
      }

	for(full_sum = 0.0, i=0;i<j;i++)
	    full_sum += sum[i];

      pi = step * full_sum;
      run_time = omp_get_wtime() - start_time;
      printf("\n pi is %f in %f seconds %d thrds \n",pi,run_time,j);
   }
}	  

/*
ganesh@fractus:~/CS_4230/src/openmp/pi_variants$ !531
pi_spmd_simple.exe 
 num_threads = 1
 pi is 3.141593 in 0.921829 seconds 1 thrds 
 num_threads = 2
 pi is 3.141593 in 1.161996 seconds 2 thrds 
 num_threads = 3
 pi is 3.141593 in 0.905224 seconds 3 thrds 
 num_threads = 4
 pi is 3.141593 in 0.817901 seconds 4 thrds 
 num_threads = 5
 pi is 3.141593 in 0.809095 seconds 5 thrds 
 num_threads = 6
 pi is 3.141593 in 0.777051 seconds 6 thrds 
 num_threads = 7
 pi is 3.141593 in 0.655344 seconds 7 thrds 
 num_threads = 8
 pi is 3.141593 in 0.683927 seconds 8 thrds 
 num_threads = 9
 pi is 3.141593 in 0.755808 seconds 9 thrds 
 num_threads = 10
 pi is 3.141593 in 0.777262 seconds 10 thrds 
 num_threads = 11
 pi is 3.141593 in 0.826489 seconds 11 thrds 
 num_threads = 12
 pi is 3.141593 in 0.905883 seconds 12 thrds 
 num_threads = 13
 pi is 3.141593 in 0.892053 seconds 13 thrds 
 num_threads = 14
 pi is 3.141593 in 1.034504 seconds 14 thrds 
 num_threads = 15
 pi is 3.141593 in 1.149505 seconds 15 thrds 
 num_threads = 16
 pi is 3.141593 in 1.310348 seconds 16 thrds 
ganesh@fractus:~/CS_4230/src/openmp/pi_variants$ h

*/
