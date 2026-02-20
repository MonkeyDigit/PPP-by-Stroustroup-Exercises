#include "std_lib_facilities.h"

int main()
{
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open file ",iname);
	
	ofstream ofs {"numbers_output.txt"};
	
	for(double d; ifs>>d;)
		ofs << setprecision(8) << scientific << setw(20) << d << '\n';
	
	return 0;
}
	
