#include "std_lib_facilities.h"
int fac_r(int n) { return n > 1 ? n * fac_r(n-1) : 1; } // recursive factorial n!
int fac_i(int n) // iterative factorial(n); n!
{
	int r = 1;
	while (n>1) 
	{
		r*=n;
		--n;
	}
	return r;
}

//i prefer the recursive function as it is shorter
int main()
{
	for(int i=0;i<=20;++i)
	{
		cout << "fac_r(" << i <<"): " << fac_r(i) << '\n'
			<< "fac_i(" << i <<"): " << fac_i(i) << '\n';
	}
	return 0;
}
