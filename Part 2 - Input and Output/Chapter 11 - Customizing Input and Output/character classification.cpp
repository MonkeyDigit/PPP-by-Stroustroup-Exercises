#include "std_lib_facilities.h"

int main()
{
	vector<string> string_vect;
	for(string s; cin>>s;)
		string_vect.push_back(s);
		
	for(string& s : string_vect)
	{
		for(char& ch : s)	//a string is a vector of characters
		{
			string chtype;
			if(isalpha(ch))
			{
				chtype="letter";
			}
			else if(isdigit(ch))
			{
				chtype="digit";
			}
			else if(ispunct(ch))
			{
				chtype="punctuation";
			}
			else if(iscntrl(ch))
			{
				chtype="control character";
			}
			else if(isprint(ch))
			{
				chtype="printable";
			}
			else
			{
				chtype="unknown";
			}
			cout << ch << ' ' << chtype << '\n';
		}
		cout << '\n';
	}
	return 0;
}
