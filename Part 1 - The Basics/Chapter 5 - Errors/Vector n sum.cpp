#include "std_lib_facilities.h"

int main()
{
	vector<int> nums;
	int n{};
	int i{};
	int sum{};
	
	cout<<"Enter the number of values you want to sum: "; //enter values into nums, then sum n elements starting from nums[0]
	cin>>n;
	if(!cin) error("Couldn't read an integer!");
	
	cout<<"Enter some integers (press '|' to stop):\n";
	for(double num;cin>>num;)
	{
		int test=narrow_cast<int>(num);						//if num is not an integer, an error is thrown
		nums.push_back(num);
		if(i<n)
		{
			sum+=num;
			i++;
		}
	}
	
	if(n<=nums.size())
	{
		cout<<"The sum of the first "<<n<<" values (";
		for(int i=0;i<n;i++)
		{
			cout<<nums[i]<<";";
		}
		cout<<") is: "<<sum;
	}
	else
	{
		error("Not enough values to sum!");
	}
}
