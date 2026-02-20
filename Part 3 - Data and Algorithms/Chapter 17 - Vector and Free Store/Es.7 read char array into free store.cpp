#include "std_lib_facilities.h"

int main()
{
	char ch;
	vector<char> char_vect;
	while (cin.get(ch) && ch!='!')	//cin.get to preserve whitespace
	{
		char_vect.push_back(ch);
	}
	
	char* char_array = new char[char_vect.size()];
	for(int i=0;i<char_vect.size();++i)
	{
		char_array[i]=char_vect[i];
	}
	
	//Just to verify that it works
	for(int i=0;i<char_vect.size();++i)
	{
		cout<<char_array[i];
	}
	
	delete[] char_array;
	return 0;
}
