#include <omp.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <pthread.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>

const long MAX_EXP = 32;
const int MAX_THREADS = 1024;
const int DEFAULT_THREADS = 16;
size_t Size;
int Exp, Thres, Thread_Num;

typedef struct {
  size_t L;
  size_t H;
  int result;
  int numThreads;
} RNG;

// Global arrays over which DP is done
double *A;
double *B;
double *C;
double totRes = 0;
double presult = 0;

// lock for the shared variable nextbase
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void Usage(char *prog_name) {
   fprintf(stderr, "usage: %s <Exp>:int <Thres>:int\n", prog_name);
   fprintf(stderr, "Ensure that Thres <= pow(2, Exp)\n");
   fprintf(stderr, "Ensure that you input a thread number\n");
   exit(0);
}  /* Usage */

void Get_args(int argc, char **argv) {
   if (argc != 4) Usage(argv[0]);
   Exp = strtol(argv[1], NULL, 10);  
   if (Exp <= 0 || Exp > MAX_EXP) Usage(argv[0]);
   Thres = strtol(argv[2], NULL, 10);
   if (Thres < 1 || Thres >= (int) pow(2, Exp)) Usage(argv[0]);
   Thread_Num = strtol(argv[3], NULL, 10);
}  

double pdp(RNG myrng, int thread_c) 
{
	double result = 0;

	if(thread_c == 0)
	{
		thread_c = DEFAULT_THREADS;
	}

	#pragma omp parallel num_threads(thread_c)
	{
		// double localRes = 0;

		#pragma omp for schedule(dynamic, Thres) \
		reduction(+:result)
		for(size_t i = myrng.L; i <= myrng.H;i++)
		{
			C[i] = A[i] * B[i];
			result += C[i];
		}

		// #pragma omp atomic
		// result += localRes;
	}

	return result;
}

void time_pdp(RNG myrng)
{
	double for_overhead, pdp_time, totDuration, pow_overhead;
  int pow_count = 1;
	clock_t startTime;

  for(int i = 1; i <= Thread_Num;i++)
  {
  	printf("%s\n", "Threshold,Thread Size,Time(msec)");

		startTime = clock();
		for(int j = 0; j < 100; j++)
		{

		}
		for_overhead = (clock() - startTime) / (double)CLOCKS_PER_SEC;

    startTime = clock();
    for(int j = 2; j <= pow(2, Exp); j = pow(2, pow_count))
    {
      pow_count++;
    }
    pow_overhead = (clock() - startTime) / (double)CLOCKS_PER_SEC;

    pow_count = 1;

    for(int k = 2; k <= pow(2,Exp); k = pow(2, pow_count))
    {
      Thres = k;
  		for(int j = 0; j < 100;j++)
  		{
  			startTime = clock();
  			pdp(myrng, i);
  			pdp_time += (clock() - startTime) / (double)CLOCKS_PER_SEC;
  		}

  		pdp_time /= 100;

  		totDuration = pdp_time - (for_overhead + pow_overhead);

  		printf("%d,%d,%lf\n", pow_count, i, totDuration);

  		pdp_time = 0;
      pow_count++;
    }

    for_overhead = pow_overhead = 0;
	}
}

int main(int argc, char **argv) 
{
  
  Get_args(argc, argv);  
  Size = (int) pow(2, Exp);
  printf("Will do DP of %d sized arrays\n", Size);

  A = (double *) malloc(Size*sizeof(double));
  B = (double *) malloc(Size*sizeof(double));
  printf("Filling arrays now\n");
  srand(17); //Seed with 17
  for (size_t i=0; i<Size; ++i) {
    A[i] = rand()%16;
    B[i] = rand()%16;
  }
  // for(int i=0; i<Size; ++i) {
  //   printf("A[%d] and B[%d] are %f and %f\n",i,i,(double)A[i],(double)B[i]);
  // }

  RNG rng;
  rng.L = 0;
  rng.H = Size-1;
  rng.numThreads = 0;
  rng.result = 0;
  double serTot = 0;
  //printf("Serial dot product is %f\n", serdp(rng));
  
  printf("Now invoking parallel dot product\n");
  C = (double *) malloc(Size*sizeof(double));
  for(size_t i=0; i<Size; ++i) {
    C[i]=0;
  }
  //printf("Parallel DP = %f\n", pdp(rng));
  presult = pdp(rng, 0);


  for(size_t i=rng.L; i<=rng.H; ++i)
  {
    C[i] = A[i] * B[i];
    serTot += C[i];
  }

  printf("%s%f\n", "Final Result parallel C is: ", presult);

  printf("Final serial C is: %f\n", serTot);

  time_pdp(rng);


  free(A);
  free(B);
  free(C);
}
