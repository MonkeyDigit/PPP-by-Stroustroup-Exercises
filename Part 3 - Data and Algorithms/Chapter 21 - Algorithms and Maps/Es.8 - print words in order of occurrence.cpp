#include "std_lib_facilities.h"
#include <map>
int main()
try
{
	map<string,int> words; // keep (word,frequency) pairs
	for (string s; cin>>s; )
		++words[s]; // note: words is subscripted by a string
	
	multimap<int,string> word_val;
	
	for (const auto& p : words)
		word_val.insert(pair<int,string>{p.second,p.first});
	
	for (const auto& p : word_val)
		cout << p.first << ": " << p.second << '\n';
}
catch(exception & e)
{
	cerr<< "Exception: " << e.what() <<'\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
