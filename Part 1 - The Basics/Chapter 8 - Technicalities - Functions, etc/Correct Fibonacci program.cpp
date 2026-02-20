#include "std_lib_facilities.h"
// 23/11/2022 - Fibonacci day, curious coincidence
//Fibonacci sequence
//Each number is the sum of the previous two
int main()
{
	constexpr int n {10};
	int ppx {}; //previous previous number - initialized to 0
	int px {};  //previous number
	int x {1};	 //number - initialized to 1
	
	for(int i=0;i<n;i++)
	{
		cout<<x<<'\n';
		ppx=px;
		px=x;
		x=ppx+px;
	}
	return 0;
}
