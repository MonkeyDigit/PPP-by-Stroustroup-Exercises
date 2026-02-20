#include "std_lib_facilities.h"

template<class T>
struct Link{
	T val;
	Link* succ;
	
	Link(): val{T()}, succ{nullptr} { }
	Link(const T& val, Link* succ=nullptr): val{val}, succ{succ} { }
};

template<typename Elem>
class my_list {
	// representation and implementation details
	Link<Elem>* first;
	Link<Elem>* last;	//one beyond the last element
public:
	my_list(): first{new Link<Elem> {}}, last{first} { }
	
	class iterator; // member type: iterator
	iterator begin() // iterator to first element
	{ return first; }
	
	iterator end()// iterator to one beyond last element
	{ return last; }
	
	iterator insert(iterator p, const Elem& v) // insert v into list after p
	{
		Link<Elem>* n=new Link<Elem> {v,p->succ};
		p->succ=n;
		return n;
	}
	
	iterator erase(iterator p) // remove p from the list
	{
		if(!p) error("Tried to erase a nullptr");
		
		iterator it=first;
		while(it->succ!=p) ++it;
		it->succ=p->succ;
		p->succ=nullptr;
		
		return p;
	}
	
	void push_back(const Elem& v) // insert v at end
	{
		Link<Elem>* n=new Link<Elem> {v};
		if(last==first) 
		{
			first=n;
			first->succ=last;
		}
		else
		{
			iterator it=first;
			while(it->succ) ++it;
			it->succ=n;
		}
		
	}
	
	void push_front(const Elem& v) // insert v at front
	{
		Link<Elem>* n=new Link<Elem> {v,first};
		first=n;
	}
	
	void pop_front() // remove the first element
	{
		if(last==first) return;
		
		Link<Elem>* p=first;
		first=first->succ;
		p->succ=nullptr;
	}
	
	void pop_back() // remove the last element
	{
		if(last==first) return;
		
		iterator it=first;
		while(it->succ && it->succ->succ) ++it;
		
		if(it==first) 
		{
			first=nullptr;
			last=first;
		}
		else
		{
			it->succ=nullptr;
		}
	}
	
	Elem& front() // the first element
	{
		return first->val;
	}
	
	Elem& back() // the last element
	{
		iterator it=first;
		while(it->succ) ++it;
		
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
	//iterator& operator--() { curr = curr->prev; return *this; } // backward
	Elem& operator*() { return curr->val; } // get value (dereference)
	bool operator==(const iterator& b) const { return curr==b.curr; }
	bool operator!= (const iterator& b) const { return curr!=b.curr; }
	Link<Elem>* operator->() { return curr; }
    Link<Elem>* ptr() const { return curr; }
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
