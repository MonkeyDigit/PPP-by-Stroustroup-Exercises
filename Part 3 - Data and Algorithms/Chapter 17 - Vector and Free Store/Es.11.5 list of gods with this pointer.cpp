#include "std_lib_facilities.h"

class Link {
public:
	string value; 
	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
	: value{v}, prev{p}, succ{s} { }
	Link* insert(Link* n); // insert n before this object
	Link* add(Link* n); // insert n after this object
	Link* erase(); // remove this object from list
	Link* find(const string& s); // find s in list
	const Link* find(const string& s) const; // find s in const list (see §18.5.1)
	const Link* advance(int n) const; // move n positions in list
	Link* next() const { return succ; }
	Link* previous() const { return prev; }
private:
	Link* prev;
	Link* succ;
};


void print_all(Link* p);

int main()
{
	//We can access a class member through a pointer with the -> operartor
	Link* norse_gods = new Link{"Thor"};
	norse_gods = norse_gods->insert(new Link{"Odin"});
	norse_gods = norse_gods->insert(new Link{"Zeus"});
	norse_gods = norse_gods->insert(new Link{"Freia"});
	
	Link* greek_gods = new Link{"Hera"};
	greek_gods = greek_gods->insert(new Link{"Athena"}); 
	greek_gods = greek_gods->insert(new Link{"Mars"});
	greek_gods = greek_gods->insert(new Link{"Poseidon"});
	
	Link* p = greek_gods->find("Mars");
	if (p) p->value = "Ares";
	
	Link* p2 = norse_gods->find("Zeus");
	if (p2)
	{
		if (p2==norse_gods) norse_gods = p2->next();
		p2->erase();
		greek_gods = greek_gods->insert(p2);
	}
	
	print_all(norse_gods);
	cout<<"\n";
	print_all(greek_gods);
	cout<<"\n";

	return 0;
}

//FUNCTIONS DEFINITION
/*
Link* Link::insert(Link* n) // insert n before p; return n
{
	Link* p = this; // pointer to this object
	if (n==nullptr) return p; // nothing to insert
	if (p==nullptr) return n; // nothing to insert into
	n->succ = p; // p comes after n
	if (p->prev) p->prev->succ = n;
	n->prev = p->prev; // p’s predecessor becomes n’s predecessor
	p->prev = n; // n becomes p’s predecessor
	return n;
}
*/

//We can simply use the this pointer instead of p
Link* Link::insert(Link* n) // insert n before p; return n
{
	if (n==nullptr) return this;
	if (this==nullptr) return n;
	n->succ = this; // this object comes after n
	if (prev) prev->succ = n;			// prev simply refers to this->prev, as it is a member of the class
	n->prev = prev; // this object’s predecessor becomes n’s predecessor
	prev = n; // n becomes this object’s predecessor
	return n;
}

Link* Link::add(Link* n) // insert n after p; return n
{
	// much like insert (see exercise 11)
	if (n==nullptr) return this;
	if (this==nullptr) return n;
	n->prev = this; // p comes before n
	if(succ) succ->prev = n;
	n->succ = succ;
	succ = n;
	return n;
}

Link* Link::erase() // remove *p from list; return p’s successor
{
	if (this==nullptr) return nullptr;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

Link* Link::find(const string& s) // find s in list;
 // return nullptr for “not found”
{
	Link* p = this;	//we must copy the pointer, because the this pointer can't point to any old object, so we can't change its value
	while (p)
	{
		if (p->value == s) return p;
		p = p->next();
	}
	return nullptr;
}

const Link* Link::find(const string& s) const
{
    if (value == s)
        return this;
    else if (succ)
        return succ->find(s);
    
    return nullptr;
}


const Link* Link::advance(int n) const// move n positions in list
// return nullptr for “not found”
// positive n moves forward, negative backward
{
    if (0 < n) {
        if (succ == nullptr) return nullptr;

        return succ->advance(--n);
    }
    else if (n < 0) {
        if (prev == nullptr) return nullptr;

        return prev->advance(++n);
    }
    return this;
} 

void print_all(Link* p)
{
	cout << "{ ";
	while (p)
	{
		cout << p->value;
		if (p=p->next()) cout << ", ";
	}
	cout << " }";
}
