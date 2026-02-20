#include "std_lib_facilities.h"

template<class Elem>
class ownership_vector{
	vector<Elem*> elems;
	vector<Elem*> owned;
public:
	ownership_vector() : elems{}, owned{} { }
	
	//pvector(const pvector&);				//copy constructor
	//pvector& operator=(const pvector&); 	//copy assignment
	
	~ownership_vector()								//destructor
	{
		for(Elem* p : owned)
		{
			delete p;
		}
	}
	
	Elem* operator[] (int n) { return elems[n]; }	//access: return reference
	const Elem* operator[] (int n) const { return elems[n]; }
	
	int size() const { return elems.size(); }				//the current size
	
	void push_back(Elem* d) { elems.push_back(d); owned.push_back(d); }
    void push_back(Elem& d) { elems.push_back(&d); }
};

int main()
try
{
	
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
