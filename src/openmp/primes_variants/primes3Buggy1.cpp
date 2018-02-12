#include <iostream>
#include <cmath>

using namespace std;

int main() {
  /*
  int numPrimes = 0;
  int numP41 = 0;
  int numP43 = 0;
  */
  int numPrimes, numP41, numP43;
  
#pragma omp parallel
{
#pragma omp for schedule(dynamic, 100000)	\
  reduction(+:numPrimes, numP41, numP43)
  for(int i = 3; i <= 1000000; i += 2)
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
