#include "std_lib_facilities.h"

int main()
{
	string fname;
	vector<string> words;
	
	cout<<"Please enter the input file name: ";
	cin>>fname;
	ifstream ifs{fname};
	if(!ifs) error("Couldn't open input file ",fname);
	
	for(string s; ifs>>s;)
		words.push_back(s);
		
	ifs.exceptions(ifs.exceptions()|ios_base::badbit);
	if(!ifs) //ist is not good()	NOTE:Operations that attempt to read at the End-of-File fail, and thus both the eofbit and the failbit end up set
	{
		if (ifs.bad()) error("ist is bad");
		if (ifs.eof())
		{
			
		}
		else if (ifs.fail()) error("Fail - wrong type");
	}
	
	ifs.close();
	cout<<"Please enter the input file name: ";
	cin>>fname;
	ifs.open(fname,ios_base::in);
	if(!ifs) error("Couldn't open input file ",fname);
	
	for(string s; ifs>>s;)
		words.push_back(s);
		
	if(!ifs) //ist is not good()	NOTE:Operations that attempt to read at the End-of-File fail, and thus both the eofbit and the failbit end up set
	{
		if (ifs.bad()) error("ist is bad");
		if (ifs.eof())
		{
			
		}
		else if (ifs.fail()) error("Fail - wrong type");
	}
	
	cout<<"Please enter the output file name: ";
	cin>>fname;
	ofstream ofs{fname};
	if(!ofs) error("Couldn't open output file ",fname);
	
	sort(words.begin(), words.end());
	
	for(string& w : words)
		ofs << w << ' ';
	return 0;
}
