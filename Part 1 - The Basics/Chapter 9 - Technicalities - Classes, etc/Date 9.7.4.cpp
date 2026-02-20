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
	class Invalid {};				//The functions below prevent access to private members directly
	int year() const {return y;};	//adding const after the function name lets us invoke non-modifying functions for const objects
	Month month() const {return m;}; //the reason why it's needed is because, when a function is used by a const object (like const Date dd), the
	int day() const {return d;};	//compiler doesn't know if that function changes its Date (that is, dd, when doing for example dd.day())
	void add_day(int n);
private:
	int y;
	Month m;
	int d;
	bool is_valid();	//check if date is valid
};

//DATE CONSTRUCTORS
const Date& default_date()	//the & means that this variable is constructed once
{
 static Date dd {2001,1,1};	//The static local variable is initialized (constructed) only the first time its function is called.
 return dd;
}
//Date::Date() : y(2001), m(Month::Jan), d(1) {}

/*NOTE: As for the constructor below, imagine this: if we have a function int f() that returns, for example, 2, then b = f() + 1; is equal to b = 2 + 1.
Since default_date() returns dd with its members initialized to certain values, when calling default_date() we are essentially using dd */
Date::Date()
:y{default_date().year()},
m{default_date().month()},
d{default_date().day()}
{}

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
ostream& operator<<(ostream& os,const Date& d)
{
	return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
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
