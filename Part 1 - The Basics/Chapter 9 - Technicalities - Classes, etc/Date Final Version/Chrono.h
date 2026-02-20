#pragma once
// file Chrono.h - Here go the declarations
#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 9 Drills\std_lib_facilities.h"
namespace Chrono {
	enum class Month {				//Symbolic constants for the months
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date {
	public:
		class Invalid { }; // to throw as exception
		Date(int yy, int mm, int dd); // check for valid date and initialize
		Date(); // default constructor
		// the default copy operations are fine
		// nonmodifying operations:				(check 9.7.4 version for further explanations)
		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }
		int month_days() const;
		// modifying operations:
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);
	private:
		int y;
		Month m;
		int d;
	};
	//Helper functions
	//int month_days (Month m);
	bool is_date(int y, Month m, int d); // true for valid date
	bool leapyear(int y); // true if y is a leap year
	//Operator overloading
	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);
	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& dd);

	//day enumerator--------------------------------------------------------------------------------
	enum class Day {
		sunday=1, monday, tuesday, wednesday, thursday, friday, saturday
	};

	Day day_of_week(const Date& d);
	/*

	Date next_Sunday(const Date& d)
	{
		// ...
	}
	Date next_weekday(const Date& d)
	{
		// . . .
	}
	*/
} // Chrono