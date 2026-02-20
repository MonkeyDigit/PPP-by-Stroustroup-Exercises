#include "std_lib_facilities.h"

template<class Iter>
Iter lex_last(Iter first, Iter last)
{
	if(first==last) error("Empty vector");
	
	Iter ll=first;
	
	for(Iter p=first;p!=last;++p)
	{
		if(*ll<*p)
			ll=p;
	}
	return ll;
}

int main()
try
{
	vector<string> v1 {"bim","bum","bam","bom","car"};
	cout << *lex_last(v1.begin(),v1.end());
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
