#include <omp.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "tbb/tbb.h"

using namespace std;

int thread_count = 1;
size_t primes_range = 0;
int chunk_size = 10;
int parallel_method;

struct Primes
{
	void operator()(const tbb::blocked_range<size_t>& range) const
	{
		for(size_t i = range.begin(); i != range.end(); i+=2)
		{

		}
	}
};

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
	if (argc != 3) 
	{
		Usage(argv[0], 0);
	}

	thread_count = strtol(argv[1], NULL, 10);  
		
	sscanf(argv[2], "%zu", &primes_range);
}  

void primes_array()
{
	int *sols = new int[thread_count] ();

	#pragma omp parallel for num_threads(thread_count) schedule(dynamic, chunk_size)
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

	delete [] sols;
}

void primes_concurrent_vector()
{
	tbb::concurrent_vector<int> primes;
	Primes prime;
	tbb::parallel_for(tbb::blocked_range<size_t>(size_t(3), primes_range),  prime);
}

void primes_boolean_vector()
{
	vector<bool> primes(thread_count);

	#pragma omp parallel for num_threads(thread_count) schedule(dynamic, chunk_size)
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
			#pragma omp critical
			primes.at(tid) = true;
		}
	}

	for(int i = 0; i < thread_count;i++)
	{
		if(primes.at(i))
		{
			cout << "Thread number " << i << " found a prime" << endl;
		}
		else
		{
			cout << "Thread number " << i << " did not find a prime" << endl;
		}
	}	
}

int main(int argc, char* argv[])
{

	Get_args(argc, argv);
	
	cout << "Thread count and primes range: " << thread_count 
	<< ", " << primes_range << endl;

	cout << "Enter chunk size for each thread..." << endl;

	cin >> chunk_size;

	cout << "Enter 1, 2, 3 for desired parallel method..." << endl;
	cout << "1: primes stored in a bit array" << endl;
	cout << "2: primes stored in a concurrent vector" << endl;
	cout << "3: primes stored in a boolean vector" << endl;

	cin >> parallel_method;

	if(parallel_method == 1)
	{
		primes_array();
	}
	else if(parallel_method == 2)
	{
		primes_concurrent_vector();
	}
	else if(parallel_method == 3)
	{
		primes_boolean_vector();
	}
	else
	{
		cout << "Invalid parallel method..." << endl;
		exit(0);
	}
}