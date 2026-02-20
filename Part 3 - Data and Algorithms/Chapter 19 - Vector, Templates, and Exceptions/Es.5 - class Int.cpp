#include "std_lib_facilities.h"

class Int{
public:
	//constructors
	Int(): val{0} { }
	Int(int val): val{val} { }
	
	//get and set value
	int get() const { return val; }
	Int& operator=(const int& v) { val=v; return *this; }
private:
	int val;
};

int operator+(const Int& a, const Int& b) {return a.get() + b.get();}
int operator-(const Int& a, const Int& b) {return a.get() - b.get();}
int operator*(const Int& a, const Int& b) {return a.get() * b.get();}
int operator/(const Int& a, const Int& b) {return a.get() / b.get();}

istream& operator>>(istream& is, Int& val)
{
	int v;
	is>>v;
	val=v;;
	return is;
}

ostream& operator<<(ostream& os, const Int& val)
{
	return os << val.get();
}

int main()
try
{
	Int a;
	cout << "a = " << a << '\n';
	
	a = 10;
	cout << "a = " << a << '\n';
	
	Int b{3};
	cout << "b = " << b << '\n';
	
	cout << "a + b = " << a + b << '\n';
	cout << "a - b = " << a - b << '\n';
	cout << "a * b = " << a * b << '\n';
	cout << "a / b = " << a / b << '\n';
	
	a = b;
	cout << "a = b: " << a << '\n';
	a = b + 6;
	cout << "a = b + 6: " << a << '\n';
	
	Int c;
	cout << "Enter an integer: ";
	cin>>c;
	
	cout << "You entered " << c << '\n';
	
	return 0;
}
catch(exception& e)
{
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown error\n";
	keep_window_open();
	return 2;
}
