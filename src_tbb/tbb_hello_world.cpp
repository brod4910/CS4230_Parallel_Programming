#include <iostream>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>

using namespace std;
using namespace tbb;

class MySeries {
public:
	double my_sum;
	MySeries(MySeries& x,split):my_sum(0){}
	MySeries():my_sum(0){}
	void operator()(const blocked_range<size_t>& r){
		double sum=my_sum;
		size_t end=r.end();
		for(long i=r.begin();i!=end;++i)
		{
			double denom = i*2.0 + 1.0;
			if(i%2==1){denom=-denom;}
			sum+=1.0/denom;
		}
		my_sum=sum;
	}
	void join(MySeries& y){	
		my_sum += y.my_sum;	
	}
};

int main() {
	MySeries x;
	parallel_reduce(
		blocked_range<size_t>(0,1000000),
		x
		);
	cout << 4 * x.my_sum << endl;	
	return 0;
}
