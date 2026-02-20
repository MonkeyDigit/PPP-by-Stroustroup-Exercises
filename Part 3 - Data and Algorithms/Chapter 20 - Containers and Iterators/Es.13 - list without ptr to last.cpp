#include "std_lib_facilities.h"

template<class T>
struct Link{
	T val;
	Link* prev;
	Link* succ;
	
	Link(): val{T()}, prev{nullptr}, succ{nullptr} { }
	Link(const T& val, Link* prev=nullptr, Link* succ=nullptr): val{val}, prev{prev}, succ{succ} { }
};

template<typename Elem>
class my_list {
	// representation and implementation details
	Link<Elem>* first;
public:
	my_list(): first{new Link<Elem> {}} { }
	
	class iterator; // member type: iterator
	iterator begin() // iterator to first element
	{ return first; }
	
	iterator end()// iterator to one beyond last element
	{ return iterator{nullptr}; }
	
	iterator insert(iterator p, const Elem& v) // insert v into list after p
	{
		Link<Elem>* n=new Link<Elem> {v,p,p->succ};
		p->succ->prev=n;
		p->succ=n;
		return n;
	}
	
	iterator erase(iterator p) // remove p from the list
	{
		p->prev->succ=p->succ;
		p->succ->prev=p->prev;
		
		p->prev=nullptr;
		p->succ=nullptr;
		
		return p;
	}
	
	void push_back(const Elem& v) // insert v at end
	{
		Link<Elem>* n=new Link<Elem> {v};
		if(!first)
		{
			first=n;
			return;
		}
		
		iterator it=first;
		while(it->succ) ++it;
		
		it->succ=n;
		n->prev=it.ptr();
	}
	
	void push_front(const Elem& v) // insert v at front
	{
		Link<Elem>* n=new Link<Elem> {v,0,first};
		first->prev=n;
		first=n;
	}
	
	void pop_front() // remove the first element
	{
		if(!first) return;
		first=first->succ;
		first->prev->prev=nullptr;//this isn't needed in theory
		first->prev->succ=nullptr;
	}
	
	void pop_back() // remove the last element
	{
		if(!first) return;
		
		iterator it=first;
		while(!it->succ) ++it;
		
		it->prev->succ=it->succ;
		it->succ->prev=it->prev;
		it->prev=nullptr;
		it->succ=nullptr;
	}
	
	Elem& front() // the first element
	{
		return first->val;
	}
	
	Elem& back() // the last element
	{
		iterator it=first;
		while(!it->succ) ++it;
		return *it;
	}
	
	~my_list()
    {
        while (first != nullptr)
		{
            auto p = first->succ;
            delete first;
            first = p;
        }
    }
};

template<typename Elem> // requires Element<Elem>() (§19.3.3)
class my_list<Elem>::iterator {
 Link<Elem>* curr; // current link
public:
	iterator(Link<Elem>* p) :curr{p} { }
	iterator& operator++() {curr = curr->succ; return *this; } // forward
	iterator& operator--() { curr = curr->prev; return *this; } // backward
	Elem& operator*() { return curr->val; } // get value (dereference)
	bool operator==(const iterator& b) const { return curr==b.curr; }
	bool operator!= (const iterator& b) const { return curr!=b.curr; }
	Link<Elem>* operator->() { return curr; }
    Link<Elem>* ptr() const { return curr; }
};

template<typename Iterator>
Iterator high(Iterator first, Iterator last)
{
	if(first==last) error("Empty container");
	
	Iterator high=first;
	
	for(Iterator p=first;p!=last;++p)
	{
		if(*high<*p) high=p;
	}
	
	return high;
}

int main()
try
{
	my_list<double> l1;
	
	l1.push_back(4.6);
	l1.push_back(2);
	l1.push_back(6.3);
	l1.push_back(5);
	
	cout << "l1 highest value: " << *high(l1.begin(),l1.end()) << '\n';
	
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
