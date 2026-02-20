#include "std_lib_facilities.h"
/*A constant is a value that must be known at compile time:
simple "const" - I can assign to that const another variable:
WORKS:
	const int a = 2;
WORKS:
	int a= 2;
	const int b = a;

"constexpr" - The value must be an expression without variables:
WORKS:
	constexpr int a = 2;
DOESN'T WORK:
	int a = 2;
	constexpr int b = a;	<----WILL NOT COMPILE
*/
void f(const int);

int main()
{
	/* WORKS
	int x{5};
	f(x);
	*/
	
	/* WORKS
	int y;
	cin>>y;
	f(y);
	*/
	
	/* WORKS
	const int x = 5;
	f(x);
	*/
}

void f(const int x)	
{
	cout<<x+1<<'\n';
}
