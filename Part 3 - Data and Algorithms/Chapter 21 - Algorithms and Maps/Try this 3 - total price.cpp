#include "std_lib_facilities.h"

struct Record{
	double unit_price;
	int units; // number of units sold
	// . . .
};

double price(double v, const Record& r)
{
 return v + r.unit_price * r.units; // calculate price and accumulate
}

int main()
try
{
	vector<Record> vr
	{
		Record{12.50,7},
		Record{20.10,22},
		Record{8.99,41},
		Record{14.50,36}
	};
		
	cout << "Total price: " << accumulate(vr.begin(),vr.end(),0.0,price);
		
	return 0;
}
catch(exception& e)
{
	cerr << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
