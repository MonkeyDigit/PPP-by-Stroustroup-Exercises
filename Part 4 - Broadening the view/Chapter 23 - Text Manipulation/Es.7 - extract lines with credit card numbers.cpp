#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>

using namespace std;
bool has_card_num(const string& s)
{
    regex pat {R"(\d{4}(-| )?\d{4}(-| )?\d{4}(-| )?\d{4}(-| )?)"};

    return regex_search(s,pat);
}

int main()
try
{
	ifstream ifs{"credit_card_file.txt"};
	
	if(!ifs) 
	{
		cerr << "Couldn't open input file\n";
		return 1;
	}
	
	cout << "Lines containing credit card numbers: \n";
	int lineno{0};
	
	for(string line; getline(ifs,line);)
	{
		++lineno;
		if(has_card_num(line))
		{
			cout << "Line no." << setw(2) << lineno << ": "
			<< line << '\n';
		}
	}
	return 0;
}
catch(exception& e)
{
	cerr << "Exception: " << e.what() << '\n';
	exit(1);
}
catch(...)
{
	cerr << "Unknown exception\n";
	exit(2);
}
