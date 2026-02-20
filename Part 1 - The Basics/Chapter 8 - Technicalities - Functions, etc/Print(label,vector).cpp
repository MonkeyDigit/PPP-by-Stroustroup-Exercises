#include "std_lib_facilities.h"

void print(string,vector<int>&);	//The vector is passed by reference while the string isn't
									//Doing so, the vector is read directly, as opposed to read, copied, and passed
int main()
{
	vector<int> vec1;
	vector<int> vec2;
	
	for(int i=0;i<25;i++)
	{
		vec1.push_back(i);
	}
	
	for(int i=0;i<18;i++)
	{
		vec2.push_back(-i);
	}
	
	print("vec1",vec1);
	print("vec2",vec2);
	return 0;
}

void print(string s,vector<int>& v)
{
	for(int i=0;i<v.size();i++)
	cout<<s<<": "<<v[i]<<'\n';
}
