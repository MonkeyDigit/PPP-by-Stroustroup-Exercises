#include "std_lib_facilities.h"
/*
write a program to read a file of whitespace-separated numbers and output them in order (lowest value first), one value per line. Write a value 
only once, and if it occurs more than once write the count of its occurrences on its line. For example, 7 5 5 7 3 117 5 should give
3
5 3
7 2
117
*/

int main()
{
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open file ",iname);
	
	vector<int> nums;
	
	for(int n; ifs>>n;)
		nums.push_back(n);
	
	//sort the numbers
	sort(nums.begin(),nums.end());
	
	for(int i=0;i<nums.size();++i)
	{	//count is the number of times a number appears in the vector
		int count{};
		
		//if a number has been already printed, this will be false
		bool print{true};
		
		//compare a number with all other numbers
		for(int j=0;j<nums.size();++j)
		{
			if(nums[i]==nums[j])
			{
				++count;
				if(j<i)			//if there is a duplicate but it has already been printed (because j<i) then print= false
					print=false;
			}
		}
		if(print)
		{
			cout << nums[i];
			if(count>1) cout << '\t' << count << '\n';
			else cout << '\n';
		}
		
		
	}
	return 0;
}
