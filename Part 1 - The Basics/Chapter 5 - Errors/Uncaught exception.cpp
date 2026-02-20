#include <iostream>
#include <stdexcept>
using namespace std;

void error(string s)
{
	throw runtime_error(s);
}
int main()
{
	double d;
	
	cin>>d;
	
	if(!cin)
	{
		error("Oops...");
	}
	return 0;
}
