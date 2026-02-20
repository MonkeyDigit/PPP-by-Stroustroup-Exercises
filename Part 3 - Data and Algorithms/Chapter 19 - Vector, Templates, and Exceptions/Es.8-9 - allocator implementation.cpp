#include "std_lib_facilities.h"
//fix string not working
//allocator-----------------------------------------------------------------------
template<typename T> class Allocator{
public:
	T* allocate(int n); // allocate space for n objects of type T
	void deallocate(T* p); // deallocate p
	void construct(T* p, const T& v); // construct a T with the value v in p
	void destroy(T* p); // destroy the T in p
};

template<typename T>
T* Allocator<T>::allocate(int n)
{
	T* p = static_cast<T*>(malloc(n*sizeof(T)));
	return p;
}

template<typename T>
void Allocator<T>::deallocate(T* p)
{
	free(p);
}

template<typename T>
void Allocator<T>::construct(T* p, const T& v) // placement new
{
	new (p) T{v};
}

template<typename T>
void Allocator<T>::destroy(T* p)
{
	p->~T();
	//cout<<"destructor called\n";
}

//vector -------------------------------------------------------------------
template<typename T, typename A=Allocator<T>> class my_vector{
	A alloc;
	int sz;
	T* elem;
	int space;
public:
	//constructors
	my_vector() : sz{0}, elem{nullptr}, space{0} { }
	
	explicit my_vector(int s): sz{s}, elem{alloc.allocate(s)}, space{s} 
	{
		for(int i=0;i<sz;++i) alloc.construct(&elem[i],T());
	}
	
	my_vector(const my_vector&);				//copy constructor
	my_vector& operator=(const my_vector&); 	//copy assignment
	
	my_vector(my_vector&&);						//move constructor
	my_vector& operator=(my_vector&&);			//move assignment
	
	~my_vector();								//destructor
	
	T& operator[] (int n) { return elem[n]; }	//access: return reference
	const T& operator[] (int n) const { return elem[n]; }
	
	T& at(int n);								//checked access
	const T& at(int n) const;
	
	int size() const { return sz; }				//the current size
	int capacity() const { return space; }
	
	void resize(int newsize, T val = T());		//growth
	void push_back(const T& t);
	void reserve(int newalloc);
};

//copy constructor
template<typename T, typename A> 
my_vector<T,A>::my_vector(const my_vector<T,A>& arg)	//we can access arg private members
	: sz{arg.sz}, elem{alloc.allocate(arg.sz)}, space{arg.sz}
{
	for(int i=0; i<sz;++i)
		alloc.construct(&elem[i], arg[i]);
}

//copy assignment
template<typename T, typename A>
my_vector<T,A>& my_vector<T,A>::operator=(const my_vector<T,A>& arg)
{
	if (this==&arg) return *this; // self-assignment, no work needed
	
	if(arg.sz<=space)	// enough space, no need for new allocation
	{
		for(int i=0;i<arg.sz;++i)
			alloc.construct(&elem[i], arg[i]);
		sz = arg.sz;
		return *this;
	}
		
	T* p = alloc.allocate(arg.sz);	//allocate new space
	for(int i=0;i<arg.sz;++i)		//copy elements
			alloc.construct(&p[i], arg[i]);
			
	for(int i=0;i<sz;++i)			//destroy old objects
		alloc.destroy(&elem[i]);
	
	alloc.deallocate(elem);			//deallocate old space
	
	space = sz = arg.sz;
	elem = p;
	return *this;
}

//move constructor
template<typename T, typename A>
my_vector<T,A>::my_vector(my_vector&& arg)
	: sz{arg.sz}, elem{arg.elem}, space{arg.sz}
{
	arg.sz=0;
	arg.space=0;
	arg.elem=nullptr;
}

//move assignment
template<typename T, typename A>
my_vector<T,A>& my_vector<T,A>::operator=(my_vector&& arg)
{
	alloc.destroy(elem);
	alloc.deallocate(elem);
	
	elem=arg.elem;
	sz=arg.sz;
	arg.sz=0;
	arg.space=0;
	arg.elem=nullptr;
	return *this;
}

//destructor
template<typename T, typename A>
my_vector<T,A>::~my_vector()
{
	for (int i = 0; i<sz; ++i)
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem);
}

//checked access
template<class T, class A>
T& my_vector<T,A>::at(int n)
{
	if (n<0 || sz<=n) throw Range_error(n);
    return elem[n];
}

template<class T, class A>
const T& my_vector<T,A>::at(int n) const
{
	if (n<0 || sz<=n) throw Range_error(n);
    return elem[n];
}

template<typename T, typename A>
void my_vector<T,A>::reserve(int newalloc)
{
	if(newalloc<=space) return;
	
	T* p=alloc.allocate(newalloc);
	for(int i=0;i<sz;++i)
		alloc.construct(&p[i], elem[i]);
	
	for(int i=0;i<sz;++i)	
		alloc.destroy(&elem[i]);
		
	alloc.deallocate(elem);
	elem=p;
	space=newalloc;
}

template<typename T, typename A>
void my_vector<T,A>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i = sz; i<newsize; ++i)    // construct
        alloc.construct(&elem[i],val);
	sz=newsize;
}

template<typename T, typename A>
void my_vector<T,A>::push_back(const T& val)
{
	if(space==0) reserve(8);				//start with space for 8 elements
	else if(sz==space) reserve(2*space);	//get more space
	
	alloc.construct(&elem[sz],val);			//add val at the end
	sz++;									//increase the size
}

//test functions
my_vector<int> move_vec()
{
	my_vector<int> vv;
	vv.push_back(1);
	vv.push_back(2);
	vv.push_back(3);
	return vv;
}

//main ----------------------------------------------------------------
int main()
try
{
	//default constructor
	my_vector<int> v1;
	my_vector<char> v2;
	
	//constructor with size
	my_vector<double> v3(5);
	cout << "v3.size(): " << v3.size() << "\nv3.capacity(): " << v3.capacity() << '\n';
	cout << "--------------------------------\n";
	
	//copy constructor
	my_vector<double> v4=v3;
	
	//copy assignment + push_back()	
	/*
	my_vector<int> v5;
	
	v5.push_back(1);
	v5.push_back(2);
	
	for(int i=0;i<v5.size();++i) cout << v5[i] <<'\n';
	
	my_vector<string> v6;
	v6.push_back("pointers");
	v6.push_back("are complex");
	/*
	v5=v6;
	for(int i=0;i<v5.size();++i) cout << v5[i] <<'\n';
	cout << "--------------------------------\n";
	*/
	
	//move constructor
	my_vector<int> v7=move_vec();
	cout << "v7.size(): " << v7.size() << "\nv7.capacity(): " << v7.capacity() << '\n';
	for(int i=0;i<v7.size();++i) cout << v7[i] <<'\n';
	cout << "--------------------------------\n";
	
	//move assignment + destructor (i put a test output in it)
	my_vector<int> v8;
	v8.push_back(5);
	v8.push_back(6);
	v8.push_back(7);
	
	cout << "v8.size(): " << v8.size() << "\nv8.capacity(): " << v8.capacity() << '\n';
	for(int i=0;i<v8.size();++i) cout << v8[i] <<'\n';
	
	v8=move_vec();
	
	cout << "v8.size(): " << v8.size() << "\nv8.capacity(): " << v8.capacity() << '\n';
	for(int i=0;i<v8.size();++i) cout << v8[i] <<'\n';
	cout << "--------------------------------\n";
	
	//at() access
	/*
	cout << v8.at(2)<<'\n';
	//cout << v8.at(3)<<'\n'; will throw an error
	*/
	
	//[] access
	cout << v8[2]<<'\n';
	cout << "Unchecked access v8[3]: " << v8[3]<<'\n';
	cout << "--------------------------------\n";
	
	//resize()
	v8.resize(5,0);
	cout << "v8.size(): " << v8.size() << "\nv8.capacity(): " << v8.capacity() << '\n';
	cout << "--------------------------------\n";
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
