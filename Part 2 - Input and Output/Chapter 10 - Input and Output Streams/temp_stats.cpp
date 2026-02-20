#include "std_lib_facilities.h"

struct Reading{
	int hour;
	double temperature;
	char suffix;
};
int main()
{
	string iname {"raw_temps.txt"};
	ifstream ist {iname};
	if (!ist) error("Couldn't open file ",iname);
	
	double sum {};
	double mean {};
	double median {};
	
	vector<Reading> temps_vect;	//will store the readings from raw_temps.txt
	int hour {};
	double temperature {};
	char suffix {};
	while (ist>>hour>>temperature>>suffix) 
	{
		//added with the suffix - convert celsius to fahrenheit
		if(suffix == 'c')
		{
			temperature = temperature*9/5+32;
			suffix = 'f';
		}
		else if(suffix != 'f') error("Unknown temperature suffix");
		temps_vect.push_back(Reading{hour,temperature,suffix});
		sum+=temperature;
	}
	
	for(Reading r : temps_vect)
		cout << r.hour << ' ' << r.temperature << ' ' << r.suffix << '\n';
	// make ist throw if it goes bad
	ist.exceptions(ist.exceptions()|ios_base::badbit);
	if(!ist) //ist is not good()	NOTE:Operations that attempt to read at the End-of-File fail, and thus both the eofbit and the failbit end up set
	{
		if (ist.bad()) error("ist is bad");
		if (ist.eof())
		{
			
		}
		else if (ist.fail()) error("Fail - wrong type");
	}
	
	//MEAN
	mean = sum/temps_vect.size();
	
	//MEDIAN
	//first we need to make a sorted copy of the temperatures
	vector<double> copy_temps_vect;
	for(Reading r : temps_vect)
		copy_temps_vect.push_back(r.temperature);
	sort(copy_temps_vect.begin(), copy_temps_vect.end());
	
	//then we check if the size is odd or even
	if(copy_temps_vect.size() % 2 == 0)
		median = (copy_temps_vect[copy_temps_vect.size()/2 - 1] + copy_temps_vect[copy_temps_vect.size()/2]) / 2;
	else
		median = copy_temps_vect[copy_temps_vect.size()/2];
		
	cout<<"Mean: "<<mean<<'\n';
	cout<<"Median: "<<median<<'\n';
	return 0;
}
