#include "std_lib_facilities.h"

int main()
{
	string iname;
	cout << "Please enter the input file name: ";
	cin >> iname;
	ifstream ifs {iname};
	if(!ifs) error("Couldn't open input file ",iname);
	
	string word;
	cout << "Enter a word: ";
	cin >> word;
	
	//getline reads input until newspace
	int line_count {};
	for(string line; getline(ifs,line);) //read from ifs into line
	{
		++line_count;
		stringstream read_line {line};	//initialize a stringstream read_line to read each word into find_word separated by whitespace
		for(string find_word; read_line >> find_word;)
		{
			if(find_word == word)
			{
				cout << "Line " << line_count << ": " << line << '\n';
			}
		}
	}
	return 0;
}
