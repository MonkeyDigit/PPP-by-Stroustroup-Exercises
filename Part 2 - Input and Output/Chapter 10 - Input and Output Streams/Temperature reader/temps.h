#pragma once
#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 10 Drills\std_lib_facilities.h"

const int not_a_reading = -7777;
const int not_a_month = -1;

//Types Day,Month,Year---------------------------------------------------------
struct Day {
	vector<double> hour{ vector<double>(24,not_a_reading) };	//this will initialize the elements of hour [0:23] with not_a_reading
};															//(in  each element goes the temperature reading of that hour)

struct Month { // a month of temperature readings
	int month{ not_a_month }; // [0:11] January is 0
	vector<Day> day{ 32 }; // [1:31] one vector of readings per day - day[0] is "wasted" to keep the code simple 
};

struct Year { // a year of temperature readings, organized by month
	int year; // positive == A.D.
	vector<Month> month{ 12 }; // [0:11] January is 0
};

struct Reading {
	int day;
	int hour;
	double temperature;
};

extern vector<string> month_input_tbl; /*= {					//How the month is read
	"jan", "feb", "mar", "apr", "may", "jun", "jul",
	"aug", "sep", "oct", "nov", "dec"
};*/

extern vector<string> month_print_tbl; /*= {					//How the month is written
 "January", "February", "March", "April", "May", "June", "July",
 "August", "September", "October", "November", "December"
};*/

//Helper functions------------------------------------------------------------
//Check if a reading is valid
bool is_valid(const Reading& r);

//Look for the terminator
void end_of_loop(istream& ist, char term, const string& message);

//Convert the month to an int
int month_to_int(string s);

//Convert the int to a month
string int_to_month(int i);

//Prints the readings of year y
void print_year(ostream& ofs, Year y);

//Operator overloading: read a Reading, Month and Year-----------------------

istream& operator>>(istream& is, Reading& r);
istream& operator>>(istream& is, Month& m);
istream& operator>>(istream& is, Year& y);