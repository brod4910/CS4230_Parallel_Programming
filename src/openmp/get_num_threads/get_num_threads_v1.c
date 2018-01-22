// From https://msdn.microsoft.com/en-us/library/xdeb73hc.aspx

#include <stdio.h>
#include <omp.h>

int main()
{
  omp_set_num_threads(4);
  
  printf("%d:%d\n", omp_get_thread_num(), omp_get_num_threads( ));//Not in par section yet
  
  #pragma omp parallel
  {
   #pragma omp master 
   {
     printf("MSTR: %d:%d\n", omp_get_thread_num(), omp_get_num_threads( ));//done by master alone
   }
  }  
  // After reconvergence
  
  printf("%d:%d\n", omp_get_thread_num(), omp_get_num_threads( ));
  
  #pragma omp parallel num_threads(3)//Combo; par section + set thr
  {
   #pragma omp master//Master does str block which is shared by par sec too
   {
    printf("MSTR: %d:%d\n", omp_get_thread_num(), omp_get_num_threads( ));//Master alone
   }
  }
  
  printf("%d:%d\n", omp_get_thread_num(), omp_get_num_threads( ));//Back to single thread
}
/*
get_num_threads_v1.exe
0:1
MSTR: 0:4
0:1
MSTR: 0:3
0:1
*/
