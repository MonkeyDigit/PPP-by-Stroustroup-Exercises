#include "std_lib_facilities.h"

void print_until_s(vector<string> v, string quit)
{
	for(string s : v)			//string s is going to assume each value present in the vector v, so it needs to be of the same type
	{
		if (s==quit) return;
		cout << s << " " << '\n';
	}
}

void print_until_ss(vector<string> v, string quit)
{
	int quit_count{};
	for(string s : v)
	{
		if (s==quit) quit_count++;
		if(quit_count  >= 2) return;
		cout << s << " " << '\n';
	}
}

int main()
{
	const string quit="exit";
	vector<string> v {"hello","my","name","is","exit","marco"};
	print_until_s(v,quit);
	
	vector<string> vv {"hello","my","name","is","exit","marco","and","exit","that's it"};
	print_until_ss(vv,quit);
	return 0;
}
