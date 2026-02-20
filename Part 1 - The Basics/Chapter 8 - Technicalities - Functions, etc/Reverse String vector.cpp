#include "std_lib_facilities.h"

void print(string s,vector<string>& v);	//Print the vector
void reverse_copy_vec(vector<string>& v);	//Create a reversed copy of the vector
void reverse_vec(vector<string>& v);		//Reverse the actual vector

int main()
{
	vector<string> v {"a", "e", "i", "o", "u"};
	print("v",v);
	
	reverse_copy_vec(v);
	print("rcv",v);
	
	reverse_vec(v);
	print("rv",v);
	return 0;
}

void print(string s,vector<string>& v)
{
	for(int i=0;i<v.size();i++)
	cout<<s<<": "<<v[i]<<'\n';
}

void reverse_copy_vec(vector<string>& v)
{
	vector<string> vc;					//vector copy
	for(int i=v.size()-1; i>=0;i--)	//start the loop from the last element to the first
		vc.push_back(v[i]);			//copy v to vc
	print("ircv",vc);
}

void reverse_vec(vector<string>& v)
{
	for(int i=0;i<v.size()/2;i++)	//the loop has to be done "v.size() / 2" because a swap operates with two elements, halving the number of loops
		swap(v[i],v[v.size()-1-i]);	//v.size()-1 is to avoid an out of range error, the "-i", is needed because (think of a mirror), one side has
}									//to reduce with the other
