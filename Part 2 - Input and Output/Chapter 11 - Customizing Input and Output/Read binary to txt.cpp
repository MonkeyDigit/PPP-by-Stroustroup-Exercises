#include "std_lib_facilities.h"

int main()
{
	// open an istream for binary input from a file: 
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname, ios_base::binary}; // note: stream mode
	// binary tells the stream not to try anything clever with the bytes
	if (!ifs) error("can't open file ",iname);
	
	ofstream ofs {"txt_output.txt"};
	vector<char> vc;
	for(char ch; ifs.read(as_bytes(ch),sizeof(char));)
	{
		vc.push_back(ch);
	}
	for(char ch : vc)
		ofs << ch/*.write(as_bytes(ch),sizeof(char))*/;
	
	return 0;
}
