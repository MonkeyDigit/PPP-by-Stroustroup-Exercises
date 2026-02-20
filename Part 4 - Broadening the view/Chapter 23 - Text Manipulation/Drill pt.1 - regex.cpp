#include <iostream>
#include <regex>
#include <string>
int main()
try
{
	std::string spat{R"(\w{3}\d{2})"};
	std::regex pat{spat};
	std::cout << "Pattern: " << spat << '\n';
	for(std::string ss;getline(std::cin,ss);)
	{
		std::smatch matches;
		if(std::regex_match(ss,matches,pat))
		{
			std::cout << "Matches!\n\n";
		}
		else
		{
			std::cout << "Doesn't match!\n\n";
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
