#include "std_lib_facilities.h"

char* strdup(const char* cstr)
{
	if(cstr == nullptr) return nullptr;
	//get string length
	int strlen = 0;
	const char* p = cstr;
	while(*p++) ++strlen;
	
	char* dup = new char[strlen+1]; //allocate strlen number of chars on the free store
	char* cdup = dup;
	
	while(*cstr) *cdup++ = *cstr++; //we use cdup so that dup points to the first character, and the elements get copied
	*cdup = 0;	//add terminating 0
	
	return dup;
}

int main()
try
{
	char my_string[] {"my_string"};
	char* my_string2 = strdup(my_string);
	
	for(int i=0;my_string[i];++i)
		cout<<my_string[i];
		
	for(int i=0;my_string2[i];++i)
		cout<<my_string2[i];
		
	delete[] my_string2;
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
