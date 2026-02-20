#include "std_lib_facilities.h"

struct God{
	God(string name,string mythology,string vehicle,string weapon)
		: name(name), mythology(mythology), vehicle(vehicle), weapon(weapon) { }
	string name;
	string mythology;
	string vehicle;
	string weapon;
};

ostream& operator<<(ostream& os, const God& g)
{
	return os << g.name << ", " << g.mythology << ", " << g.vehicle << ", " << g.weapon;
}

bool operator==(const God& a, const God& b)
	{
		return a.name == b.name
			&& a.mythology == b.mythology
			&& a.vehicle == b.vehicle
			&& a.weapon == b.weapon;
	}

bool operator!=(const God& a, const God& b)
{
	return !(a == b);
}
	
class Link {
public:
	God value; 
	Link(const God& v, Link* p = nullptr, Link* s = nullptr)
	: value{v}, prev{p}, succ{s} { }
	Link* insert(Link* n); // insert n before this object
	Link* add(Link* n); // insert n after this object
	Link* erase(); // remove this object from list
	Link* find(const God& g); // find s in list
	const Link* find(const God& g) const; // find s in const list (see §18.5.1)
	const Link* advance(int n) const; // move n positions in list
	Link* next() const { return succ; }
	Link* previous() const { return prev; }
	
	Link* add_ordered(Link* n);
	void print_all();
private:
	Link* prev;
	Link* succ;
};


void print_all(Link* p);

int main()
{
	Link* greek_gods = new Link{God{"Zeus", "Greek", "", "lightning"}};
	greek_gods = greek_gods->insert(new Link{God{"Poseidon","Greek","", "Water"}});
	
	Link* norse_gods = new Link{God{"Odin", "Norse", "Eight-legged flying horse called Sleipner", "Spear called Gungnir"}};
	norse_gods = norse_gods->insert(new Link{God{"Thor","Norse","","Hammer"}});
	cout << "greek gods\n";
	greek_gods->print_all();
	cout<<'\n';
	cout << "\nnorse gods\n";
	norse_gods->print_all();

	return 0;
}

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

Link* Link::find(const God& g) // find s in list;
 // return nullptr for “not found”
{
	Link* p = this;	//we must copy the pointer, because the this pointer can't point to any old object, so we can't change its value
	while (p)
	{
		if (p->value == g) return p;
		p = p->next();
	}
	return nullptr;
}

const Link* Link::find(const God& g) const
{
    if (value == g)
        return this;
    else if (succ)
        return succ->find(g);
    
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

void Link::print_all()
{
	cout << "{ \n";
	int n{0};
	while (advance(n))
	{
		cout << advance(n)->value;
		if (advance(n)->next()) cout << '\n';
		n++;
	}
	cout << "\n}";
}

Link* Link::add_ordered(Link* n) // insert n after p; return n
    // this will always be called from the first element in the list
    // handle insert case: new head of list
    // loop through rest of list and add where appropriate
{
    if (value.name > n->value.name) {
        prev = n;
        n->succ = this;
        return n;
    }
    else 
	{
        Link* p = this;
        while (p->succ) {           // working through list checking lex
            if (p->value.name < n->value.name &&
                    n->value.name < p->succ->value.name) {
                p->add(n);
                return this;
            }
            p = p->succ;
        }
        p->add(n);                  // end of list, add to tail
    }
    return this;
}
