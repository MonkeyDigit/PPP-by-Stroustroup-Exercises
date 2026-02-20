#include "std_lib_facilities.h"
//IMPORTANT: placing ++ left or right of the variable name isn't the same
//for example: ++*p  means add 1 to the value of the object pointed by p
// *p++  means value of p[i+1]
template<class T> class counted_ptr{
	T* obj;
	int* count;
public:
	explicit counted_ptr(T* p): obj{p}, count{new int{1}}
	{
		std::cout << "c_p " << *obj << " constructed\n";
	}
	
	counted_ptr(const counted_ptr&);
	counted_ptr& operator=(const counted_ptr&);
	
	counted_ptr(counted_ptr&&);
	counted_ptr& operator=(counted_ptr&&);
	
	T* object() const { return obj; }
	int use_count() const { return *count; }
	
	~counted_ptr()
	{
		if(count != nullptr)
		{
			--*count;
			std::cout << "c_p " << *obj << " destructor: " << *count
						<< " ptrs left..\n";
			if(*count==0)
			{
				delete obj;
				delete count;
				std::cout << "c_p deleted!\n";
			}
		}
	}
	
	T& operator*() { return *obj; }
    T* operator->() { return obj; }
};

template<class T>
counted_ptr<T>::counted_ptr(const counted_ptr<T>& arg)
	: obj{arg.obj}, count{arg.count}
{
	++*count;
	std::cout << "c_p " << *obj << " copy constructed\n";
}

template<class T>
counted_ptr<T>& counted_ptr<T>::operator=(const counted_ptr<T>& arg)
{
	if (this==&arg) return *this; // self-assignment, no work needed
	--*count;
	obj=arg.obj;
	count=arg.count;
	++*count;
	std::cout << "c_p " << *obj << " copy assigned\n";
	return *this;
}

template<class T>
counted_ptr<T>::counted_ptr(counted_ptr&& arg)
	: obj{arg.obj}, count{arg.count}
{
	arg.obj=nullptr;
	arg.count=nullptr;
	std::cout << "c_p move constructor\n";
}

template<class T>
counted_ptr<T>& counted_ptr<T>::operator=(counted_ptr&& arg)
{
	--*count;
	obj=arg.obj;
	count=arg.count;
	arg.obj=nullptr;
	arg.count=nullptr;
	std::cout << "c_p move assignment\n";
	return *this;
}

counted_ptr<int> f1()
{
	return counted_ptr<int> {new int{4}};
}

int main()
try
{
	//exp constructor
	counted_ptr<int> cp1{new int{1}};
	
	cout<<"--------------------------------\n";
	
	//copy constructor
	counted_ptr<int> cp2{cp1};
	
	cout<<"--------------------------------\n";
	
	//copy assignment
	counted_ptr<int> cp3{new int{3}};
	cp3=cp2;
	
	cout<<"--------------------------------\n";
	
	//move constructor
	counted_ptr<int> cp4{f1()};
	
	cout<<"--------------------------------\n";
	
	//move assignment
	counted_ptr<int> cp5{new int{5}};
	cp5=f1();
	
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
