#include "std_lib_facilities.h"

int main()
{
	int fibnum{};				//Vector that contains the Fibonacci sequence (1 1 2 3 5 8 13 21 34...)
	int prevnum{};
	int add{1};
	int n{};
	
	cout<<"Enter how many numbers of the Fibonacci sequence you want to compute: ";
	cin>>n;
	if(!cin) error("Couldn't read an integer!");
	for(int i=0;i<n;i++)
	{
		prevnum=fibnum;
		fibnum=fibnum+add;
		add=prevnum;
		cout<<fibnum<<'\n';
	}
	return 0;
}
