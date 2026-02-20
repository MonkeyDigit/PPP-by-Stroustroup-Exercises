#include "std_lib_facilities.h"

bool is_palindrome(const char s[], int n)
// s points to the first character of an array of n characters
{
	int first = 0; // index of first letter
	int last = n-1; // index of last letter
	while (first < last) { // we haven’t reached the middle
	if (s[first]!=s[last]) return false;
	++first; // move forward
	--last; // move backward
}
return true;
}

//Solution a
/*
istream& read_word(istream& is, char* buffer, int max)
// read at most max–1 characters from is into buffer
{
	is.width(max); // read at most max–1 characters in the next >>
	is >> buffer; // read whitespace-terminated word,
	// add zero after the last character read into buffer
	
	//check if the input was terminated by whitespace or if the string was truncated
	char ch;
	is.get(ch);
	if(!isspace(ch)) //this means that string has > max-1 characters
	{
        cout << "Input cut off after " << max-1 << " characters!\n";
        while (is.get(ch))
		{
            if (ch=='\n') break;
        }
	}
	return is;
}
*/

//Solution b
istream& read_long_word(istream& is, char*& buffer) {
    int max = 128;
    char* temp1 = new char[max];
    *temp1 = 0;
    char ch;
    while (cin.get(ch)) {
        if (ch=='\n') break;
        if (strlen(temp1) == max-1) {
            // double length of temp1
            char* temp2 = new char[max];
            strcpy(temp2,temp1);
            delete[] temp1;
            max *= 2;
            temp1 = new char[max];
            strcpy(temp1,temp2);
            delete[] temp2;
        }
        temp1[strlen(temp1)+1] = 0;
        temp1[strlen(temp1)] = ch;
    }
    buffer = temp1;
    return is;
}

int main()
try
{
	//Solution a
	/*
	constexpr int max = 5;
	for (char s[max]; read_word(cin,s,max); )
	{ 
		cout << s << " is";
		if (!is_palindrome(s,strlen(s))) cout << " not";
		cout << " a palindrome\n";
	}
	*/
	
	//Solution b
	for(char* s; read_long_word(cin,s);)
	{
		for(int i=0;s[i];++i)
			cout << s[i];
		cout << " is";
		if (!is_palindrome(s,strlen(s))) cout << " not";
		cout << " a palindrome\n";
	}
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
