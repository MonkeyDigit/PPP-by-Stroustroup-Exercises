#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>

using namespace std;
bool has_date(const string& s)
    // pat1 = 12/24/2004
    // pat2 = Mon(,) Feb 26 2018 (comma optional)
    // pat3 = January 12, 1995
{
    std::regex pat1 {R"(\d{2}/\d{2}/\d{4})"};
    std::regex pat2 {R"(\b[A-Za-z]+,? [A-Za-z]+ \d{1,2} \d{4}\b)"};
    std::regex pat3 {R"(\w+ \d{1,2}, \d{4}\b)"};

    return std::regex_search(s, pat1) ||
           std::regex_search(s, pat2) ||
           std::regex_search(s, pat3);
}

int main()
try
{
	ifstream ifs{"date_file.txt"};
	
	if(!ifs) cerr << "Couldn't open input file\n";
	
	cout << "Lines containing dates: \n";
	int lineno{0};
	
	for(string line; getline(ifs,line);)
	{
		++lineno;
		smatch matches;
		if(has_date(line))
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
