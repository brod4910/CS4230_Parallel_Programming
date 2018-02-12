#include <omp.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

int thread_count = 1;
unsigned long long primes_range = 0;
int chunk_size = 10;

void Usage(char *prog_name, int printCase) 
{
	if(printCase == 0)
	{
		fprintf(stderr, "Not Enough arugments. Thread count, primes range and chunk size are required\n");	
	}

	exit(0);
}  /* Usage */

void Get_args(int argc, char **argv) 
{
	if (argc != 4) 
	{
		Usage(argv[0], 0);
	}

	thread_count = strtol(argv[1], NULL, 10);  
		
	primes_range = strtoull(argv[2], NULL, 10);

	chunk_size = stoi(argv[3], NULL, 10);
}  

int main(int argc, char* argv[])
{

	Get_args(argc, argv);
	
	int *sols = new int[thread_count] ();

	cout << "Thread count, primes range and chunk size are: " << thread_count 
	<< ", " << primes_range << ", " << chunk_size << endl;

	int numPrimes = 0, numP41 = 0, numP43 = 0;

	#pragma omp parallel for num_threads(thread_count) schedule(guided)
		// reduction(+:numPrimes, numP41, numP43)

	for(size_t i = 3; i <= primes_range; i += 2)
	{
		int limit, prime, tid;

		tid = omp_get_thread_num();
		limit = (int)sqrt((float)i) + 1;
		prime = 1; // assume number is prime
		int j = 3;

		while(prime && (j <= limit))
		{
			if(i % j == 0)
			{
				prime = 0;
			}

			j += 2;
		}

		if(prime)
		{
			numPrimes++;
			// if(i % 4 == 1)
			// {
			// 	numP41++;
			// }
			// else if(i % 4 == 3)
			// {
			// 	numP43++;
			// }

			#pragma omp critical
			sols[tid] = 1;
		}
	}

	for(int i = 0; i < thread_count;i++)
	{
		if(sols[i] == 1)
		{
			cout << "Thread number " << i << " found a prime" << endl;
		}
		else
		{
			cout << "Thread number " << i << " did not find a prime" << endl;
		}
	}
}