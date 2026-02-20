#include "std_lib_facilities.h"

int main()
{
	//string vect will take the content from the file, words (the vector) will be filled with the words without punctuation, and dictionary will have 
	
	//words sorted alphabetically and without duplicates
	vector<string> string_vect;
	
	//words from string vect without punctuation
	vector<string> words;
	
	//has to be sorted
	//can't have duplicates
	vector<string> dictionary;
	
	//entering the file
	string iname;
	cout << "Please enter the input file name: ";
	cin >> iname;
	ifstream ifs {iname};
	if(!ifs) error("Couldn't open input file ",iname);
	
	//filling string_vect
	for(string s; ifs>>s;)
		string_vect.push_back(s);
	
	//filling words without punctuation
	for(string& s : string_vect)
	{
		//first convert all words to lowercase
		for(char& ch : s) ch=tolower(ch);
		
		if(s=="don't") 
		{
			words.push_back("do");
			words.push_back("not");
		}
		else if(s=="can't") 
		{
			words.push_back("can");
			words.push_back("not");
		}
		else
		{
			string s_copy {};
			//take the word and remove punctuation
			//build s_copy char by char
			for(char& ch : s)
			{	
				if(!ispunct(ch) && isprint(ch))	//beware of unprintable characters
					s_copy+=ch;
				else if(s_copy.length()>1 && ch=='-')	//consider hyphen-separated words as two words (as-if)
				{
					words.push_back(s_copy); //take the first part, then reset s_copy and read the second part
					s_copy="";
				}
			}
			words.push_back(s_copy);
		}
	}
	
	//fill dictionary from words
	for(string& ws : words)
	{	// return false if the word is already present in the dictionary
		bool to_copy{true};
		for(string& ds : dictionary)
		{
			if(ws==ds)
			{
				to_copy=false;
				break;
			}
		}
		if(to_copy) dictionary.push_back(ws);
	}
	
	sort(dictionary.begin(),dictionary.end());
	for(string& ds : dictionary)
	{
		cout << ds <<'\n';
	}
	return 0;
}
