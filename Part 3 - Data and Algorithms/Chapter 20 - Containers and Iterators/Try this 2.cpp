#include "std_lib_facilities.h"

/*
double* high(double* first, double* last)
// return a pointer to the element in [first,last) that has the highest value
{
	double h = -1;
	double* high;
	for(double* p = first; p!=last; ++p)
		if (h<*p) { high = p; h = *p; }
	return high;
}
*/

//errors:
// line 7: double h = -1;   --  magic constant. if we wanted to measure temperatures in antartica this would probably give wrong results

// line 8: double* high;    --  uninitialized pointer. this implies that when the container is empty (first==last), the pointer returned (high) points to some
//								unknown location in memory

double* high(double* first, double* last)
// return a pointer to the element in [first,last) that has the highest value
{
	if(first==last) return nullptr;
	
	double h = *first;
	double* high;
	for(double* p = first; p!=last; ++p)
		if (h<*p) { high = p; h = *p; }
	return high;
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
