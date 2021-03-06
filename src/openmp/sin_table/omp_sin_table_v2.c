// g++ -fopenmp sin.c and then a.out
// From http://bisqwit.iki.fi/story/howto/openmp/
//
#include <stdio.h>
#include <math.h>
int main()
{
  const int size = 16;
  double sinTable[size];
   
#pragma omp parallel
  #pragma omp for
  for(int n=0; n<size; ++n)
    sinTable[n] = sin(2 * M_PI * n / size);
  // the table is now initialized

  // ILL-INFORMED! Why? Because the 'parallel' above does not apply here
  #pragma omp for  
  for (int i=0; i < size; ++i)
    {
      printf("Thread %d: [%d, %f]\n", omp_get_thread_num(), i, sinTable[i]);
    }
}
