#include "std_lib_facilities.h"

class File_handle{
	fstream fs;
public:
	File_handle(string file_name)
	{
		fs.open(file_name);
		if(!fs) error("Couldn't open file ",file_name);
		cout<<"file ("<<file_name<<") opened\n";
	}
	
	~File_handle()
	{
		if(fs.is_open())
		{
			cout<<"file closed\n";
			fs.close();
		}
	}
	
};
int main()
try
{
	string fname;
	cout<<"Please enter the file name: ";
	cin>>fname;
	
	File_handle{fname};
	
	return 0;
}
catch(exception& e)
{
	cerr << "Exception: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
