#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 10 Drills\std_lib_facilities.h"
#include "temps.h"

int main()
{
	// open an input file:
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs{ iname };
	if (!ifs) error("can't open input file", iname);
	ifs.exceptions(ifs.exceptions() | ios_base::badbit); // throw for bad()

	// open an output file:
	cout << "Please enter output file name\n";
	string oname;
	cin >> oname;
	ofstream ofs{ oname };
	if (!ofs) error("can't open output file", oname);

	//---------------------------------------------------------------------
	// read an arbitrary number of years:
	vector<Year> ys;
	while (true) {
		Year y; // get a freshly initialized Year each time around
		if (!(ifs >> y)) break;
		ys.push_back(y);
	}

	cout << "read " << ys.size() << " years of readings\n";
	for (Year& y : ys) print_year(ofs, y);
	
	return 0;
}