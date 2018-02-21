#include <tbb/tbb.h>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include <stdlib.h>
#include <iostream>


typedef int T;

// merge sequences [xs,xe) and [ys,ye) to output [zs,(xe-xs)+(ye-ys)
void parallel_merge( const T* xs, const T* xe,  const T* ys, const T* ye, T* zs ) {
    const size_t MERGE_CUT_OFF = 2000;
    if( xe-xs + ye-ys <= MERGE_CUT_OFF ) {
        std::merge(xs,xe,ys,ye,zs);
    } else {
        const T *xm, *ym;
        if( xe-xs < ye-ys  ) {
            ym = ys+(ye-ys)/2;
            xm = std::upper_bound(xs,xe,*ym);
        } else {
            xm = xs+(xe-xs)/2;
            ym = std::lower_bound(ys,ye,*xm);
        }
        T* zm = zs + (xm-xs) + (ym-ys);
        tbb::parallel_invoke( [=]{parallel_merge( xs, xm, ys, ym, zs );},
                              [=]{parallel_merge( xm, xe, ym, ye, zm );} );
    }
}

// sorts [xs,xe).  zs[0:xe-xs) is temporary buffer supplied by caller.
// result is in [xs,xe) if inplace==true, otherwise in zs[0:xe-xs)
void parallel_merge_sort( T* xs, T* xe, T* zs, bool inplace ) {
    const size_t SORT_CUT_OFF = 500;
    if( xe-xs<=SORT_CUT_OFF ) {
        std::stable_sort( xs, xe );
        if( !inplace ) 
            std::move( xs, xe, zs );
    } else {
       T* xm = xs + (xe-xs)/2;
       T* zm = zs + (xm-xs);
       T* ze = zs + (xe-xs);
       tbb::parallel_invoke( [=]{parallel_merge_sort( xs, xm, zs, !inplace );},
                             [=]{parallel_merge_sort( xm, xe, zm, !inplace );} );
       if( inplace )
           parallel_merge( zs, zm, zm, ze, xs );
       else
           parallel_merge( xs, xm, xm, xe, zs );
   }
}


void call_parallel_merge_sort( T* xs, T* xe ) {
    T* zs = new T[xe-xs];

    int nthr = tbb::task_scheduler_init::default_num_threads();
    // std::cout << "Will run upto " << nthr << " threads" << std::endl;

    for(int i = 1; i <= 24;i++)
    {
      tbb::tick_count t0, t1;
      double for_overhead = 0, tot = 0.0;

      t0 = tbb::tick_count::now();
      for(int j = 0; j < 100;j++)
      {

      }
      t1 = tbb::tick_count::now();
      for_overhead = (t1-t0).seconds();

      tbb::task_scheduler_init init(i);

      for(int j = 0; j < 50;j++)
      {
        t0 = tbb::tick_count::now();
        parallel_merge_sort( xs, xe, zs, true );
        t1 = tbb::tick_count::now();
        tot += (t1-t0).seconds();

        for (int i=0; i<2000000; ++i)
        { 
          xs[i] = i;
          xe[i] = i;
        }
      }

      tot /= 100;
      tot -= for_overhead;
      std::cout << "Total duration for " << i << " threads was: " << tot << std::endl;
    }



    // delete [] zs;
}

int main()
{
    T *xs = new T[2000000];
    T *xe = new T[2000000];

    call_parallel_merge_sort(xs, xe);

    // delete [] xs;
    // delete [] xe;

    return 0;
}