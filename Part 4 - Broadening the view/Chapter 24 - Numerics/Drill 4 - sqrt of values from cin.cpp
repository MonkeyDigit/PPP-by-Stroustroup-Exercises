#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	for(int val;cin>>val;)
	{
		cout << "sqrt(" << val <<"): ";
		if(val)
			cout << sqrt(val) << '\n';
		else
			cout << "None\n";
	}
	return 0;
}
