#include "std_lib_facilities.h"

vector<double> copy_list(const list<int>& list)
{
	vector<double> vec;
	
	for(const int& n : list)
		vec.push_back(n);
	return vec;
}

int main()
try
{
	list<int> l1 {4,7,6,2,1,8,5};
	
	vector<double> v1=copy_list(l1);
	
	cout << "v1: \n";
	for(const double& d : v1)
		cout << d << '\n';
		
	sort(v1);
	cout << "v1 after sorting: \n";
	for(const double& d : v1)
		cout << d << '\n';
	
	return 0;
}
catch(exception& e)
{
	cerr << "Exception: " << e.what() << '\n';
	keep_window_open();
	return 1;	
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
