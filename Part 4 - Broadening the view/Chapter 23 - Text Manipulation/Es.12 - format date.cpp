#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>

using namespace std;
int main()
try
{
	ifstream ifs{"to_format.txt"};
	
	if(!ifs) cerr << "Couldn't open input file\n";
	
	std::regex pat1 {R"(\d{1,2}/\d{2}/\d{4})"};
    std::regex pat2 {R"(\b[A-Za-z]+,? [A-Za-z]+ \d{1,2} \d{4}\b)"};
    std::regex pat3 {R"(\w+ \d{1,2}, \d{4}\b)"};
    
	vector<string> words;
	
	for(string w; ifs>>w;)
	{
		istringstream is{w};
		int day;
		int month;
		int year;
		char ch;
		if(regex_search(w,pat1) || regex_search(w,pat2) || regex_search(w,pat3))
		{
			if(regex_search(w,pat3))
			{
				string smonth;
				is>>smonth;
				if(smonth=="January")
					month=1;
				else if(smonth=="February")
					month=2;
				else if(smonth=="March")
					month=3;
				else if(smonth=="April")
					month=4;
				else if(smonth=="May")
					month=5;
				else if(smonth=="June")
					month=6;
				else if(smonth=="July")
					month=7;
				else if(smonth=="August")
					month=8;
				else if(smonth=="September")
					month=9;
				else if(smonth=="October")
					month=10;
				else if(smonth=="November")
					month=11;
				else if(smonth=="December")
					month=12;
					
				is>>day>>ch;
				if(ch!=',') is.unget();
				is>>year;
			}
			else
			{
				is>>day>>ch;
				is>>month>>ch;
				is>>year;
			}
			
			w="";
			w+=to_string(year)+'-'+to_string(month)+'-'+to_string(day);
		}
		
		words.push_back(w);
	}
	
	ofstream ofs {"formatted_dates.txt"};
	
	for(const string& w : words)
	{
		ofs << w << ' ';
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
