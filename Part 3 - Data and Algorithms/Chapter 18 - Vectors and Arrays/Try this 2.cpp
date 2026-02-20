#include <iostream>
#include <stdexcept>
#include <initializer_list>    
#include <algorithm>
class vector {
	int sz; // the size
	double* elem; // a pointer to the elements
public:
	explicit vector(int s);
	double operator[](int n) { return elem[n]; } // return element
	
	vector(vector&& a); // move constructor
	vector& operator=(vector&&); // move assignment
	~vector() // destructor
 		{ delete[] elem; } // deallocates memory
	
	//vector(const vector&); // copy constructor: define copy
	//vector(std::initializer_list<double> lst);
};

vector::vector(int s) // constructor (s is the element count)
	:sz{s}, elem{new double[sz]} // uninitialized memory for elements
{
	for (int i = 0; i<sz; ++i) elem[i] = 0.0; // initialize
}

/*
vector::vector(std::initializer_list<double> lst) // initializer-list constructor
	:sz{lst.size()}, elem{new double[sz]} // uninitialized memory 
// for elements
{
	std::copy( lst.begin(),lst.end(),elem); // initialize (using std::copy(); §B.5.2)
}

vector:: vector(const vector& arg)
// allocate elements, then initialize them by copying
	:sz{arg.sz}, elem{new double[arg.sz]}
{
	std::copy(arg,arg+sz,elem); // std::copy(); see §B.5.2
}
*/


vector::vector(vector&& a)
	:sz{a.sz}, elem{a.elem} // copy a’s elem and sz
{
	a.sz = 0; // make a the empty vector
	a.elem = nullptr;
}

vector& vector::operator=(vector&& a) // move a to this vector
{
	delete[] elem; // deallocate old space
	elem = a.elem; // copy a’s elem and sz
	sz = a.sz;
	a.elem = nullptr; // make a the empty vector
	a.sz = 0;
	return *this; // return a self-reference (see §17.10)
}

int main()
try
{
	vector v(10);
	double x = v[2]; // fine
	v[3] = x; // error: v[3] is not an lvalue
	return 0;
}

catch(exception& e)
{
	cerr<<"error:"<<e.what()<<'\n';
	keep_window_open();
	return 1;
}

catch(...)
{
	cerr<<"Unknown error"<<'\n';
	keep_window_open();
	return 2;
}
