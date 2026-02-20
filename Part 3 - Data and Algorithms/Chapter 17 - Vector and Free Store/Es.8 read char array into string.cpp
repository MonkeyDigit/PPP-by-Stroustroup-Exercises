#include "std_lib_facilities.h"

int main()
{
	string store = "";

    cout << "Enter some characters. Terminate with '!'\n";
    char ch;
    while (cin.get(ch) && ch != '!')
        store += ch;

    cout << store << '\n';
	return 0;
}
