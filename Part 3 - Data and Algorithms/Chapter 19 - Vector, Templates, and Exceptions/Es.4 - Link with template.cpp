#include "std_lib_facilities.h"

struct God{
	God(string name,string myth, string weapon)
		: name{name}, myth{myth}, weapon{weapon} { }
	string name;
	string myth;
	string weapon;
};

std::ostream& operator<<(std::ostream& os, God& g)
{
    return os << g.name << ' ' << g.weapon;
}

bool operator<(const God& a, const God& b) { return a.name < b.name; }
bool operator>(const God& a, const God& b) { return a.name > b.name; }
bool operator<=(const God& a, const God& b) { return a.name <= b.name; }
bool operator>=(const God& a, const God& b) { return a.name >= b.name; }
bool operator==(const God& a, const God& b) { return a.name == b.name; }
bool operator!=(const God& a, const God& b) { return !(a == b); }

template<typename T>
struct Link {
	Link(const T& v, Link<T>* p = nullptr, Link* s = nullptr)
	: value{v}, prev{p}, succ{s} { }
	
	T value;
	Link<T>* prev;
	Link<T>* succ;
	Link<T>* add(Link<T>*);
	Link<T>* insert(Link<T>*);
	Link<T>* add_ordered(Link<T>*);
	Link<T>* erase();
};

template<typename T>
Link<T>* Link<T>::insert(Link<T>* n) // insert n before p; return n
{
	if (n==nullptr) return this;
	n->prev = prev; // this object’s predecessor becomes n’s predecessor
	n->succ = this; // this object comes after n
	if (prev) prev->succ = n;			// prev simply refers to this->prev, as it is a member of the class
	prev = n; // n becomes this object’s predecessor
	return n;
}

template<typename T>
Link<T>* Link<T>::add(Link<T>* n) // insert n after p; return n
{
	// much like insert (see exercise 11)
	if (n==nullptr) return this;
	n->prev = this; // p comes before n
	if(succ) succ->prev = n;
	n->succ = succ;
	succ = n;
	return this;
}

template<typename T>
Link<T>* Link<T>::erase()
{
    if (prev) prev->succ = succ;
    if (succ) succ->prev = prev;
    prev = nullptr;
    succ = nullptr;
    return this;
}

template<typename T>
Link<T>* Link<T>::add_ordered(Link<T>* n) // insert n after p; return n
    // this will always be called from the first element in the list
    // handle insert case: new head of list
    // loop through rest of list and add where appropriate
{
	if(n == nullptr) return this;
	
    if (n->value < value)
        return insert(n);
        
    Link<T>* p = this;
    while (p->succ)
	{           // working through list checking lex
        if (p->value < n->value && n->value < p->succ->value)
		{
            p->add(n);
            return this;
        }
        p = p->succ;
    }
    p->add(n);                  // end of list, add to tail
    return this;
}

template<typename T>
void print_all(Link<T>* p)
{
	while(p)
	{
		cout << p->value <<'\n';
		p=p->succ;
	}
}

Link<God>* break_out_list(Link<God>*& list, const std::string& s)
    // if match is found at list head, transfer head to succ link
    // if match is found, store ptr to q->succ before erasing q
{
    Link<God>* p = nullptr;                 // new list
    Link<God>* q = list;

    while (q) {
        if (q->value.myth == s) {
            if (q->prev == nullptr) list = list->succ;

            Link<God>* t = q->succ;
            p = p == nullptr ? q->erase() : p->add_ordered(q->erase());
            q = t;
        }
        else q = q->succ;
    }

    return p;
}

int main()
try
{
	God thor {"Thor", "Norse", "Mjolnir"};
    God odin {"Odin", "Norse", "Gungnir"};
    God zeus {"Zeus", "Greek", "Lightning"};
    God freia {"Freia", "Norse", "Brisingamen"};
    God hera {"Hera", "Greek", "pomegranate"};
    God tyr {"Tyr", "Norse", "spear of justice"};
    God athena {"Athena", "Greek", "thunderbolt"};
    God poseidon {"Poseidon", "Greek", "trident"};
    God ares {"Ares", "Greek", "random spear"};

    Link<God>* gods = new Link<God>{thor};
    gods = gods->add(new Link<God>{odin});
    gods = gods->insert(new Link<God>{zeus});
    gods = gods->add(new Link<God>{freia});
    gods = gods->insert(new Link<God>{hera});
    gods = gods->add(new Link<God>{tyr});
    gods = gods->insert(new Link<God>{athena});
    gods = gods->add(new Link<God>{poseidon});
    gods = gods->add(new Link<God>{ares});

    std::cout << '\n';

    std::cout << "All Gods:\n";
    std::cout << "=========\n";
    print_all(gods);
    std::cout << '\n';

    Link<God>* norse = break_out_list(gods, "Norse");

    std::cout << "Norse Gods:\n";
    std::cout << "===========\n";
    print_all(norse);
    std::cout << '\n';

    Link<God>* greek = break_out_list(gods, "Greek");

    std::cout << "Greek Gods:\n";
    std::cout << "===========\n";
    print_all(greek);
    std::cout << '\n';

    std::cout << "All Gods:\n";
    std::cout << "=========\n";
    print_all(gods);
    std::cout << '\n';
	return 0;
}
catch(exception& e)
{
	cerr<<"error"<<e.what()<<'\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr<<"Unknown error\n";
	keep_window_open();
	return 2;
}
