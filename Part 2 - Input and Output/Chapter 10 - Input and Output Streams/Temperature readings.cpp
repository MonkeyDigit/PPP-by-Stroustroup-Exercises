#include "std_lib_facilities.h"

const int not_a_reading = -7777;
const int not_a_month = -1;

//Types Day,Month,Year---------------------------------------------------------
struct Day {
	vector<double> hour {vector<double>(24,not_a_reading)};	//this will initialize the elements of hour [0:23] with not_a_reading
};															//(in  each element goes the temperature reading of that hour)

struct Month { // a month of temperature readings
	int month {not_a_month}; // [0:11] January is 0
	vector<Day> day {32}; // [1:31] one vector of readings per day - day[0] is "wasted" to keep the code simple 
};

struct Year { // a year of temperature readings, organized by month
	int year; // positive == A.D.
	vector<Month> month {12}; // [0:11] January is 0
};

struct Reading {
 int day;
 int hour;
 double temperature;
};
//READING EXAMPLE: { year 1992 { month jan ( 1 0 61.5) } {month feb (1 1 64) (2 2 65.2) } }
//Defining operators-------------------------------------------------------------------------
//Reading >>
istream& operator>>(istream& is, Reading& r)
// read a temperature reading from is into r
// format: ( 3 4 9.7 )
// check format, but don’t bother with data validity
{
	char ch1;
	if (is>>ch1 && ch1!='(') // could it be a Reading?
	{ 
		is.unget();
		is.clear(ios_base::failbit);
		return is;			//if the format doesn't start plausibly, state to fail() and return. This allows us to try to read the information in some other way
	}	//like the unget token function from the calculator, here we "unget" the character that prompted the fail() state, as it might be useful elsewhere
	
	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if (!is || ch2!=')') error("bad reading"); // messed-up reading
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;
//check if a reading is valid
bool is_valid(const Reading& r)
// a rough test
{
	if (r.day<1 || 31<r.day) return false;
	if (r.hour<0 || 23<r.hour) return false;
	if (r.temperature<implausible_min|| implausible_max<r.temperature)
		return false;
	return true;
}

//Look for the terminator
void end_of_loop(istream& ist, char term, const string& message)
{
	if (ist.fail())
	{ // use term as terminator and/or separator
		ist.clear();
		char ch;
		if (ist>>ch && ch==term) return; // all is fine
		error(message); //we get here if nothing is left in the buffer (so ist.eof() ), or the character is not the terminator
	}
}
//Month functions--------------------------------------------------------------
vector<string> month_input_tbl = {
	"jan", "feb", "mar", "apr", "may", "jun", "jul", 
	"aug", "sep", "oct", "nov", "dec"
};
int month_to_int(string s)
// is s the name of a month? If so return its index [0:11] otherwise –1
{
	for (int i=0; i<12; ++i) if (month_input_tbl[i]==s) return i;
	return -1;
}

vector<string> month_print_tbl = { 
 "January", "February", "March", "April", "May", "June", "July", 
 "August", "September", "October", "November", "December"
};
string int_to_month(int i)
// months [0:11]
{
 if (i<0 || 12<=i) error("bad month index");
 return month_print_tbl[i];
}

//Month >>
istream& operator>>(istream& is, Month& m)
// read a month with readings, from is into m
// format: { month feb . . . } - {month feb (10 12 56.73) (11 14 58.45) ...}
{
	char ch = 0;
	if (is >> ch && ch!='{')
	{
		is.unget();
		is.clear(ios_base::failbit); // we failed to read a Month
		return is;
	}
	
	string month_marker;
	string mm;
	
	is >> month_marker >> mm;
	if (!is || month_marker!="month") error("bad start of month");
	m.month = month_to_int(mm);
	
	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r; )
	{
		if (is_valid(r))
		{
			if (m.day[r.day].hour[r.hour] != not_a_reading)	//if we try to insert a reading multiple times, an error is given
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else
		++invalids;
	}
	if (invalids) error("invalid readings in month",invalids);
	if (duplicates) error("duplicate readings in month", duplicates);
	
	end_of_loop(is,'}',"bad end of month"); //check for terminator, print an error message if it's not found
	return is;
}

//Year functions------------------------------------------------------
void print_year(ostream& ofs, Year y) 	//will print a single year
{
	ofs << "{ year " << y.year << ' ';
	for(int i=0; i < y.month.size();++i)
	{
		if(y.month[i].month!=not_a_month)
		{
			ofs << "{ month " << int_to_month(i) << ' ';
			for(int j=1; j<32;++j)	//starts from 1 because day[0] isn't used - [1:31]
			{
				for(int k=0;k<24;++k)
				{
					if(y.month[i].day[j].hour[k] != not_a_reading)
						ofs << "(" << j << ' ' << k << ' ' << y.month[i].day[j].hour[k] << ") "; //(day hour temp)
				}
			}
			ofs << "} ";
		}
	}
	
	ofs << "} \n";
}

//Year >>
istream& operator>>(istream& is, Year& y)
// read a year from is into y
// format: { year 1972 . . . }
{
	char ch;
	is >> ch;
	if (ch!='{')
	{
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	
	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker!="year") error("bad start of year");
	y.year = yy;
	
	/*Previous version of the loop
	while(true)
	{
		Month m; // get a clean m each time around
		if(!(is >> m)) break;
		y.month[m.month] = m;
	}
	*/
	for (Month m; is >> m; )
	{
		y.month[m.month] = m;
		m = Month{}; // “reinitialize” m
	}
/*
NOTE:
we didn't use:
	for(Month m; is >> m;)
		y.month[m.month] = m;
because, in this case, the Month variable m is declared once but used multiple times. So when we need to enter another month with its own readings,
m.month will change, but since we are just modifying, so not initializing, m, other attributes will stay, like the readings, so if we were to use this loop,
we risk having a month with the readings of the previous month added in.
*/
	end_of_loop(is,'}',"bad end of year");
	return is;
}

//Main----------------------------------------------------------------------------------------------------
int main()
{
	// open an input file:
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open input file",iname);
	ifs.exceptions(ifs.exceptions()|ios_base::badbit); // throw for bad()
	
	// open an output file:
	cout << "Please enter output file name\n"; 
	string oname;
	cin >> oname;
	ofstream ofs {oname};
	if (!ofs) error("can't open output file",oname);
	
	// read an arbitrary number of years:
	vector<Year> ys;
	while(true) {
		Year y; // get a freshly initialized Year each time around
		if (!(ifs>>y)) break;
		ys.push_back(y);
	}
	
	cout << "read " << ys.size() << " years of readings\n";
	for (Year& y : ys) print_year(ofs,y);
	return 0;
}
