#include "std_lib_facilities.h"
#include <set>

struct Fruit{
	string name;
	int count;
	double unit_price;
};

struct Fruit_comparison{
	bool operator()(const Fruit* a, const Fruit* b) const
	{
		return (*a).name<(*b).name;
	}
};

//There isn't a big difference between the first implementation (§21.6.5)
//in Fruit_comparison we just dereference the fruits and compare their names
//and when inserting fruits in the set we use new to allocate them in the free 
//store memory

ostream& operator<<(ostream& os, const Fruit& f)
{
	return os << '(' << f.name << ' ' << f.count << ' ' << f.unit_price << ')';
}

int main()
try
{
	set<Fruit*,Fruit_comparison> inventory;
	
	inventory.insert(new Fruit{"Orange", 21, 1.99});
	inventory.insert(new Fruit{"Apple", 46, 2.50});
	inventory.insert(new Fruit{"Strawberry", 33, 2.66});
	inventory.insert(new Fruit{"Banana", 45, 2.30});
	
	for(const auto& p : inventory)
		cout << *p << '\n';
	return 0;
}
catch(exception & e)
{
	cerr<< "Exception: " << e.what() <<'\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
