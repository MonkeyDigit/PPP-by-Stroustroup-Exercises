#include "std_lib_facilities.h"

int ga[10] {1,2,4,8,16,32,64,128,256,512};

//We don't need to pass the array by reference because the argument declaration of int a[] is considered equivalent to int* a
//Consequently, this saves us from an expensive copy operation, in case the array has a lot of elements
void f(int a[], int n)
{
	int la[10];
	for(int i=0;i<10;++i)
		la[i] = ga[i];
		
	for(int i=0;i<10;++i)
		cout << la[i] << '\n';
		
	int* p = new int[n];
	
	for(int i=0;i<n;++i)
		p[i] = a[i];
		
	for(int i=0; i<n;++i)
		cout << p[i] << '\n';
	
	delete[] p;
}

int main()
try
{
	f(ga,10);
	int aa[10];
	for(int i=0;i<10;++i)
	{
		int fac=1;
		for(int j=i+1;j>1;--j)
		{
			fac*=j;
		}
		aa[i]=fac;
	}
	
	f(aa,10);
	return 0;
}

catch(exception & e)
{
	cerr<<"error: "<<e.what()<<'\n';
	keep_window_open();
	return 1;
}

catch(...)
{
	cerr<<"Unknown exception\n";
	keep_window_open();
	return 2;
}
