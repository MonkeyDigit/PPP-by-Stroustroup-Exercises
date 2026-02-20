#include "std_lib_facilities.h"

template<typename T, typename U>
T product_sum(const vector<T>& vt, const vector<U>& vu)
{
	if(vt.size() != vu.size()) error("Different vector sizes");
	
	T sum = 0;
	for(int i=0;i<vt.size();++i)
	{
		sum+=vt[i]*vu[i];
	}
	
	return sum;
}

int main()
try
{
	vector<int> v1 {1,2};
	vector<double> v2 {4,4};
	
	cout << "v1\n";
	for(const int& v : v1)
		cout << v << '\n';
	
	cout << "v2:\n";
	for(const int& v : v2)
		cout << v << '\n';
		
	cout << "product_sum: " << product_sum(v1,v2) << '\n';
	return 0;
}
catch(exception& e)
{
	cerr<<"error: "<<e.what()<<'\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown error\n";
	keep_window_open();
	return 2;
}
