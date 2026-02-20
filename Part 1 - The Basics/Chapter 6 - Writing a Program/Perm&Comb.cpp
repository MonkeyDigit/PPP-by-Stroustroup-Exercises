#include "std_lib_facilities.h"
//type __int64 can hold big integers
__int64 fact(int n);
__int64 perm(int n,int k);
__int64 comb(int n,int k);

int main()
{
	cout<<"Enter p to calculate a permutation \nEnter c to calculate a combination\n";
	char ch;
	cin>>ch;
	if(ch!='p' && ch!='c') error("Invalid choice");
	
	int n;
	int k;
	
	cout<<"Enter the number of elements\n";
	cin>>n;
	if(!cin || n<0) error("Expected a positive integer for n");
	cout<<"Enter the class\n";
	cin>>k;
	if(!cin || n<0) error("Expected a positive integer for k");
	
	if(ch=='p')
	{
		cout<<"Permutations: "<<perm(n,k)<<'\n';
	}
	else if(ch=='c')
	{
		cout<<"Combinations: "<<comb(n,k)<<'\n';
	}
	else error("Invalid response");
}

__int64 fact(int n)
{
	__int64 fact{1};
	for(int i=n;i>1;i--)
	{
		fact=(__int64)(fact*i);
	}
	if(fact<=0) error("Factorial to big to handle");
	return fact;
}

__int64 perm(int n, int k)
{
	__int64 r=(__int64)(fact(n)/fact(n-k));
	if(r<=0) error("Permutations too many to handle");
	return r;
}

__int64 comb(int n, int k)
{
	__int64 r=(__int64)(perm(n,k)/fact(k));
	if(r<=0) error("Combinations too many to handle");
	return r;
}
