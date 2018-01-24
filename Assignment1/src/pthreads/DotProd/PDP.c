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
} RNG;


// Global arrays over which DP is done
float *A;
float *B;
float *C;
float result;

// lock for the shared variable nextbase
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// ID structs for the threads
pthread_t id[MAX_THREADS];

int tid = 0;

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

void serdp(RNG rng) 
{
  pthread_mutex_lock(&mutex);
  for(int i=rng.L; i<=rng.H; ++i)
  {
    C[i] = A[i] * B[i];
  }
  pthread_mutex_unlock(&mutex);
}

// void* pdp(void* myrng) 
// {
//   RNG rng = *(RNG*)myrng;

//   if ((rng.H - rng.L) <= Thres) 
//   {
//     serdp(rng);
//   }
//   else 
//   {
//     printf("-> rng.L and rng.H are %d %d\n", rng.L, rng.H);
    
//     RNG rngL = rng;
//     RNG rngH = rng;
    
//     rngL.H = rng.L + (rng.H - rng.L)/2;
//     rngH.L = rngL.H+1;

//     pthread_mutex_lock(&mutex);
//     printf("--> creating thread for range %d %d\n", rngL.L, rngL.H);
//     pthread_create(&id[tid++], NULL, &pdp, (void*)&rngL);
//     pthread_mutex_unlock(&mutex);
    
//     pthread_mutex_lock(&mutex);
//     printf("--> creating thread for range %d %d\n", rngH.L, rngH.H);    
//     pthread_create(&id[tid++], NULL, &pdp, (void*)&rngH);
//     pthread_mutex_unlock(&mutex);
//   }
// }

void* pdp(void* oldrng)
{
  RNG rng = *(RNG*)oldrng;

  if(rng.L < rng.H)
  {
    printf("%d:%d\n", rng.L, rng.H);

    for(int i = rng.L; i <= rng.H;++i)
    {
      C[i] = A[i] * B[i];
    }

    RNG* newrng = (RNG*)malloc(sizeof(RNG));
    newrng->L = rng.H + 1;
    newrng->H = newrng->L + Thres;

    if(newrng->H >= (Size-1))
    {
      newrng->H = Size-1;
    }
      printf("--> creating thread for range %d %d\n", newrng->L, newrng->H);
      pthread_create(&id[tid++], NULL, &pdp, (void*)newrng);
    }
}

void do_pdp(RNG rng)
{
  printf("--> creating thread for range %d %d\n", rng.L, rng.H);

  pthread_create(&id[tid++], NULL, &pdp, (void*)&rng);

  nanosleep((const struct timespec[]){{1, 0L}}, NULL);

  for(int i = 0; i < tid; ++i)
  {
    pthread_join(id[i], NULL);
    printf("%d\n", i);
  }
}

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
  rng.H = Thres;
  //printf("Serial dot product is %f\n", serdp(rng));
  
  printf("Now invoking parallel dot product\n");
  C = (float *) malloc(Size*sizeof(float));
  for(int i=0; i<Size; ++i) {
    C[i]=0;
  }
  //printf("Parallel DP = %f\n", pdp(rng));
  do_pdp(rng);

  printf("Final C is\n");
  for(int i=0; i<Size; ++i) {
    // printf("%f\n", (double) C[i]);
    result += C[i];
  }

  printf("%s%f\n", "Final Result: ", result);

  free(A);
  free(B);
  free(C);
}
