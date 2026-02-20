#include "std_lib_facilities.h"
#include <unordered_map>
int main()
try
{
	unordered_map<string,int> um {
		{"lecture",21},
		{"table",34},
		{"binary tree",49},
		{"skyscraper",17}
			};
			
	for(const auto& p : um)
		cout << p.first << ' ' << p.second << '\n';
	return 0;
}
catch(exception& e)
{
	cerr << "Exception: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
