#include "std_lib_facilities.h"

struct Date {
	int y, m, d; 				// year, month, day 
	Date(int yy, int mm, int dd);  // check for valid date and initialize - the compiler will throw an error 
									//if a class with a constructor is initialized without using it
	void add_day(int n); 		// increase the Date by n days
};

Date::Date(int yy,int mm,int dd) : y(yy), m(mm), d(dd)
{
	if(m<1 || m>12) error("Invalid month");
	if(d<1 || d>31) error("Invalid day");
}

void Date::add_day(int n)
{
	if(n<0) error("Invalid number of days");
	
	while (n>30)
	{
		n-=31;			//if n > 30, (because 1+30 can still be 31 but 1+31 is the 1st of the next month) subtract 31 to n and increase the month
		if(m == 12)		//if m is december, set the month to january and increase the year
		{
			m=1;
			y++;
		}
		else
		{
		m++;
		}
	}
	
	if(d+n > 31)		//if the days to add plus d, exceed 31, then increase the month and assign the remaining days to d
	{
		d = n-(31-d);
		m++;
	}
	else
	{
		d+=n;
	}
}
/*
// helper functions:
void init_day(Date& dd, int y, int m, int d)
{
 // check that (y,m,d) is a valid date
 // if it is, use it to initialize dd
 if(m<1 || m>12) error("Invalid month");
 if(d<1 || d>31) error("invalid day");
 
 dd.y=y;
 dd.m=m;
 dd.d=d;
}
void add_day(Date& dd,int n)
{
	if(n<0) error("Invalid number of days");
	
	if(n>30)
	{
		while(n>30)
		{
			dd.m++;
			n-=31;	
		}
	}
	
	if (dd.d+n > 31)
	{
		dd.m++;
		dd.d = n-(31-dd.d);
	}
	else
	{
		dd.d+=n;
	}
	
	if(dd.m > 12) error ("Invalid number of days");
}
*/

ostream& operator<<(ostream& os, const Date& d)
{
 return os << '(' << d.y
 << ',' << d.m
 << ',' << d.d << ')';
}

int main()
{
	//Date today; 			this won't compile because a constructor that takes arguments is defined. To resolve this we must use the constructor
							//with normal or curly brackets
	Date today{1978,6,25};
	//Date today{1978,13,-5};
	//init_day(today,1978,6,25);
	//init_day(today,2004,13,-5);
	Date tomorrow = today;
	tomorrow.add_day(1);
	//add_day(tomorrow,1);
	cout<<today;
	cout<<tomorrow;
	
	today.add_day(38);	
	//add_day(today,38);
	
	cout<<today;
	
	return 0;
}
