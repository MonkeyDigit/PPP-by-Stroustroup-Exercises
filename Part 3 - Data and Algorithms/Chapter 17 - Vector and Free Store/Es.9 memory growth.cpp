#include "std_lib_facilities.h"

int main()
{
	int a = 1;
	int b = 2;
	cout << "a: " << &a << '\n';
	cout << "b: " << &b << '\n';
	//the stack grows downward
	
	constexpr int n=5;
	int* store= new int[n];
	for(int i=0;i<n;++i)
		store[i]=i;
	
	cout << "store: \n";
	for(int i=0;i<n;++i)
		cout << &store[i] << '\n';
	//free store grows upward
	delete[] store;
	return 0;
}
