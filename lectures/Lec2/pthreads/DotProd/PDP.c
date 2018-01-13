#include <stdio.h>
//#include <sys/sysinfo.h>
#include <pthread.h> 
#include <stdlib.h>
#include <math.h>

void Get_args(int argc, char **argv);
void Usage(char* prog_name);


const long MAX_EXP = 32;
int Exp, Thres;

typedef struct {
  int L;
  int H;
} RNG;

void serdp(RNG rng);
void pdp(RNG rng);

// Global arrays over which DP is done
float *A;
float *B;
float *C;

int main(int argc, char **argv) {
  // Turn this on on Linux systems
  // On Mac, it does not work
  // printf("This system has %d processors configured and "
  //	 "%d processors available.\n",
  //	 get_nprocs_conf(), get_nprocs());
  
  Get_args(argc, argv);  
  int Size = (int) pow(2, Exp);
  printf("Will do DP of %d sized arrays\n", Size);

  A = (float *) malloc(Size*sizeof(float));
  B = (float *) malloc(Size*sizeof(float));
  
  printf("Filling arrays now\n");
  srand(17);//Seed with 17
  for (int i=0; i<Size; ++i) {
    A[i] = rand()%16;
    B[i] = rand()%16;
  }
  for(int i=0; i<Size; ++i) {
    printf("A[%d] and B[%d] are %f and %f\n",i,i,A[i],B[i]);
  }
  RNG rng;
  rng.L = 0;
  rng.H = Size-1;
  //printf("Serial dot product is %f\n", serdp(rng));
  
  printf("Now invoking parallel dot product\n");
  C = (float *) malloc(Size*sizeof(float));
  for(int i=0; i<Size; ++i) {
    C[i]=0;
  }
  //printf("Parallel DP = %f\n", pdp(rng));
  pdp(rng);

  printf("Final C is\n");
  for(int i=0; i<Size; ++i) {
    printf("%f\n", C[i]);
  }  

  free(A);
  free(B);
  free(C);
}

void serdp(RNG rng) {
  for(int i=rng.L; i<=rng.H; ++i) {
    C[i] = A[i] * B[i];
  }
}

void pdp(RNG myrng) {
  RNG rng = myrng;
  if ((rng.H - rng.L) <= Thres) {
    serdp(rng);
  }
  else {
    printf("-> rng.L and rng.H are %d %d\n", rng.L, rng.H);
    
    RNG rngL = rng;
    RNG rngH = rng;
    
    rngL.H = rng.L + (rng.H - rng.L)/2;
    rngH.L = rngL.H+1;

    printf("--> creating thread for range %d %d\n", rngL.L, rngL.H);
    pdp(rngL);
    
    printf("--> creating thread for range %d %d\n", rngH.L, rngH.H);    
    pdp(rngH);
  }
}

void Get_args(int argc, char **argv) {
   if (argc != 3) Usage(argv[0]);
   Exp = strtol(argv[1], NULL, 10);  
   if (Exp <= 0 || Exp > MAX_EXP) Usage(argv[0]);
   Thres = strtol(argv[2], NULL, 10);
   if (Thres < 1 || Thres >= (int) pow(2, Exp)) Usage(argv[0]);
}  

void Usage(char *prog_name) {
   fprintf(stderr, "usage: %s <Exp>:int <Thres>:int\n", prog_name);
   fprintf(stderr, "Ensure that Thres <= pow(2, Exp)\n");
   exit(0);
}  /* Usage */

