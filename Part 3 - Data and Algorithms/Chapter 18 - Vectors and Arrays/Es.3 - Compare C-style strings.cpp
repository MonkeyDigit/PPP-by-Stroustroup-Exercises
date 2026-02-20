#include "std_lib_facilities.h"
//returns -1 if s1 is lexicographically before s2
// 0 if equal
//1 if after
//does not account for uppercase
int cstrcmp(const char* s1, const char* s2)
{
	while(*s1)
	{
		if(*s1 < *s2) return -1;
		if(*s1 > *s2) return 1;
		s1++;
		s2++;
	}
	
	return 0;
}

int main()
try
{
	char s1[] {"abc"};
	char s2[] {"aba"};
	
	cout << cstrcmp(s1,s2);
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
