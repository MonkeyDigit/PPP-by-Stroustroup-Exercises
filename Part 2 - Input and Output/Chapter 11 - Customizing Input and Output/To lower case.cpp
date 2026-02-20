#include "std_lib_facilities.h"

int main()
{
	string iname;
	cout << "Please enter the input file name: ";
	cin >> iname;
	ifstream ifs {iname};
	if(!ifs) error("Couldn't open input file ",iname);
	
	ofstream ofs {"es1lowercase.txt"};
	for(char ch; ifs.get(ch);)		//The istream::get() function reads a single character into its argument. It does not 
	{								//skip whitespace. Like >>, get() returns a reference to its istream so that we can test its state
		ch=tolower(ch);
		ofs << ch;
	}
	return 0;
}
