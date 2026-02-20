#include "std_lib_facilities.h"

template<typename T>
void f(vector<T>& vec1, const vector<T>& vec2)
{
	if(vec1.size() != vec2.size()) error("Different vector sizes");
	
	for(int i=0;i<vec1.size();++i)
	{
		vec1[i]+=vec2[i];
	}
}

int main()
try
{
	vector<int> v1 {1,2};
	vector<int> v2 {4,4};
	
	for(const int& v : v1)
		cout << v << '\n';
		
	f(v1,v2);
	
	cout << "after f():\n";
	for(const int& v : v1)
		cout << v << '\n';
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
