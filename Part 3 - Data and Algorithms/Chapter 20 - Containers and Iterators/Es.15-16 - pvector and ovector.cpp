#include "std_lib_facilities.h"
template<class Elem>
class pvector{
	vector<Elem*> elems;
public:
	pvector() : elems{} { }
	
	explicit pvector(int s): elems{vector<Elem*>(s)}{ }
	
	pvector(const pvector&);				//copy constructor
	pvector& operator=(const pvector&); 	//copy assignment
	
	pvector(pvector&&);						//move constructor
	pvector& operator=(pvector&&);			//move assignment
	
	~pvector()								//destructor
	{
		for(Elem* p : elems)
		{
			delete p;
		}
	}
	
	Elem* operator[] (int n) { return elems[n]; }	//access: return reference
	const Elem* operator[] (int n) const { return elems[n]; }
	
	Elem* at(int n);								//checked access
	const Elem* at(int n) const;
	
	int size() const { return elems.size(); }				//the current size
	int capacity() const { return elems.capacity(); }
	
	void resize(int newsize, Elem val = Elem{});		//growth
	void push_back(const Elem& t);
	void reserve(int newalloc);
};

template<typename Elem>
pvector<Elem>::pvector(const pvector<Elem>& arg)			//copy constructor
{
	pvector n = new pvector<Elem>{pvector<Elem>(arg.size())};
	
	for(const Elem& p : arg)
	{
		n.push_back(new Elem (*p));
	}
}

template<typename Elem>
pvector<Elem>& pvector<Elem>::operator=(const pvector& arg)		//copy assignment
{
	if (this==&arg) return *this; // self-assignment, no work needed
	if(arg.size()<=elems.capacity())
	{
		for(int i=0;i<arg.size();++i)
			elems[i] = new Elem ((*arg)[i]);
		elems.sz=arg.size();
		return *this;
	}
	
	vector<Elem*> n;
	for(int i=0;i<arg.size();++i)
			n.push_back(new Elem {(*arg)[i]});
	
	~pvector();
	elems=n;
	
	return *this;
}

template<typename Elem>
pvector<Elem>::pvector(pvector&& arg)					//move constructor
: elems{arg.elems}
{
	arg.elems=vector<Elem*>{};
}

template<typename Elem>
pvector<Elem>& pvector<Elem>::operator=(pvector&& arg)		//move assignment
{
	~pvector();
	
	elems=arg.elems;
	arg.elems=vector<Elem*>{};
	return *this;
}

template<typename Elem>
Elem* pvector<Elem>::at(int n)							//checked access
{
	return elems.at(n);
}

template<typename Elem>
const Elem* pvector<Elem>::at(int n) const
{
	return elems.at(n);
}

template<typename Elem>
void pvector<Elem>::resize(int newsize, Elem val)		//growth
{
	elems.resize(newsize,val);
}

template<typename Elem>
void pvector<Elem>::push_back(const Elem& t)
{
	elems.push_back(new Elem{t});
}

template<typename Elem>
void pvector<Elem>::reserve(int newalloc)
{
	if(newalloc<=elems.capacity()) return;
	
	vector<Elem*> n(newalloc);
	
	for(int i=0;i<elems.size();++i)
		n[i]=elems[i];
	
	~pvector();
	elems=n;
}

template<typename Elem>
class ovector : public pvector<Elem>{
	Elem& operator[](int i) { return *pvector<Elem>::operator[](i); }
    const Elem& operator[](int i) const { return *pvector<Elem>::operator[](i); }
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

