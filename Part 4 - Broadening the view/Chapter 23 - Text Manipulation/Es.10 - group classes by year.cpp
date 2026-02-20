#include "std_lib_facilities.h"
#include <string>

struct bad_from_string : std::bad_cast{	//class for reporting cast errors
	const char* what() const noexcept override
	{
		return "bad cast from string";
	}
};

template<typename T> T from_string(const string& s)
{
	istringstream is{s};
	T t;
	is>>t;
	if(!is) throw bad_from_string();
	return t;
}

bool get_class_year(const string& s,int& year)
{
	istringstream is{s};
	char ch;
	is>>ch;
	
	if(isdigit(ch))
	{
		is.unget();
		is>>year;
		return true;
	}
	return false;
}

int main()
{
	ifstream in {"table.txt"}; // input file
	if (!in) error("no input file");
	
	string line; // input buffer
	regex header {R"(^[\w ]+(	[\w ]+)*$)"}; // header line
	regex row {R"((^[\w ]+)(	\d+)(	\d+)(	\d+)$)"}; // data line
	if (getline(in,line))
	{ // check header line
		smatch matches;
		if (!regex_match(line, matches, header)) error("no header");
	}
	
	vector<int> years;
	vector<int> boys_per_year;
	vector<int> girls_per_year;
	
	int lineno = 0;
	// column totals:
	int boys = 0;
	int girls = 0;
	while (getline(in,line))
	{
		++lineno;
		smatch matches;
		if (!regex_match(line, matches, row))
			cerr << "bad line: " << lineno << '\n';
			
		if (in.eof()) cout << "at eof\n";
		
		// check row:
		
		int curr_boy = from_string<int>(matches[2]);
		int curr_girl = from_string<int>(matches[3]);
		int curr_total = from_string<int>(matches[4]);
		
		if (curr_boy+curr_girl != curr_total) error("bad row sum \n");
		
		int curr_year;
		if(get_class_year(matches[1],curr_year))
		{
			if(find(years,curr_year)==years.end())
			{
				years.push_back(curr_year);
				boys_per_year.push_back(curr_boy);
				girls_per_year.push_back(curr_girl);
			}
			else
			{
				int i = find(years,curr_year)-years.begin();
				boys_per_year[i]+=curr_boy;
				girls_per_year[i]+=curr_girl;
			}
		}
		
		if (matches[1]=="Alle klasser")
		{ // last line
			cout << "Table is valid\n";
			if (curr_boy != boys) error("boys don't add up\n");
			if (curr_girl != girls) error("girls don't add up\n");
			if (!(in>>ws).eof()) error("characters after total line");
		}
		// update totals:
		boys += curr_boy;
		girls += curr_girl;
	}
	
	if(years.size()!=boys_per_year.size() || years.size()!=girls_per_year.size())
		error("Wrong vector sizes");
	
	
	cout << "New table written to file \"newtable.txt\"\n";
	ofstream ofs{"newtable.txt"};
	ofs << "YEAR\t" << "BOYS\t" << "GIRLS\t" << "TOTAL\n";
	for(int i=0;i<years.size();++i)
		ofs << years[i] << '\t' 
		<< boys_per_year[i] << '\t' 
		<< girls_per_year[i] << '\t'
		<<boys_per_year[i]+girls_per_year[i] << '\n';
	
	ofs << "All classes\t" 
		<< accumulate(boys_per_year.begin(),boys_per_year.end(),0) << '\t'
		<< accumulate(girls_per_year.begin(),girls_per_year.end(),0) << '\t'
		<< accumulate(girls_per_year.begin(),girls_per_year.end(),0) + 
			accumulate(boys_per_year.begin(),boys_per_year.end(),0) << '\n';
}
