#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <omp.h>
using namespace std;
int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "Plz provide # threads and prime range" << endl;
    exit(EXIT_FAILURE);
  }
  int thread_count = strtol(argv[1], NULL, 10);
  int primes_range = strtol(argv[2], NULL, 10);
  cout << "thread_count and primes_range are " << thread_count
       << ", " << primes_range << endl;
  int numPrimes = 0, numP41 = 0, numP43 = 0; // BUG if init omitted!!
#pragma omp parallel num_threads(thread_count)
{
#pragma omp for schedule(dynamic, 1000000)	\
    reduction(+:numPrimes, numP41, numP43)
  for(int i = 3; i <= primes_range; i += 2)
    { int limit, prime;
      limit = (int) sqrt((float)i) + 1;
      prime = 1; // assume number is prime
      int j = 3;
      while (prime && (j <= limit))
	{
	  if (i%j == 0) prime = 0;
	  j += 2;
	}
      if (prime)
	{
	  numPrimes++;
	  if (i%4 == 1) numP41++;  // 4k+1 primes
	  if (i%4 == 3) numP43++;  // 4k-1 primes
	}
    }
 }
 cout << "Num primes is:" << numPrimes << endl;
 cout << "numP41 is:" << numP41 << endl;
 cout << "numP43 is:" << numP43 << endl;
}
/*
 time primes3.exe 16 40000000
thread_count and primes_range are 16, 40000000
Num primes is:2433653
numP41 is:1216687
numP43 is:1216966
real    0m3.777s
user    0m39.992s
sys     0m0.000s
*/
