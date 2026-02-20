#include "std_lib_facilities.h"

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
	if(!(is >> t)) throw bad_from_string();
	return t;
}

int main()
{
	ifstream in {"newtable.txt"}; // input file
	if (!in) error("no input file");
	
	string line; // input buffer
	regex header {R"(^[\w ]+(	[\w ]+)*$)"}; // header line
	regex row {R"((^[\w ]+)(	\d+)(	\d+)(	\d+)$)"}; // data line
	if (getline(in,line))
	{ // check header line
		smatch matches;
		if (!regex_match(line, matches, header)) error("no header");
	}
	
	int lineno = 0;
	// column totals:
	int boys = 0;
	int girls = 0;
	
	int prev_total{0};
	
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
		
		
		if (matches[1]=="All classes")
		{ // last line
			cout << "Table is valid\n";
			if (curr_boy != boys) error("boys don't add up\n");
			if (curr_girl != girls) error("girls don't add up\n");
			if (!(in>>ws).eof()) error("characters after total line");
		}
		else if(prev_total)
		{
			cout << "Year " << matches[1] << ": ";
			if(curr_total>prev_total)
			{
				cout << "Student number increase\n";
			} 
			else if(curr_total<prev_total)
			{
				cout << "Student number decrease\n";
			} 
			else
				cout << "Student number steady\n";
		}
			
		// update totals:
		prev_total=curr_total;
		boys += curr_boy;
		girls += curr_girl;
	}
	
}
