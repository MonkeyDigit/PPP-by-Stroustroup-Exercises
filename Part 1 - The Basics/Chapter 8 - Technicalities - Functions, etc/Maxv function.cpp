#include "std_lib_facilities.h"

double maxv(vector<double>&);
void print(vector<double>&);


int main()
{
	vector<double> v {3,4.5,2,5,6,8.6,9.1,8.3};
	double max{};
	
	print(v);
	max=maxv(v);
	cout<<"Max: "<<max<<'\n';
	return 0;
}


double maxv(vector<double>& v)
{
	double max{};
	
	for(double x : v) if(x>max) max=x;
	
	return max;
}

void print(vector<double>& v)
{
	for(double x : v) cout<<x<<'\n';
}

