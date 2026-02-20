#include "std_lib_facilities.h"

void print (string,vector<int>& v);
void fibonacci(int x,int y,vector<int>& v,int n);	//vector v for the numbers, n for the number of elements, x is v[0], y is v[2]
													//REMEMBER: Each number is the sum of the previous two
	
								
int main()
{
	vector<int> v;			//Random numbers
	constexpr int x{1};
	constexpr int y{2};
	constexpr int n{10};
	/*
	cout<<"Enter two starting numbers for the Fibonacci sequence\n"<<"1: ";
		cin>>x;
		if(!cin) error ("Couldn't read an int");
		
	cout<<"2: ";
	cin>>y;
		if(!cin) error ("Couldn't read an int");
		
	cout<<"\nEnter the numbers of elements to output: ";
	cin>>n;
	*/
	fibonacci(x,y,v,n);
	print("fib",v);
	return 0;
}



void print(string s,vector<int>& v)
{
	for(int i=0;i<v.size();i++)
	cout<<s<<": "<<v[i]<<'\n';
}

void fibonacci(int x,int y,vector<int>& v,int n)	//Since we have x and y, we don't need variables like ppx and px like in the Correct Fibonacci program made before
{	
	int f{};
	v.push_back(x);
	v.push_back(y);
	
	for (int i=2; i<n;i++)	//Since v[0] and v[1] are filled, "i" starts from 2
	{
		f=v[i-1]+v[i-2];
		v.push_back(f);
	}
}

