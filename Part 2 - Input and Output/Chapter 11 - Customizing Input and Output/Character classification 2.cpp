#include "std_lib_facilities.h"
/*
 isspace(c) Is c whitespace (' ', '\t', '\n', etc.)?
 isalpha(c) Is c a letter ('a'.. 'z', 'A'.. 'Z') (note: not '_')?
 isdigit(c) Is c a decimal digit ('0'.. '9')?
isxdigit(c) Is c a hexadecimal digit (decimal digit or 'a'.. 'f' or 'A'.. 'F')?
 isupper(c) Is c an uppercase letter?
 islower(c) Is c a lowercase letter?
isalnum(c) Is c a letter or a decimal digit?
iscntrl(c) Is c a control character (ASCII 0..31 and 127)?
 ispunct(c) Is c not a letter, digit, whitespace, or invisible control character?
isprint(c) Is c printable (ASCII ' '.. '~')?
isgraph(c) Is isalpha(c) or isdigit(c) or ispunct(c) (note: not space)?
*/

int main()
{
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open file ",iname);
	
	int space_count {};
	int alpha_count {};
	int digit_count {};
	int punct_count {};
	int upper_count {};
	int lower_count {};
	for(char ch; ifs.get(ch);)
	{
		if(isspace(ch))
		{
			++space_count;
		}
		else if(isalpha(ch))
		{
			++alpha_count;
		}
		else if(isdigit(ch))
		{
			++digit_count;
		}
		else if(ispunct(ch))
		{
			++punct_count;
		}
		if(isupper(ch))
		{
			++upper_count;
		}
		if(islower(ch))
		{
			++lower_count;
		}
	}
	
	cout<<"Number of specific characters: \n";
	if(space_count>0)
	{
		cout << setw(16) << "Space" << ": " << space_count <<'\n';
	}
	if(alpha_count>0)
	{
		cout << setw(16) << "Letter" << ": " << alpha_count <<'\n';
	}
	if(digit_count>0)
	{
		cout << setw(16) << "Number" << ": " << digit_count <<'\n';
	}
	if(punct_count>0)
	{
		cout << setw(16) << "Punctuation" << ": " << punct_count <<'\n';
	}
	if(upper_count>0)
	{
		cout << setw(16) << "Uppercase letter" << ": " << upper_count <<'\n';
	}
	if(lower_count>0)
	{
		cout << setw(16) << "Lowercase letter" << ": " << lower_count <<'\n';
	}
	else cout << "No characters";
	return 0;
}
