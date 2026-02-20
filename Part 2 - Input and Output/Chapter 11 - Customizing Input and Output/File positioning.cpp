#include "std_lib_facilities.h"

int main()
{
	string name;
	cin>>name;
	fstream fs {name}; // open for input and output
	if (!fs) error("can't open ",name);
	
	fs.seekg(5); // move reading position (g for “get”) to 5 (the 6th character)
	char ch;
	fs>>ch; // read and increment reading position
	cout << "character[5] is " << ch << " (" << int(ch) << ")\n";
	
	fs.seekp(1); // move writing position (p for “put”) to 1
	fs<<'y'; // write and increment writing position
	return 0;
}
