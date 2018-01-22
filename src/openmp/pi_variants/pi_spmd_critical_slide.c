#include <stdio.h>//Tim Mattson, 11/99. Modified by Ganesh.
#include <omp.h>
#define MAX_THREADS 4
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

    pi = 0.0; // IMPORTANT
    #pragma omp parallel
    {
      int i;
      int id = omp_get_thread_num();
      int numthreads = omp_get_num_threads();
      double x;
      double sum; // accum                                1 -> 0.921731 secs
			  				  2 -> 0.463312 secs
      //          Decl pi here, won't be seen by printf   3 -> 0.340936 secs
							  4 -> 0.253653 secs
      if (id == 0)					  5 -> 0.214674 secs
	printf(" num_threads = %d",numthreads);		  6 -> 0.153863 secs
							  7 -> 0.131804 secs
      for (i=id, sum = 0.0; i< num_steps; i+=numthreads){ 8 -> 0.115371 secs
	x = (i+0.5)*step;				  9 -> 0.102932 secs
	sum = sum + 4.0/(1.0+x*x);			  10 -> 0.092284 secs
      }							  11 -> 0.085565 secs
							  12 -> 0.077253 secs
      #pragma omp critical				  13 -> 0.114608 secs
      pi += step * sum;					  14 -> 0.112714 secs
    }							  15 -> 0.108695 secs
							  16 -> 0.095081 secs
    run_time = omp_get_wtime() - start_time;
    printf("\n pi is %f in %f seconds %d thrds \n",pi,run_time,j);
  }
}
