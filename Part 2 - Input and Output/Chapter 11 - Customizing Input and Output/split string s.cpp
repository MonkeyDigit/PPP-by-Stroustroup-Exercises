#include "std_lib_facilities.h"
//there are two ways to do this
/*
vector<string> split(const string& s)
{
	vector<string> vs;
	string temp{};
	for(int i=0;i<s.size();++i)	//we need to use an index because we must make an exception for the last element in s
	{
		if(isspace(s[i]))
		{
			vs.push_back(temp);
			temp = {};
		}
		else
			temp+=s[i];
		if(i==s.size()-1)
		{
			vs.push_back(temp);
		}
	}
	return vs;
}
*/

//this is shorter
vector<string> split(const string& s)
{
	vector<string> vs;
	stringstream ss {s};		//this simulates user input, and since >> stops at whitespace, the input of words will be separated automatically
	for(string word; ss>>word;)
	{
		vs.push_back(word);
	}
	return vs;
}

int main()
{
	string input_line;
	getline(cin,input_line);
	vector<string> word_list = split(input_line);
	for(string s : word_list)
		cout << s << '\n';
	return 0;
}
