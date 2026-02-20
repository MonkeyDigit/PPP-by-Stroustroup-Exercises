#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> prime_v;
	int num{50000};
	bool prime;
	
	for(int i=2;i<=num;i++)
	{
		prime=true;
		for(int j=i-1;j>1;j--)
		{
			if(i%j==0)
			{
				prime=false;
			}
		}
		if(prime)
		{
			prime_v.push_back(i);
			cout<<i<<endl;
		}
	}
	
	cout<<prime_v.size();
	
}
