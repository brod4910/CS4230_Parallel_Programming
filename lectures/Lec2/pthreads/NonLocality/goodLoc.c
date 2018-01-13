#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
int A[16384][16384]; //show nonlocal
int main(){
  double start, finish, elapsed;
  GET_TIME(start);  
  for (int i=0; i<16384; ++i)
    for (int j=0; j<16384; ++j)
      A[i][j]++;
  GET_TIME(finish);
  elapsed = finish - start;
  printf("The elapsed time is %e seconds\n", elapsed);  
}

