#include "std_lib_facilities.h"

int main()
{
	char c;
	cin>>c;
	
	cin.putback(c);
	double v;
	cin>>v;
	
	cout<<v+5<<'\n';
	
	cin>>c;
	cout<<c;
}
