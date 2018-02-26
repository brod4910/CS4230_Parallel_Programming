#include <iostream>
#include <stdlib.h>
#include <vector>
#include <pthread.h> 
#include <math.h>
#include <time.h>
#include <tbb/tbb.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>

const long MAX_EXP = 32;
const int MAX_THREADS = 1024;
const int DEFAULT_THREADS = 16;
size_t Size;
int Exp, Thres, Thread_Num;

struct RNG {
  size_t L;
  size_t H;
  int result;
  int numThreads;
};

struct PDP
{
  const double* A;
  const double* B;
  double* output;

   void operator()(const tbb::blocked_range<int>& range) const
   {
      for(int i = range.begin(); i != range.end(); ++i)
      {
        output[i] = A[i] * B[i];
      }
   }
}; 

struct SDP 
{

};

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

int serdp(RNG rng) 
{
  int result = 0;

  for(int i=rng.L; i<=rng.H; ++i)
  {
    C[i] = A[i] * B[i];
    result += C[i];
  }

  presult += result;
  return result;
}

void pdp(RNG myrng) 
{
  RNG *prng = &myrng;

  if((myrng.H - myrng.L) + 1 < Thres)
  {
    prng->result = serdp(myrng);
  }
  else
  {
    RNG rngL = myrng;
    RNG rngH = myrng;
    
    rngL.H = myrng.L + (myrng.H - myrng.L)/2;
    rngH.L = rngL.H+1;

    tbb::parallel_invoke( [=]{pdp(rngL);}, 
                          [=]{pdp(rngH);}
                          );
  }
}

void time_pdp(RNG myrng)
{
  double for_overhead, pdp_time, totDuration, pow_overhead;
	clock_t startTime;
  int nthr = tbb::task_scheduler_init::default_num_threads();
  int pow_count = 3;

  PDP pdp_res;
  pdp_res.A = A;
  pdp_res.B = B;
  pdp_res.output = C;


  for(int i = 1; i <= Thread_Num;i++)
  {
    tbb::tick_count t0, t1;
    presult = 0;

    t0 = tbb::tick_count::now();
  	for(int j = 0; j < 100; j++)
  	{

  	}
    t1 = tbb::tick_count::now();
    for_overhead = (t1-t0).seconds();

    t0 = tbb::tick_count::now();
    for(int j = 8; j <= pow(2, Exp); j = pow(2, pow_count))
    {
      pow_count++;
    }
    t1 = tbb::tick_count::now();
    pow_overhead = (t1-t0).seconds();

    pow_count = 3;

    tbb::task_scheduler_init init(i);
    // tbb::task_arena limited_arena(i);
    // tbb::task_group tg;
  
    for(size_t k = 8; k <= pow(2,Exp); k = pow(2, pow_count))
    {  
      myrng.H = k - 1;  
  		for(int j = 0; j < 100;j++)
  		{
        t0 = tbb::tick_count::now();
        tbb::parallel_for(tbb::blocked_range<int>(myrng.L, myrng.H + 1), pdp_res);
        // limited_arena.execute([&](){
        //           tg.run([&](){ 
        //               tbb::parallel_for(tbb::blocked_range<int>(myrng.L, myrng.H + 1), pdp_res);});
        //           });
        t1 = tbb::tick_count::now();
        pdp_time += (t1-t0).seconds();
  		}

  		pdp_time /= 100;

  		totDuration = pdp_time - (for_overhead + pow_overhead);

      for(int i = myrng.L; i <= myrng.H; i++)
      {
        presult += C[i];
      }

      std::cout << "PSize = " << pow(2, pow_count) << ", nThr = " 
      << 8 << ", DP = " << presult <<", T = " << totDuration << std::endl;

      for_overhead = pdp_time = presult =0;
      pow_count++;
      PDP pdp_res;
    }
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

  PDP pdp_res;
  pdp_res.A = A;
  pdp_res.B = B;
  pdp_res.output = C;

  //printf("Parallel DP = %f\n", pdp(rng));

  tbb::parallel_for(tbb::blocked_range<int>(rng.L, rng.H + 1), pdp_res);

  for(size_t i = rng.L; i <= rng.H;i++)
  {
     presult += C[i];
  }

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
