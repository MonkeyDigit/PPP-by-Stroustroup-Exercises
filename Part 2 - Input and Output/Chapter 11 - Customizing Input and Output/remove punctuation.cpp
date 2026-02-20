#include "std_lib_facilities.h"

int main()
{
	vector<string> string_vect;
	
	//input the words
	for(string s;cin>>s;)
		string_vect.push_back(s);
	
	//convert everything to lowercase
	//leave quotes intact
	//convert don't to do not and can't to cannot
	//leave hyphens within words intact
	bool in_quotes {false};
	for(string& s : string_vect)
	{
		//first convert all words to lowercase
		for(char& ch : s) ch=tolower(ch);
		
		if(s=="don't") s="do not";
		else if(s=="can't") s="cannot";
		else
		{
			for(char& ch : s)
			{	//leave anything in quotes intact
				if(ch == '\"' && !in_quotes)      in_quotes=true;	//when we encounter a quotation mark, then we are inside a quote, so don't touch anything
				else if (ch == '\"' && in_quotes) in_quotes=false;	//if we encounter another quotation mark, then it means we are exiting the quote
				else
				{
					if(!in_quotes)
					{
						if(ispunct(ch) && !(ch=='-' && s.length()>1)) ch = ' ';	//leave hyphens within words 
					}
				}
			}
		}
	}
	
	for(string& s : string_vect)
	{
		cout << s << ' ';
	}
	return 0;
}
