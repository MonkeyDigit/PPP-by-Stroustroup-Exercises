#include "std_lib_facilities.h"

int main()
{
	string iname;
	cout<<"Please enter the input file name: ";
	cin >> iname;
	ifstream ifs{iname};
	if(!ifs) error("Couldn't open input file: ",iname);
	
	int sum{};
	for(char ch;ifs>>ch;)
	{
		if(isdigit(ch))
		{
			ifs.unget();
			int n;
			ifs >> n;
			sum+=n;
		}
	}
	
	cout<<"Sum: "<<sum;
	return 0;
}
