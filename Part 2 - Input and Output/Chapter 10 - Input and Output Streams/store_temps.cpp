#include "std_lib_facilities.h"

struct Reading{	//as in, temperature reading (lettura della temperatura)
	int hour;	//hour after midnight [0:23]
	double temperature; //in fahrenheit
	char suffix;
};
/*
//to read the temperature readings from a file, we need to define the cin operator for the Reading struct
istream& operator>>(istream& is, Reading& r)
{
	is >> r.hour >> r.temperature;
	if(!is) return is;
}
*/

int main()
{
	vector<Reading> temps; // store the readings here
	int hour;
	double temperature;
	char suffix;
	cout <<"Enter a reading (for example - 1 65.21 f)\n";
	while (cin >> hour >> temperature >> suffix)
	{
		if(!cin) error("Incorrect reading");
		if (hour < 0 || 23 <hour) error("hour out of range");
		if (suffix != 'c' && suffix != 'f') error("Unknown temperature suffix");
		temps.push_back(Reading{hour,temperature,suffix});
	}
	
	string oname{"raw_temps.txt"};
	ofstream ost {oname};
	if (!ost) error("can't open output file ",oname);
	for(Reading r : temps)
	{
		ost << r.hour << ' ' << r.temperature << ' ' << r.suffix << '\n';
	}
	return 0;
}
