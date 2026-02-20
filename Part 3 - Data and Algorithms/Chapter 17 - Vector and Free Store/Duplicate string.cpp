#include "std_lib_facilities.h"

int c_str_len(const char* s)
    // return the length of a C-string in a char array including terminator
{
    int n = 0;
    while(s[n]) ++n;
    //cout << n << '\n';
    return n + 1;           // + 1 to include terminator
}

char* strdup(const char* c)
{
    const int n = c_str_len(c);

    char* s = new char[n];

    for (int i = 0; i < n; ++i)
        s[i] = c[i];

    return s;
}

int main()
{
	char cs1[] {"Hello, World!"};
	char* cs2 = strdup(cs1);
	
	for (int i = 0; cs2[i]; ++i)
        cout << cs2[i];

    cout << '\n';

    delete[] cs2;	//Remember to free memory on the free store to avoid leaks
	
	return 0;
}
