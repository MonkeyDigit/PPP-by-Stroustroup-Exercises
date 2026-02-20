#include "std_lib_facilities.h"

template<typename T>
class Number{
public:
	Number(): val{0} { }
	Number(T val): val{val} { }
	
	T get() const { return val; }
	Number& operator=(const T& v) { val=v; return *this; }
private:
	T val;
};

//overloading the operators +, -, *, /, %, >>, and <<
template<typename T, typename U>
T operator+(const Number<T>& a, const Number<U>& b) { return a.get() + b.get(); }

template<typename T, typename U>
T operator-(const Number<T>& a, const Number<U>& b) { return a.get() - b.get(); }

template<typename T, typename U>
T operator*(const Number<T>& a, const Number<U>& b) { return a.get() * b.get(); }

template<typename T, typename U>
T operator/(const Number<T>& a, const Number<U>& b) { return a.get() / b.get(); }

template<typename T, typename U>
T operator%(const Number<T>& a, const Number<U>& b) { return int(a.get()) % int(b.get()); }

template<typename T>
istream& operator>>(istream& is, Number<T>& num)
{
	T val;
	cin>>val;
	num=val;
	return is;
}

template<typename T>
ostream& operator<<(ostream& os, const Number<T>& num)
{
	return os << num.get();
}

int main()
try
{
	Number<int> x {5};
	Number<double> y = 2.5;
	
	cout << "x: " << x << '\n';
	cout << "y: " << y << '\n';
	
	cout << "x + y = " << x + y << '\n';
	cout << "x - y = " << x - y << '\n';
	cout << "x * y = " << x * y << '\n';
	cout << "x / y = " << x / y << '\n';
	cout << "x % y = " << x % y << '\n';	//would have given a compiler error had we not define % to make a conversion to int
	
	Number<double> z;
	
	cout << "Enter a number (double): ";
	cin>>z;
	
	cout << "You entered " << z << '\n'; 
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
