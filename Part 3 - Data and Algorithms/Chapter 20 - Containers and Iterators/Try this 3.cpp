#include "std_lib_facilities.h"

void copy(int* f1, int* e1, int* f2)
{
	for (int* p = f1; p != e1; ++p)
        *f2++ = *p;                     // sets f2 value then increments f2 ptr
}

int main()
try
{
	return 0;
}
catch(exception & e)
{
	cerr<< "Exception: " << e.what() <<'\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
