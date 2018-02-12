// g++ -fopenmp sin.c and then a.out
// From http://bisqwit.iki.fi/story/howto/openmp/
//
#include <stdio.h>
#include <math.h>
int main()
{
  const int size = 65536 * 16;
  double sinTable[size];
   
  //#pragma omp parallel for
  for(int n=0; n<size; ++n)
    sinTable[n] = sin(2 * M_PI * n / size);
  // the table is now initialized
  
  for (int i=0; i < size; ++i)
    //printf("sinTable[%i] = %f\n", i, sinTable[i]);
    printf("%i %f\n", i, sinTable[i]);
}
