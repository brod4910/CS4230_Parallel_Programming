#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>
#include <math.h>

static int Thres;
int serdp(int *A, int *B, int L, int H);
int pdp(int *A, int *B, int *C, int L, int H);

int main(int argc, char **argv) {
  int Exp; // of DP array; Size = 2 ** Exp
  printf("Please provide Exp for array sizes and threshold sep by a comma\n");
  scanf("%d,%d", &Exp, &Thres);
  int Size = (int) pow(2, Exp);
  printf("Will do DP of %d sized arrays\n", Size);
  int *A, *B, *C;
  A = (int *) malloc(Size*sizeof(int));
  B = (int *) malloc(Size*sizeof(int));
  printf("Filling arrays now\n");
  srand(17);//Seed with 17
  for (int i=0; i<Size; ++i) {
    A[i] = rand()%128;
    B[i] = rand()%128;
  }
  //  for(int i=0; i<Size; ++i) {
  //    printf("A[%d] and B[%d] are %d and %d\n",i,i,A[i],B[i]);
  //  }
  printf("Serial dot product is %d\n", serdp(A,B,0,Size));
  printf("Now invoking parallel dot product\n");
  C = (int *) malloc(Size*sizeof(int));
  for(int i=0; i<Size; ++i) {
    C[i]=0;
  }
  printf("Parallel DP = %d\n",pdp(A,B,C,0,Size));
}

int serdp(int *A, int *B, int L, int H) {
  int DP = 0;
  for(int i=L; i<H; ++i) {
    DP += A[i]*B[i];
  }
  return DP;
}

int pdp(int *A, int *B, int *C, int L, int H) {
    for(int i=L; i<H; ++i) {
      printf("i,A[],B[],C[],Thres,L,H = %d,%d,%d,%d,%d,%d,%d\n",
  	   i,A[i],B[i],C[i],Thres,L,H);
    }  
  if ((H-L)<Thres) {
    return serdp(A,B,L,H);
  }
  else {
    return -1;
  }
}

