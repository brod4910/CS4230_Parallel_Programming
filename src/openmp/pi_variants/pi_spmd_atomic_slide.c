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

		    History: Written by Tim Mattson, 11/99. Modified by Ganesh.
*/
#include <stdio.h>
#include <omp.h>
#define MAX_THREADS 16
static long num_steps = 100000000;
double step;
int main ()
{
  int j;
  double start_time, run_time;
  step = 1.0/(double) num_steps;
  double pi = 0.0;
  for (j=1;j<=MAX_THREADS ;j++) {
    omp_set_num_threads(j);
    start_time = omp_get_wtime();

    pi = 0.0; //  IMPORTANT

          #pragma omp parallel
    {
      int i;
      int id = omp_get_thread_num();
      int numthreads = omp_get_num_threads();
      double x;
      double sum; // this is where accumulation will happen first

      // Try declaring pi here; won't be seen by final printf!
							        1 -> 0.921926 secs
      if (id == 0)					        2 -> 0.463495 secs
	printf(" num_threads = %d",numthreads);		        3 -> 0.307760 secs
							        4 -> 0.240112 secs
      for (i=id, sum = 0.0; i< num_steps; i+=numthreads){       5 -> 0.232079 secs
	x = (i+0.5)*step;				        6 -> 0.154659 secs
	sum = sum + 4.0/(1.0+x*x);			        7 -> 0.153942 secs
      }							        8 -> 0.115406 secs
      sum = sum * step;					        9 -> 0.102532 secs
							       10 -> 0.092301 secs
      #pragma omp atomic				       11 -> 0.083997 secs
      pi +=  sum;					       12 -> 0.077011 secs
    }							       13 -> 0.111017 secs
							       14 -> 0.113270 secs
    run_time = omp_get_wtime() - start_time;		       15 -> 0.102988 secs
    printf("\n pi .. ");                                       16 -> 0.095126 secs
  }
}
