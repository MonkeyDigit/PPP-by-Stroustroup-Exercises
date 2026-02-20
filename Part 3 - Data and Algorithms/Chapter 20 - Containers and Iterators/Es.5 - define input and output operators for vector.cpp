#include "std_lib_facilities.h"

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	os << '{';
	for(int i=0;i<v.size();++i)
	{
		os << v[i];
		if(i<v.size()-1) os << ", ";
	}
	
	os << '}';
	return os;
}

template<class T>
istream& operator>>(istream& is, vector<T>& vec)
{
	char ch1;
	is >> ch1;
	
	if(ch1!='{')
	{
		is.clear(ios_base::failbit); // set the fail bit
			return is;
	}
	
	T val;
	while(true)
	{
		char ch;
		is >> ch;
		
		if(is && ch=='}') return is;
		is.unget();
		is >> val;
		
		if(is) 
			vec.push_back(val);
		else
		{
			is.clear(ios_base::failbit); // set the fail bit
			return is;
		}
	}
	
	return is;
}

int main()
try
{
	vector<double> v1;
	cin >> v1;
	
	cout<<v1;
	return 0;
}
catch(exception & e)
{
	cerr<< "Exception: " << e.what() <<'\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
