#include "std_lib_facilities.h"
//The exercise asks to not use standard library functions
//To get around this, we must look at the ASCII table, and take note of the decimal numbers for the start of uppercase letters and the end, and 
//the number to add to shift them into lowercase version
void to_lower(char* s)
{
	int count {0};
	while(true)
	{
		if(64 < s[count] && s[count] < 91 )
			s[count]+=32;
		else if(s[count] == 0) break;	//C style strings end with 0
		++count;
	}
}

int main()
{
	char my_string[]{ "Hello, World!" };
	cout << my_string << '\n';
	to_lower(my_string);
	cout << my_string << '\n';
	return 0;
}
