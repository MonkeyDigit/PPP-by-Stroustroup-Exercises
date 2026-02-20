#include <iostream>
#include <iomanip>
using namespace std;

#define PI 3.141592653589793238462643383279502884197
void f(int i, double fpd)
{
	cout << "f(" << i << ", " << fpd << ")\n";
	char c = i; // yes: chars really are very small integers
	short s = i; // beware: an int may not fit in a short int
	i = i+1; // what if i was the largest int?
	long lg = i*i; // beware: a long may not be any larger than an int
	
	float fps = fpd; // beware: a large double may not fit in a float
	i = fpd; // truncates: e.g., 5.7 –> 5
	fps = i; // you can lose precision (for very large int values)
	
	cout << "c:\t" << c << '\n'
		 << "s:\t" << s << '\n'
		 << "i:\t" << i << '\n'
		 << "lg:\t" << lg << '\n'
		 << "fpd:\t" << fpd << '\n'
		 << "fps:\t" << fps << '\n';
}

void g()
{
	char ch = 0;
	for (int i = 0; i<500; ++i) 
	cout << int(ch++) << '\n';
}

int main()
{
	/*
	
	g();
	
	*/
	
	f(100,12.567);
	
	cout << '\n';
	f(232,PI);
	
	return 0;
}
