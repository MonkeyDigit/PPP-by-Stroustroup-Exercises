#include "std_lib_facilities.h"

vector<int> string_length(vector<string>&);	//a function can return a vector type, so: v=char_length(vv), means that v (also a vector) 
											//will have the elements returned by string_length, equal to vv
void long_short(vector<string>&,string&,string&);//find the longest and shortest string

void print(vector<int>& v)
{
	for(int x : v) cout<<x<<'\n';
}
							
int main()
{
	string long_s;
	string short_s;
	vector<string> string_vect {"abc", "defg","hi","jklmn"};
	
	vector<int> str_length=string_length(string_vect);	//vector that contains the length of each string in string_vect
	
	print(str_length);
	long_short(string_vect,long_s,short_s);
	
	cout<<"Longest string: "<<long_s<<'\n'
		<<"Shortest string: "<<short_s<<'\n';
	
	return 0;
}

vector<int> string_length(vector<string>& vs)
{
	vector<int> sl;
	for(string s : vs) sl.push_back(s.length());
	
	return sl;
}

void long_short(vector<string>& vs,string& long_s, string& short_s)
{	
	//variables to check the length
	int loc_l{};
	int loc_s = vs[0].length();
	//variables that will contain the longest and shortest strings
	string ls;
	string ss;
	
	for(string s : vs)
	{
		if(s.length()>loc_l)
		{
			loc_l=s.length();
			ls=s;
		}
		if(s.length()< loc_s)
		{
			loc_s=s.length();
			ss=s;
		}
	}
	
	long_s=ls;
	short_s=ss;
}
