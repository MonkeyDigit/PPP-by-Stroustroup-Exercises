#include "std_lib_facilities.h"

char* cat_dot(const char* s1, const char* s2)
{
	const char* cs1 = s1;	//first we copy s1 and s2 to traverse through them. we do this because we must traverse through them 2 times
	const char* cs2 = s2;	
	int strlen;
	while(*cs1++) strlen++;
	while(*cs2++) strlen++;
	strlen++; //add 1 for the dot
	
	char* s = new char[strlen+1];	//add 1 for the terminating 0
	char* m = s;
	
	while(*s1) *m++ = *s1++;
	*m++ = '.';
	while(*s2) *m++ = *s2++;
	*m = 0;
	return s;
}

char* cat_dot_sep(const char* s1, const char* s2, const char* sep)
{
	const char* cs1 = s1;
	const char* cs2 = s2;
	const char* csep = sep;
	int strlen;
	while(*cs1++) strlen++;
	while(*cs2++) strlen++;
	while(*csep++) strlen++;
	
	char* s = new char[strlen+1];	//add 1 for the terminating 0
	char* m = s;
	
	while(*s1) *m++ = *s1++;
	while(*sep) *m++ = *sep++;
	while(*s2) *m++ = *s2++;
	*m = 0;
	return s;
}

int main()
try
{
	char s1[] {"Niels"};
	char s2[] {"Bohr"};
	char sep[] {"DOT"};
	char* str = cat_dot(s1,s2);
	char* str2 = cat_dot_sep(s1,s2,sep);
	
	for(int i=0; str[i]; ++i)
		cout << str[i];
	cout<<'\n';
	for(int i=0; str2[i]; ++i)
		cout << str2[i];
	
	delete[] str;
	delete[] str2;
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
