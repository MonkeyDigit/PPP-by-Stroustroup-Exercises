#include "std_lib_facilities.h"

template<class T> class Unique_ptr{
	T* p;
public:
	explicit Unique_ptr(T* val): p{val} { }
	T* release()
	{
		T* q=p;
		p=nullptr;
		return q;
	}
	
	~Unique_ptr() { delete p; }
	T& operator*() const { return *p; }
};

unique_ptr<int> f1(int n)
{
    unique_ptr<int> p {new int{n}};
    return p;
}

double* f2(double n)
{
    unique_ptr<double> p {new double{n}};
    return p.release();
}

int main()
try
{
	std::cout << "Start of main\n";

    unique_ptr<int> p1 = f1(11);

    std::cout << "Pointer contents: " << *p1 << '\n';

    //throw std::runtime_error("Was u_p destructed?");

    double* p2 = f2(2.71828);

    std::cout << "Pointer contents: " << *p2 << '\n';
    delete p2;
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
