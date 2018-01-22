#include <stdio.h>
#include <omp.h>
#define MAX_THREADS 16
static long num_steps = 100000000; double step;
int main ()
{ int j; double start_time, run_time;  step = 1.0/(double) num_steps;
  double pi = 0.0;  double sum;
  for (j=1;j<=MAX_THREADS ;j++) {                      1 -> 0.919905 secs
    omp_set_num_threads(j);	 		       2 -> 0.462154 secs
    start_time = omp_get_wtime();		       3 -> 0.309200 secs
    sum = 0.0; 			 		       4 -> 0.230493 secs
    pi = 0.0; // IMP                                   5 -> 0.186146 secs
    #pragma omp parallel			       6 -> 0.169749 secs
    { int i;   					       7 -> 0.131675 secs
      int id = omp_get_thread_num();		       8 -> 0.133439 secs
      int numthreads = omp_get_num_threads();	       9 -> 0.102678 secs
      double x;		  			      10 -> 0.092414 secs
      //double sum; // this is where accum happens    11 -> 0.083937 secs
      if (id == 0)	  			      12 -> 0.076848 secs
	printf(" num_threads = %d",numthreads);	      13 -> 0.113573 secs
      // threads share work, divide work eql (static) 14 -> 0.105807 secs
      #pragma omp for reduction(+:sum)		      15 -> 0.100549 secs
      for (i=0; i < num_steps; i++){		      16 -> 0.091065 secs
	x = (i+0.5)*step;
	sum = sum + 4.0/(1.0+x*x);
    }}
    pi = step * sum; run_time = omp_get_wtime() - start_time; printf("\n pi... ");
}}
