#include "std_lib_facilities.h"

int main()
{
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open file ",iname);
	
	vector<string> words;
	
	for(string s; ifs>>s;)
		words.push_back(s);
		
	ofstream ofs {"words_reverse.txt"};
	
	for(int i=words.size()-1; i>=0;--i)
		ofs << words[i] << ' ';
	return 0;
}
