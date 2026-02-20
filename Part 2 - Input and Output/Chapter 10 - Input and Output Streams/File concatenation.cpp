#include "std_lib_facilities.h"
/*NOTE:
ifstream - input file stream
ofstream - output file stream
fstream  - input/output file stream, can be used for both
*/
int main()
{
	vector<string> content;
	string iname;
	cout<<"Please enter input file name: ";
	cin>>iname;
	ifstream ifs{iname};
	if(!ifs) error("Couldn't open input file ", iname);
	
	for(string sf;ifs>>sf;)
		content.push_back(sf);
	
	ifs.close();
	cout<<"Please enter the second input file name: ";
	cin>>iname;
	ifs.open(iname,ios_base::in);
	if(!ifs) error("Couldn't open input file ", iname);
	
	for(string sf;ifs>>sf;)
		content.push_back(sf);
	
	cout<<"Please enter output file name: ";
	string oname;
	cin >> oname;
	ofstream ofs{oname};
	if(!ofs) error("Couldn't open output file ", oname);
	
	for(string& s : content)
	{
		ofs << s << ' ';
	}
	return 0;
}
