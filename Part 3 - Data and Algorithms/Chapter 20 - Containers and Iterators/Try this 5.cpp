#include "std_lib_facilities.h"

template<class T>
class my_vector{
	int sz;
	int space;
	T* elem;
public:
		//constructors
	my_vector() : sz{0}, elem{nullptr}, space{0} { }
	
	explicit my_vector(int s): sz{s}, elem{new T[s]}, space{s} 
	{
		for(int i=0;i<sz;++i) elem[i] = T{};
	}
	
	my_vector(const my_vector&);				//copy constructor
	my_vector& operator=(const my_vector&); 	//copy assignment
	
	my_vector(my_vector&&);						//move constructor
	my_vector& operator=(my_vector&&);			//move assignment
	
	~my_vector()								//destructor
	{
		delete[] elem;
	}
	
	T& operator[] (int n) { return elem[n]; }	//access: return reference
	const T& operator[] (int n) const { return elem[n]; }
	
	T& at(int n);								//checked access
	const T& at(int n) const;
	
	int size() const { return sz; }				//the current size
	int capacity() const { return space; }
	
	void resize(int newsize, T val = T{});		//growth
	void push_back(const T& t);
	void push_front(const T& t);
	void reserve(int newalloc);
};

template<class T>
void my_vector<T>::push_front(const T& t)
{
	if(space==0) reserve(8);				//start with space for 8 elements
	else if(sz==space) reserve(2*space);	//get more space
	
	for(int i=sz;i>0;--i)
		elem[i]=elem[i-1];
	
	*elem=t;
	sz++;
}

//all other vector functions are defined after main
int main()
try
{
	my_vector<int> v1;
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);
	
	cout << "v1 - size(): " << v1.size() << " capacity(): " << v1.capacity() << "\n";
	for(int i=0;i<v1.size();++i)
		cout << v1[i] << '\n';
		
	v1.push_front(0);
	
	cout << "v1 - size(): " << v1.size() << " capacity(): " << v1.capacity() << "\n";
	for(int i=0;i<v1.size();++i)
		cout << v1[i] << '\n';
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

template<class T>
my_vector<T>::my_vector(const my_vector& arg)
	: sz{arg.sz}, elem{new T[arg.sz]}, space{arg.sz}
{
	for(int i=0; i<sz;++i)
		elem[i]=arg[i];
}

template<class T>
my_vector<T>& my_vector<T>::operator=(const my_vector& arg)
{
	if (this==&arg) return *this; // self-assignment, no work needed
	
	if(arg.sz<=space)	// enough space, no need for new allocation
	{
		for(int i=0;i<arg.sz;++i)
			elem[i]=arg[i];
		sz = arg.sz;
		return *this;
	}
		
	T* p = new T[arg.sz];
	for(int i=0;i<arg.sz;++i)		//copy elements
			p[i]=arg[i];
			
	delete[] elem;
	
	space = sz = arg.sz;
	elem = p;
	return *this;
}

template<class T>
my_vector<T>::my_vector(my_vector&& arg)
	: sz{arg.sz}, elem{arg.elem}, space{arg.sz}
{
	arg.sz=0;
	arg.space=0;
	arg.elem=nullptr;
}

template<class T>
my_vector<T>& my_vector<T>::operator=(my_vector&& arg)
{
	delete[] elem;
	
	elem=arg.elem;
	sz=arg.sz;
	space=arg.space;
	arg.sz=0;
	arg.space=0;
	arg.elem=nullptr;
	return *this;
}

template<class T>
T& my_vector<T>::at(int n)
{
	if (n<0 || sz<=n) throw Range_error(n);
    return elem[n];
}

template<class T>
const T& my_vector<T>::at(int n) const
{
	if (n<0 || sz<=n) throw Range_error(n);
    return elem[n];
}

template<class T>
void my_vector<T>::reserve(int newalloc)
{
	if(newalloc<=space) return;
	
	T* p= new T[newalloc];
	for(int i=0;i<sz;++i)
		p[i]=elem[i];
	
	delete[] elem;
	
	elem=p;
	space=newalloc;
}

template<class T>
void my_vector<T>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i = sz; i<newsize; ++i)    // construct
        elem[i]=val;
	sz=newsize;
}

template<class T>
void my_vector<T>::push_back(const T& t)
{
	if(space==0) reserve(8);				//start with space for 8 elements
	else if(sz==space) reserve(2*space);	//get more space
	
	elem[sz]=t;
	sz++;									//increase the size
}

