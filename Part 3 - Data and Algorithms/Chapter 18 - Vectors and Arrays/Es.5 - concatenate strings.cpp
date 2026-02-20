#include "std_lib_facilities.h"

string cat_dot(const string& s1, const string& s2)
{
	return s1+'.'+s2;
}

int main()
try
{
	string str = cat_dot("Niels","Bohr");
	cout << str;
	return 0;
}

catch(exception& e)
{
	cerr<<"error:"<<e.what()<<'\n';
	keep_window_open();
	return 1;
}

catch(...)
{
	cerr<<"Unknown error"<<'\n';
	keep_window_open();
	return 2;
}
