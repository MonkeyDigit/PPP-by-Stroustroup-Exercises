#include "std_lib_facilities.h"

int main()
{
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open file ",iname);
	
	vector<char> chars;
	for(char ch; ifs.get(ch);)
	{
		chars.push_back(ch);
	}
	
	ofstream ofs {"reverse_order.txt"};
	
	for(int i=chars.size()-1; i>=0;--i)
	{
		cout << chars[i];
		ofs << chars[i];
	}
	
	return 0;
}
