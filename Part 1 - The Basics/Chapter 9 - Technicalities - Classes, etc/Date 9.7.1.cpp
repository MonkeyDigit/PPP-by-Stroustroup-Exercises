#include "std_lib_facilities.h"
//MONTH ENUMERATION CLASS	-	They are essentially symbolic constants
enum class Month {										//Notice the difference: when an enum is declared as an enum class, every time you try to access the 
	Jan=1,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec	//constants inside, you must specify the scope (Month::jan), and to convert to int ->int(Month::jan)
};

//MONTH OPERATORS
Month operator++(Month& m) // prefix increment operator
{
	m = (m == Month::Dec) ? Month::Jan : Month(int(m)+1); // “wrap around”
	return m;
}

//DATE CLASS
class Date {
public:
	Date();						//Default constructor - sets the default values, the date, of a declared Date variable
	Date(int y);				//January 1 of year y
	Date(int yy,int mm,int dd);
	class Invalid {};			//Invalid type to throw in case of an invalid date
	int year() {return y;};		//this prevents access to private members directly
	Month month() {return m;};
	int day() {return d;};
	void add_day(int n);
private:
	int y;
	Month m;
	int d;
	bool is_valid();	//check if date is valid
};

//DATE CONSTRUCTORS
Date::Date() : y(2001), m(Month::Jan), d(1) {}	//1st day of the 21st century

Date::Date(int yy) : y(yy), m(Month::Jan), d(1)
{
	if(!is_valid()) throw Invalid{};
} 

Date::Date(int yy, int mm,int dd) : y(yy), m(Month(mm)), d(dd) //today {1978,6,25} ->the month number gets converted into a Month enum equivalent
{																//Month(mm) -> the symbolic constant in Month enum that has the value of mm
	if(!is_valid()) throw Invalid{};
}

//DATE FUNCTIONS
bool Date::is_valid()
{
	if(y<0) 								return false;
	if(m < Month::Jan || m > Month::Dec) 	return false;
	if(d<0 || d>31) 						return false;
	
											return true;
}

void Date::add_day(int n)
{
	if(n<0) ("Invalid number of days");
	
	while (n>30)
	{
		n -= 31;			//if n > 30, (because 1+30 can still be 31 but 1+31 is the 1st of the next month) subtract 31 to n and increase the month
		if(m == Month::Dec)		//if m is december, set the month to january and increase the year
		{
			m = Month::Jan;
			y++;
		}
		else
		{
			++m; //We defined the ++ operator for Month enumeration constants
		}		 //IMPORTANT: the syntax is ++m NOT m++. otherwise it won't work
	}
	
	if(d+n > 31)		//if the days to add plus d, exceed 31, then increase the month and assign the remaining days to d
	{
		d = n-(31-d);
		++m;
	}
	else
	{
		d+=n;
	}
}

//OUTPUT
ostream& operator<<(ostream& os, Date& d)
{
	int yy = d.year();
	int mm = int(d.month());
	int dd = d.day();
	return os << '(' << yy << ',' << mm << ',' << dd << ')';
}

//MAIN
int main()
try
{
	Date today {1978,6,25};
	Date tomorrow {today};
	tomorrow.add_day(1);
	
	cout<<today;
	cout<<tomorrow;
	today.add_day(38);
	cout<<today;
	
	return 0;
}
catch (Date::Invalid) {							//catch any exception thrown by the try block
		error("Invalid date");
		return 1;
	}
	
catch (exception& e) {							//catch any exception thrown by the try block
		cerr << "exception: " << e.what() << '\n';
		return 2;
	}
	catch (...) {				//catch unknown exceptions
		cerr << "exception\n";
		return 3;
	}
