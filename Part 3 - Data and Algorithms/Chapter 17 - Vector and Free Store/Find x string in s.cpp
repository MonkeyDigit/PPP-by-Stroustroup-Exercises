#include "std_lib_facilities.h"

int c_str_len(const char* s)
    // return the length of a C-string in a char array including terminator
{
    int n = 0;
    while(s[n]) ++n;
    //cout << n << '\n';
    return n + 1;           // + 1 to include terminator
}
/*
const char* findx(const char* s, const char* x)
{
	if(c_str_len(x) < c_str_len(s))
	{
		for(int i=0;i<c_str_len(s)-1;++i)
		{
			bool found {true};
			for(int j=0;j<c_str_len(x)-1;++j)
			{
				if (s[i+j] != x[j])
				{
					found = false;
					break;
				}
			}
			if(found)
			{
				return &s[i];
			}
		}
	}
	return nullptr;
}
*/

const char* findx(const char* s, const char* x)
{
    for (int i = 0; s[i]; ++i)
        if (s[i] == x[0]) {
            for (int j = 1; ; ++j)
                if (!x[j]) {
                    return &s[i];
                } else if (x[j] != s[i + j]) {
                    break;
                }
        }

    return nullptr;         // returned for falsey test
}

int main()
try {
    char cs1[] = "For the Horde?";
    char cs2[] = "Horde";
    char cs3[] = "Alliance";

    const char* found = findx(cs1, cs2);
    const char* not_found = findx(cs1, cs3);

    if (found)
        cout << "Glory to the Horde!!" << found << '\n';

    if (not_found)
        cout << "Glory to the Alliance!!" << not_found << '\n';
}

catch(std::exception& e) {
    cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "unknown exception\n";
    return 2;
}
