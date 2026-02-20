#include "std_lib_facilities.h"

const char* findx(const char* s, const char* x)
{
	const char* fstr = s;
	while(*fstr++)	//copy of s to traverse through it
	{
		const char* sstr = fstr; // copy of s which resets when x isn't in s
		const char* xstr = x; // copy of x which resets when it isn't in s
		bool found = true;
		while(*xstr)
		{
			if(*sstr++ != *xstr++) found = false;
		}
		
		if(found)
		{
			return s;
		}
	}
	
	return nullptr;
	
}

int main()
try
{
	char cs1[] = "For the Horde?";
    char cs2[] = "Horde";
    char cs3[] = "Alliance";

    const char* found = findx(cs1, cs2);
    const char* not_found = findx(cs1, cs3);

    if (found)
        cout << "Glory to the Horde!!" << found << '\n';

    if (not_found)
        cout << "Glory to the Alliance!!" << not_found << '\n';
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
