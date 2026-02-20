#include "std_lib_facilities.h"

int main()
{
	vector<int> fibnum{};				//Vector that contains the Fibonacci sequence (1 1 2 3 5 8 13 21 34...)
	int add{};
	int n{};
	
	cout<<"Enter how many numbers of the Fibonacci sequence you want to compute: ";
	cin>>n;
	if(!cin) error("Couldn't read an integer!");
	fibnum.push_back(1);
	
	for(int i=0;i<n;i++)
	{
		cout<<fibnum[i]<<'\n';
		fibnum.push_back(fibnum[i]+add);
		add=fibnum[i];
	}
	
	
}
