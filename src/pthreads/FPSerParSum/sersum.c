#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

const long MAX_EXP = 28;
void Get_args(int argc, char **argv);
void Usage(char* prog_name);

// args
int exp_range;
float start_value;

int main(int argc, char **argv){
  double start, finish, elapsed;
  Get_args(argc, argv);
  printf("exp_range = %d\n", exp_range);
  int ASize = (int) pow(2, exp_range);  
  printf("start_value = %50.40f\n", start_value);
  float *A;
  A = (float *) malloc(ASize * sizeof(float));
  for (long i=0; i<ASize; ++i) {
    A[i]=start_value;
  }
  GET_TIME(start);  
  for (int i=0; i<ASize-1; ++i) {
    A[i+1] += A[i];
  }
  GET_TIME(finish);
  elapsed = finish - start;
  printf("The elapsed time is %e seconds\n", elapsed);
  printf("The accumulated answer is %50.40f\n", A[ASize-1]);  
}

void Get_args(int argc, char **argv) {
   if (argc != 3) Usage(argv[0]);
   exp_range = strtol(argv[1], NULL, 10);  
   if (exp_range <= 0 || exp_range > MAX_EXP) Usage(argv[0]);
   start_value = strtod(argv[2], NULL);
   if (start_value <= 0.0) Usage(argv[0]);
}  

void Usage(char *prog_name) {
   fprintf(stderr, "usage: %s <iter_range>:long <start_value>:float\n", prog_name);
   exit(0);
}  /* Usage */
