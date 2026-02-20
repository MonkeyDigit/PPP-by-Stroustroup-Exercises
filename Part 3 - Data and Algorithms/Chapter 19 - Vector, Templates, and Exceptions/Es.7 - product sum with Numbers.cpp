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

template<typename T, typename U>
Number<T> operator+(const Number<T>& a, const Number<U>& b) { return a.get() + b.get(); }

template<typename T, typename U>
Number<T> operator-(const Number<T>& a, const Number<U>& b) { return a.get() - b.get(); }

template<typename T, typename U>
Number<T> operator*(const Number<T>& a, const Number<U>& b) { return a.get() * b.get(); }

template<typename T, typename U>
Number<T> operator/(const Number<T>& a, const Number<U>& b) { return a.get() / b.get(); }

template<typename T, typename U>
Number<T> operator%(const Number<T>& a, const Number<U>& b) { return int(a.get()) % int(b.get()); }

template<typename T, typename U>
void operator+=(Number<T>& a, const Number<U>& b) { a = a + b; }

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

template<typename T, typename U>
T product_sum(const vector<T>& vt, const vector<U> vu)
{
	if(vt.size() != vu.size()) error("Different vector sizes");
	
	T sum {0};
	for(int i=0;i<vt.size();++i)
	{
		sum += vt[i]*vu[i];
	}
	
	return sum;
}

int main()
try
{
	vector<Number<int>> vi {2,3,4};
	vector<Number<double>> vd {1.5,1.1,2.5};
	
	cout << "vi: {";
	for(const Number<int>& n : vi)
		cout << n << ", ";
	cout << "}\n";
	
	cout << "vd: {";
	for(const Number<double>& n : vd)
		cout << n << ", ";
	cout << "}\n";
	
	cout << "product_sum(vi,vd): " << product_sum(vi,vd)<<'\n';
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
