#include <iostream>
#include <regex>
#include <fstream>
int main()
try
{
	std::ifstream in {"postal_codes.txt"}; //input file
	if(!in) std::cerr << "no file\n";
	
	std::string pat_str{R"(\w{2}\s*\d{5}(-\d{4})?)"};
	std::regex pat{pat_str};
	
	std::cout << "Pattern: " << '\"' << pat_str << "\"\n";
	int lineno{0};
	for(std::string line;std::getline(in,line);)
	{
		++lineno;
		std::smatch matches;
		if(std::regex_search(line,matches,pat))
		{
			std::cout << lineno << ": " << matches[0] << '\n';	//whole match
			if(1<matches.size() && matches[1].matched)
				std::cout << "\t: " << matches[1] << '\n';		//sub-match
		}
			
	}
	return 0;
}
catch(std::exception& e)
{
	std::cerr << "Exception: " << e.what() << '\n';
	return 1;
}
catch(...)
{
	std::cerr << "Unknown exception\n";
	return 2;
}
