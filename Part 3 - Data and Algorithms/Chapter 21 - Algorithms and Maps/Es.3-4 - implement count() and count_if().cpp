#include "std_lib_facilities.h"
#include <map>
template<typename Iter>
int Count(Iter first, Iter last)
{
	int count{};
	
	while(first!=last)
	{
		++count;
		++first;
	}
	return count;
}

template<typename Iter, typename Pred>
int Count_if(Iter first, Iter last, Pred p)
{
	int count{};
	
	while(first!=last)
	{
		if(p(*first)) ++count;
		++first;
	}
	return count;
}

class Larger_than{
	int val;
public:
	Larger_than(const int vv): val{vv} {}
	
	bool operator()(const int n){return n>val;}
};

int main()
try
{
	int ai[] {0,1,2,3,4,5,6,7,8};
	cout << "ai Count(): " << Count(ai,ai+sizeof(ai)/sizeof(int)) << '\n';
	
	vector<int> vi {0,1,2,3,4,5};
	cout << "vi Count(): " << Count(vi.begin(),vi.end()) << '\n';
	
	list<int> li {0,1,2,3,4,5,6,7};
	cout << "li Count(): " << Count(li.begin(),li.end()) << '\n';
	
	map<string,int> msi {
		{"bob",1},
		{"abc",3},
		{"rock",14},
		{"water",7}
	};
	cout << "msi Count(): " << Count(msi.begin(),msi.end()) << '\n';
	
	cout << "ai Count_if(Larger_than(5)): " 
		<< Count_if(ai,ai+sizeof(ai)/sizeof(int),Larger_than(5)) << '\n';
		
	cout << "vi Count_if(Less_than(1)): " 
		<< Count_if(ai,ai+sizeof(ai)/sizeof(int),[](int n) {return n<1;}) << '\n';
	
	return 0;
}
catch(exception& e)
{
	cerr << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
