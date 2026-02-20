#include "std_lib_facilities.h"
//IMPORTANT: a binary search presumes that the sequence is ordered

template<typename In, typename T>
In Binary_search(In first, In last, const T& val)
{
	if (first==last) return last;  // sequence is empty
	
	In p = first + (last-first)/2;
	
	if (*p==val) return p;
    if (*p<val && p+1!=last) return Binary_search(p,last,val);
    if (*p>val) return Binary_search(first,p,val);
    return last;   // *p<val && p+1==last
}
int main()
try
{
	vector<int> vi {0,4,7,1,7,9,10,17,18,20,41,23,12,16,18,26,31};
	
	sort(vi.begin(),vi.end());
	
	int vf{13};
	if(Binary_search(vi.begin(),vi.end(),vf)!=vi.end()) 
		cout << "Value found\n" << *Binary_search(vi.begin(),vi.end(),vf);
	else 
		cout << "Value not found\n";
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
