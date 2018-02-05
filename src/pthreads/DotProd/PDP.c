#include <stdio.h>
//#include <sys/sysinfo.h>
#include <pthread.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>

const long MAX_EXP = 32;
const int MAX_THREADS = 1024;
int Size;
int Exp, Thres;

typedef struct {
  int L;
  int H;
  int result;
  int numThreads;
} RNG;


// Global arrays over which DP is done
float *A;
float *B;
float *C;
float result;

// lock for the shared variable nextbase
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void Usage(char *prog_name) {
   fprintf(stderr, "usage: %s <Exp>:int <Thres>:int\n", prog_name);
   fprintf(stderr, "Ensure that Thres <= pow(2, Exp)\n");
   exit(0);
}  /* Usage */

void Get_args(int argc, char **argv) {
   if (argc != 3) Usage(argv[0]);
   Exp = strtol(argv[1], NULL, 10);  
   if (Exp <= 0 || Exp > MAX_EXP) Usage(argv[0]);
   Thres = strtol(argv[2], NULL, 10);
   if (Thres < 1 || Thres >= (int) pow(2, Exp)) Usage(argv[0]);
}  

int serdp(RNG rng) 
{
  int result = 0;

  for(int i=rng.L; i<=rng.H; ++i)
  {
    C[i] = A[i] * B[i];
    result += C[i];
  }

  return result;
}

void* pdp(void* myrng) 
{
  RNG *prng = (RNG*)myrng;
  RNG rng = *(RNG*)myrng;

  // variables to join threads after they have been created
  pthread_t tid[2];

  if ((rng.H - rng.L) + 1 < Thres) 
  {
    prng->result = serdp(rng);
  }
  else 
  {
    printf("-> rng.L and rng.H are %d %d\n", rng.L, rng.H);
    
    RNG rngL = rng;
    RNG rngH = rng;
    
    rngL.H = rng.L + (rng.H - rng.L)/2;
    rngH.L = rngL.H+1;

    // critical section. create a thread then increment the thread id
    // set the variable to join the thread after it is created.
    // printf("--> creating thread for range %d %d\n", rngL.L, rngL.H);
    pthread_create(&tid[0], NULL, &pdp, (void*)&rngL);
    
    // critical section. create a thread then increment the thread id
    // set the variable to join the thread after it is created.
    // printf("--> creating thread for range %d %d\n", rngH.L, rngH.H);    
    pthread_create(&tid[1], NULL, &pdp, (void*)&rngH);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    prng->numThreads = rngL.numThreads + rngH.numThreads + 2;
    prng->result = rngL.result + rngH.result;
  }
}

/*
 * Driver method for doing parallel dot product
 */
// void do_pdp(RNG rng)
// {
//   printf("--> creating thread for range %d %d\n", rng.L, rng.H);
//   // set variable to join the thread after it has finished work
//   int t = tid;

//   // create the thread to do the work.
//   pthread_create(&id[tid++], NULL, &pdp, (void*)&rng);

//   // join the thread after the calls have been made
//   pthread_join(id[t], NULL);
// }

// /*
//  * Reduces the final array in parallel
//  */
// void* reduce(void* rng)
// {
//   RNG myrng = *(RNG*)rng;

//   // printf("--> reducing between: %d %d\n", myrng.L, myrng.H);

//   for(int i = myrng.L; i <= myrng.H;i++)
//   {
//       pthread_mutex_lock(&mutex);
//       result += C[i];
//       pthread_mutex_unlock(&mutex);
//       // printf("%f\n", C[i]);
//   }
// }

// /*
//  * Driver method for doing parallel reduce
//  */
// void do_reduce(RNG rng, int reduction)
// {
//   RNG *splits = (RNG*)malloc(sizeof(RNG) * reduction);

//   // set up the initial work
//   RNG work;
//   work.L = rng.L;
//   work.H = rng.H / reduction;
//   splits[0] = work;

//   int mult = 2;

//   for(int i = 1; i < reduction; ++i)
//   {
//     printf("--> reducing between: %d %d\n", work.L, work.H);
    
//     work.L = work.H + 1;
//     work.H = ((Size) / reduction) * mult;

//     if(work.H >= (Size-1))
//     {
//       work.H = Size - 1;
//     }

//     splits[i] = work;
//   }
  
//   for(int i = 0; i < reduction; ++i)
//   {
//     pthread_create(&id[i++], NULL, &reduce, (void*)&splits[i]);
//   }

//   for(int i = 0; i < tid; ++i)
//   {
//     pthread_join(id[i], NULL);
//   }

//   free(splits);
// }


// int get_nprocs_conf(void);
// int get_nprocs(void);

int main(int argc, char **argv) {
  // Turn this on on Linux systems
  // On Mac, it does not work
  // printf("This system has\
  //         %d processors configured and\
  //         %d processors available.\n",
  //         get_nprocs_conf(), get_nprocs());
  
  Get_args(argc, argv);  
  Size = (int) pow(2, Exp);
  printf("Will do DP of %d sized arrays\n", Size);

  A = (float *) malloc(Size*sizeof(float));
  B = (float *) malloc(Size*sizeof(float));
  printf("Filling arrays now\n");
  srand(17); //Seed with 17
  for (int i=0; i<Size; ++i) {
    A[i] = rand()%16;
    B[i] = rand()%16;
  }
  for(int i=0; i<Size; ++i) {
    printf("A[%d] and B[%d] are %f and %f\n",i,i,(double)A[i],(double)B[i]);
  }

  RNG rng;
  rng.L = 0;
  rng.H = Size-1;
  rng.numThreads = 0;
  rng.result = 0;
  //printf("Serial dot product is %f\n", serdp(rng));
  
  printf("Now invoking parallel dot product\n");
  C = (float *) malloc(Size*sizeof(float));
  for(int i=0; i<Size; ++i) {
    C[i]=0;
  }
  //printf("Parallel DP = %f\n", pdp(rng));
  result = pdp(rng);

  printf("Final C is\n");

  // do_reduce(rng, 2);
  // printf("%s%f\n", "Parallel C is: ", result);

  // result = 0;
  // for(int i=0; i<Size; ++i) 
  // {
  //   // printf("%f\n", (double) C[i]);
  //   result += C[i];
  // }


  printf("%s%f\n", "Final Result: ", result);

  free(A);
  free(B);
  free(C);
}
