#include "std_lib_facilities.h"

class Tracer{
	string clab;
	string dlab;
public:
	Tracer(string clabel, string dlabel): clab{clabel}, dlab{dlabel}
	{
		cout << clab << '\n';
	}
	
	Tracer(const Tracer& a): clab{a.clab}, dlab{a.dlab}
	{
		cout << "In copy constructor\n";
	}
	
	Tracer& operator=(const Tracer& a)
	{
		clab=a.clab;
		dlab=a.dlab;
		cout << "In copy assignment\n";
	}
	
	~Tracer()
	{
		cout << dlab << '\n';
	}
};

void f1()
{
	Tracer t{"in f1 t constructor", "in f1 t destructor"};
}

const Tracer t0{"Global t0 constructor", "Global t0 destructor"};

int main()
try
{
	Tracer t1{"inside main t1 constructor", "inside main t1 destructor"};
	f1();
	Tracer* tracer_ptr1{new Tracer{"tracer_ptr1 constructor", "tracer_ptr1 destructor"}};
	Tracer t2{t1};
	Tracer t3{"inside main t3 constructor", "inside main t3 destructor"};
	Tracer t4{"inside main t4 constructor", "inside main t4 destructor"};	
	t4=t3;
	delete tracer_ptr1;	//by doing this the destructor label is printed
	
	return 0;
}
catch(exception& e)
{
	cerr << "Exception: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
