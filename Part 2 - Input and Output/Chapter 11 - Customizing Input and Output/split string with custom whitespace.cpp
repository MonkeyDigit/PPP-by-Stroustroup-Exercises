#include "std_lib_facilities.h"
//we can't use the stringstream in this case, because we need to analyze each character and ignore specific ones
vector<string> split(const string& s, const string& w)
{
	//the vector to be returned
	vector<string> string_vect;
	
	//temp will be used to build words
	string temp{};
	for(int i=0;i<s.length();++i)
	{
		//with this loop we compare s[i] to all the characters in w, the string that contains custom whitespace characters
		bool is_ch_space {false};
		for(const char& space_ch : w)
		{
			if(s[i]==space_ch) is_ch_space=true;
		}
		
		//if s[i] is a whitespace or is_ch_space returned true, after comparing s[i] with w, insert temp into the vector
		if(isspace(s[i]) || is_ch_space )
		{
			if(temp.size()>0)
			{
				string_vect.push_back(temp);
				temp = {};
			}
		}
		else temp+=s[i];
		
		//we must make an exception for the last element, which we need to always include
		if(i==s.size()-1)
		{
			string_vect.push_back(temp);
		}
	}
	return string_vect;
}

int main()
{
	string whitespace {"-,;.!?"};
	/*
	cout << whitespace;
	
	for(char space_ch : whitespace)
	{
		cout <<space_ch;
	}
	*/
	
	string input_line;
	getline(cin,input_line);

	vector<string> word_list = split(input_line,whitespace);
	for(string s : word_list)
		cout << s << '\n';	
	return 0;
}
