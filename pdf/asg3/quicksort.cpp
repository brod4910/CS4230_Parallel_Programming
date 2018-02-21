// Compilation: g++ --std=c++14 -O3 tbb_qs.cpp -ltbb -o tbb_qs
// http://parallelbook.com/downloads

#include <iostream>
#include <tbb/tbb.h>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>

using namespace std;
using namespace tbb;

// Size of parallel base case.
ptrdiff_t QUICKSORT_CUTOFF = 100;//CHANGEME!!
// This constant must be selected to 
// something higher; see the book's selection
// Experiment with a few constants.

typedef int T;

// Choose median of three keys.
T* median_of_three(T* x, T* y, T* z) {
    return *x<*y ? *y<*z ? y : *x<*z ? z : x 
         : *z<*y ? y : *z<*x ? z : x;
}

// Choose a partition key as median of medians.
T* choose_partition_key( T* first, T* last ) {
    size_t offset = (last-first)/8;
    return median_of_three(
        median_of_three(first, first+offset, first+offset*2),
        median_of_three(first+offset*3, first+offset*4, last-(3*offset+1)), 
        median_of_three(last-(2*offset+1), last-(offset+1), last-1 )
    );
}

// Choose a partition key and partition [first...last) with it.
// Returns pointer to where the partition key is in partitioned sequence.
// Returns NULL if all keys in [first...last) are equal.
T* divide( T* first, T* last ) {
    // Move partition key to front.
    std::swap( *first, *choose_partition_key(first,last) );
    // Partition 
    T key = *first;
    T* middle = std::partition( first+1, last, [=](const T& x) {return x<key;} ) - 1;
    if( middle!=first ) {
        // Move partition key to between the partitions
        std::swap( *first, *middle );
    } else {
        // Check if all keys are equal
        if( last==std::find_if( first+1, last, [=](const T& x) {return key<x;} ) )
            return NULL;
    }
    return middle;
}

void parallel_quicksort( T* first, T* last ) {
    tbb::task_group g;
    while( last-first>QUICKSORT_CUTOFF ) {
        // Divide
        T* middle = divide(first,last);
        if( !middle ) {
            g.wait();
            return;
        }

        // Now have two subproblems: 
        // [first..middle) and [middle+1..last)

        if( middle-first < last-(middle+1) )  {
            // Left problem (first..middle) is smaller, so spawn it.
            g.run([=]{parallel_quicksort( first, middle );});
            // Solve right subproblem in next iteration.
            first = middle+1;
        } else {
            // Right problem (middle..last) is smaller, so spawn it.
            g.run([=]{parallel_quicksort( middle+1, last );});
            // Solve left subproblem in next iteration.
            last = middle;
        }
    }
    // Base case
    std::sort(first,last); // sorts [first,last)
    g.wait();
 }

//--

#define MAX_ASIZE  1000000000
int ASize; // array size to be sorted

void Get_args(int argc, char **argv);
void Usage(char* prog_name);

int *A; // Global array sorted

//--

int main(int argc, char **argv) {
  Get_args(argc, argv); 
  // CHANGE THIS USAGE to 'new' in your code!
  // ALSO include delete[] A; at the end
  A = new int[ASize];
  srand(17);
// The public method 'init' used below is 
// documented at https://software.intel.com/en-us/node/506296
 int nthr = task_scheduler_init::default_num_threads();
 cout << "Will run upto " << nthr << " threads" << endl;

 // Iterate over all the threads allowed
 for( int p=1; p <= 24; ++p ) {
   
   for (int i=0; i<ASize; ++i)
   { 
      // A[i] = rand()%2000000;
      A[i] = i;
   }

   if (ASize < 17) // Print for small arrays
   {
     for (int i=0; i<ASize; ++i)
     { 
        cout << "A[" << i << "] = " << A[i] << endl;
     }
   }
   
   // Construct task scheduler with p threads
   // re-initialize task-scheduler to carry p threads
   task_scheduler_init init(p); 
   
   tick_count t0 = tick_count::now();   
   //--
   parallel_quicksort(&A[0], &A[ASize]); //sort [first,last)
   //--
   tick_count t1 = tick_count::now();
   double t = (t1-t0).seconds();

   if (ASize < 17)
   {
     for (int i=0; i<ASize; ++i)
       { cout << "A[" << i << "] = " << A[i] << endl;
       }
   }

   cout << "ASize = " << ASize << ", nThr = " 
        << p << ", T = " << t << endl;

 } // for (int p= 1; ...)
 
 return 0;
 }    
      
//---
void Get_args(int argc, char **argv) {
   if (argc != 2) Usage(argv[0]);
   ASize = strtol(argv[1], NULL, 10);  
   if (ASize <= 0 || ASize > MAX_ASIZE) Usage(argv[0]);
}  

void Usage(char *prog_name) {
   fprintf(stderr, "usage: %s ASize:int\n", prog_name);
   exit(0);
}  /* Usage */
