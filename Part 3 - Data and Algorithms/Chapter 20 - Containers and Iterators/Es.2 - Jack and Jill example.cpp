#include "std_lib_facilities.h"

double* get_from_jack(int* count)
{
	cout << "Please enter Jack's input file name: ";
	string iname;
	cin >> iname;
	ifstream ifs{iname};
	
	if(!ifs) error("Couldn't open input file",iname);
	
	vector<double> v;
	for(double d;ifs>>d;)
		v.push_back(d);
		
	*count=v.size();
	double* data = new double[*count];	//IMPORTANT: For Jack and also Jill's input functions, we must make and return a pointer. 
	for(int i=0;i<v.size();++i)			//making a container and returning its address doesn't guarantee it won't get deallocated, and most if the
		data[i]=v[i];					//times it will cause errors.
	
	return data;
}

vector<double>* get_from_jill()
{
	cout << "Please enter Jill's input file name: ";
	string iname;
	cin >> iname;
	ifstream ifs{iname};
	
	if(!ifs) error("Couldn't open input file",iname);
	
	vector<double>* data = new vector<double>;
	for(double d;ifs>>d;)
		(*data).push_back(d);
		
	return data;
}

double* high(double* first, double* last)
// return a pointer to the element in [first,last) that has the highest value
{
	double h = -1;
	double* high;
	for(double* p = first; p!=last; ++p)
	if (h<*p) { high = p; h = *p; }
	return high;
}

void fct()
{
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();
	
	double* jack_high = high(jack_data,jack_data+jack_count);
	
	vector<double>& v = *jill_data;
	
	double* jill_high = high(&v[0],&v[0]+v.size());
	
	cout << "Jill's max: " << *jill_high
		<< "; Jack's max: " << *jack_high;
	
	delete[] jack_data;
	delete jill_data;
}

int main()
try
{
	fct();
	return 0;
}
catch(exception & e)
{
	cerr<< "Exception: " << e.what() <<'\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
