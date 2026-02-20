#include "std_lib_facilities.h"
//count already returns 0 if there are no elements
template<typename In, typename T>
bool Find(In first, In last, const T& val)
{
	while(first!=last)
	{
		if(*first==val) return true;
		++first;
	}
	
	return false;
}

int main()
try
{
	vector<int> vi {4,7,1,9,12,8};
	
	if(Find(vi.begin(),vi.end(),5)) cout << "5 found in vi\n";
	else cout << "5 not found in vi\n";
	
	if(Find(vi.begin(),vi.end(),8)) cout << "8 found in vi\n";
	else cout << "8 not found in vi\n";
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
