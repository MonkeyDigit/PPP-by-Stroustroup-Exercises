#include "std_lib_facilities.h"

int main()
{
	string iname;
	cout << "Please enter the input file name: ";
	cin >> iname;
	ifstream ifs {iname};
	if(!ifs) error("Couldn't open input file ",iname);
	
	ofstream ofs{"vowelsremoved.txt"}; 
	
	for(char ch; ifs.get(ch);)	//remember, get doesn't skip whitespace, it stops only with a newline
	{							//we need to copy all the letters, lower case and uppercase and all the spaces except for vowels
		switch(tolower(ch))
		{
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
			case 'y':
				break;
			default:
				ofs << ch;
		}
	}
	return 0;
}
