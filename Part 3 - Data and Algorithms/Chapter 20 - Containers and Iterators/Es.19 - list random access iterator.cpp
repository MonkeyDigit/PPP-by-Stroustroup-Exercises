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
		if(last==first) first=n;
		else last->prev->succ=n;
		
		n->prev=last->prev;
		n->succ=last;
		last->prev=n;
	}
	
	void push_front(const Elem& v) // insert v at front
	{
		Link<Elem>* n=new Link<Elem> {v,0,first};
		first->prev=n;
		first=n;
	}
	
	void pop_front() // remove the first element
	{
		if(last==first) return;
		first=first->succ;
		first->prev->prev=nullptr;//this isn't needed in theory
		first->prev->succ=nullptr;
	}
	
	void pop_back() // remove the last element
	{
		if(last==first) return;
		
		last->prev=last->prev->prev;
		last->prev->succ->prev=nullptr;
		last->prev->succ->succ=nullptr;
		last->prev->succ=last;
	}
	
	Elem& front() // the first element
	{
		return first->val;
	}
	
	Elem& back() // the last element
	{
		return last->prev->val;
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
	iterator& operator++(); // forward
	iterator& operator--();// backward
	Elem& operator*() { return curr->val; } // get value (dereference)
	bool operator==(const iterator& b) const { return curr==b.curr; }
	bool operator!= (const iterator& b) const { return curr!=b.curr; }
};

template<typename Elem>
typename my_list<Elem>::iterator& my_list<Elem>::iterator::operator++()
{
	if (curr->succ == nullptr) throw std::out_of_range("List it");
	curr = curr->succ;
	return *this;
}

template<typename Elem>
typename my_list<Elem>::iterator& my_list<Elem>::iterator::operator--()
{
	if (curr->prev == nullptr) throw std::out_of_range("List it");
	curr = curr->prev;
	return *this;
}

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
