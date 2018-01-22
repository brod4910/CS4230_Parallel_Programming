#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

const long MAX_EXP = 28;
// args
int exp_range;
float start_value;

void Usage(char *prog_name) {
   fprintf(stderr, "usage: %s <exp_range>:long <start_value>:float\n", prog_name);

   exit(0);
}  /* Usage */

void Get_args(int argc, char **argv) {
   if (argc != 3) Usage(argv[0]);

   exp_range = strtol(argv[1], NULL, 10);
   if (exp_range <= 0 || exp_range > MAX_EXP) Usage(argv[0]);

   start_value = strtod(argv[2], NULL);
   if ((double) start_value <= (double) 0.0) Usage(argv[0]);
}

int main(int argc, char **argv){
  Get_args(argc, argv);
  printf("exp_range = %d\n", exp_range);

  int ASize = (int) pow(2, exp_range);
  printf("start_value = %50.40f\n", start_value);

  float *A = (float *) malloc(ASize * sizeof(float));

  for (long i=0; i<ASize; ++i) {
    A[i]=start_value;
  }

  double start;
  GET_TIME(start);

  for (int str=1; str<=ASize/2; str*=2) {
    for (int i=0; i<ASize; i+=2*str) {
      if (exp_range<6) printf("A[%d] += A[%d]\n", i, i+str);
      A[i]+=A[i+str];
    }
    if (exp_range<6) printf("\n");
  }

  double finish;
  GET_TIME(finish);

  double elapsed;
  elapsed = finish - start;

  printf("The elapsed time is %e seconds\n", elapsed);
  printf("The accumulated answer is %50.40f\n", (double) A[0]);
}
