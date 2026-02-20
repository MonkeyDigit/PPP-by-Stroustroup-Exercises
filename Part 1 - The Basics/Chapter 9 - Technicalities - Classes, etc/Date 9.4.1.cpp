#include "std_lib_facilities.h"

struct Date {
	int y;
	int m;
	int d;
	
};

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
	
				//in this version, all months have 31 days, and since the maximum you can add to a month before going to the next one is 30 (1+30=31),
	while(n>30) //while n> 30, add 1 month and remove 31 from n each time
	{
		dd.m++;
		n-=31;	
	}
	
	if (dd.d+n > 31)	//and if now n < 30, but when added it has to go to the next month
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

ostream& operator<<(ostream& os, const Date& d)	//operators overloading -> definition of operators (that is, defining what they do with a certain type)
{
 return os << '(' << d.y
 << ',' << d.m
 << ',' << d.d << ')';
}

int main()
{
	Date today;
	init_day(today,1978,6,25);
	//init_day(today,2004,13,-5);
	Date tomorrow = today;
	
	add_day(tomorrow,1);
	cout<<today;
	cout<<tomorrow;
		
	add_day(today,38);
	
	cout<<today;
	
	
	return 0;
}
