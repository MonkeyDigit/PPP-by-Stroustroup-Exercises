#include "std_lib_facilities.h"

class Less_than{
	double val;
public:
	Less_than(double vv): val{vv} {}
	bool operator()(double x) const {return x<val;}
};

int main()
try
{
	vector<double> vd;
	
	ifstream ifs{"floats.txt"};
	
	for(double d;ifs>>d;)
		vd.push_back(d);
		
	cout << "vd: \n";
	for(const double& d : vd)
		cout << d << '\n';
		
	vector<int> vi;
	for(const double& d : vd)
		vi.push_back(d);
	
	cout << "\n(vd[i],vi[i]) pairs: \n";
	for(int i=0;i<vd.size();++i)
		cout << '(' << vd[i] << ", " << vi[i] << ')' << '\n';
	cout << "\nSum of vd elements: " << accumulate(vd.begin(), vd.end(), 0.0) << '\n';
	
	cout << "\nDifference between the sum of vd and vi: " 
		<< double(accumulate(vd.begin(), vd.end(), 0.0) - 
			accumulate(vi.begin(), vi.end(), 0))<< '\n';
			
	reverse(vd.begin(),vd.end());
	
	cout << "\nReversed vd: \n";
	for(const double& d : vd)
		cout << d << '\n';
	
	cout << "\nMean value of vd: " << accumulate(vd.begin(), vd.end(), 0.0) / vd.size() << '\n';
	
	vector<double> vd2(vd.size());
	
	double vd_mean=accumulate(vd.begin(), vd.end(), 0.0) / vd.size();
	copy_if(vd.begin(),vd.end(),vd2.begin(), Less_than(vd_mean));
	
	cout << "\nCopied vd values less than mean to vd2: \n";
	for(const double& d : vd2)
		cout << d << '\n';
	
	sort(vd.begin(),vd.end());
	cout << "\nSorted vd: \n";
	for(const double& d : vd)
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
