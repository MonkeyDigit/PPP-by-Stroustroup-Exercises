#include "std_lib_facilities.h"

int main()
{
	string iname;
	cin >>iname;
	ifstream ifs;
	if(iname == "h")
	{
		iname="test.txt";
		ifs.open(iname,ios_base::in);
	}
	
	if(ifs.is_open())
	{
		cout << "taking input from file";
	}
	else
	{
		cout<<"user input";
	}
	/*
	for(char ch; ifs>>ch;)
	{
		if(isalpha(ch))
		{
			cout << 1;
		}
	}
	*/
	return 0;
}
