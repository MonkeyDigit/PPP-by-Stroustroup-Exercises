#include "std_lib_facilities.h"

struct Item{
	string name;
	int iid;
	double value;
};

istream& operator>>(istream& is, Item& it)
{
	char ch1,ch2;
	
	is >> ch1 >> ch2;
	
	if(!is) return is;
	if(ch1!='(' || ch2!= '\"')
		is.clear(ios_base::failbit); // set the fail bit
		
	it.name="";
	
	for(char ch;is.get(ch);)
	{
		if(ch=='\"') break;
		it.name+=ch;
	}
	
	if(!is) return is;
	if(is.eof())	//this means that the item name wasn't inserted properly
		is.clear(ios_base::failbit);
	
	is >> it.iid >> it.value >> ch2;
	
	if(!is) return is;
	if(ch2!=')')
		is.clear(ios_base::failbit);
	
	return is;
}

ostream& operator<<(ostream& os, const Item& it)
{
	return os << "(\"" << it.name << "\" " << it.iid << ' ' << it.value << ')';
}

struct Cmp_by_name{
	bool operator() (const Item& a, const Item& b) const
	{return a.name<b.name;}
};

struct Cmp_by_iid{
	bool operator() (const Item& a, const Item& b) const
	{return a.iid<b.iid;}
};

struct Cmp_by_value{
	bool operator() (const Item& a, const Item& b) const
	{return a.value<b.value;}
};

int main()
try
{
	vector<Item> vi;
	
	ifstream ifs{"items.txt"};
	for(int i=0;i<10;++i)
	{
		Item it;
		ifs>>it;
		vi.push_back(it);
	}
	
	for(const Item& it : vi)
		cout << it << '\n';
	
	cout << "\n------------------------\nSorted by name\n\n";
	
	sort(vi.begin(),vi.end(),Cmp_by_name());
	
	for(const Item& it : vi)
		cout << it << '\n';
		
	cout << "\n------------------------\nSorted by iid\n\n";
	
	sort(vi.begin(),vi.end(),Cmp_by_iid());
	
	for(const Item& it : vi)
		cout << it << '\n';
		
	cout << "\n------------------------\nSorted by value, printed in decreasing order\n\n";
	
	sort(vi.begin(),vi.end(),Cmp_by_value());
	
	for(int i=vi.size()-1;i>=0;--i)
		cout << vi[i] << '\n';

	cout << "\n------------------------\nInserted 2 items\n\n";
		
	vi.push_back(Item{"horse shoe",99,12.34});
	vi.push_back(Item{"Canon S400",9988,499.95});
	
	
	for(const Item& it : vi)
		cout << it << '\n';
		
	cout << "\n------------------------\nRemoved Nutella and Glass bowl\n\n";
	
	for(int i=0;i<vi.size();++i)
	{
		if(vi[i].name=="Nutella" || vi[i].name=="Glass bowl")
			vi.erase(vi.begin()+i);
	}
	
	for(const Item& it : vi)
		cout << it << '\n';
		
	cout << "\n------------------------\nRemoved items with iid 49 and 171\n\n";
	
	for(int i=0;i<vi.size();++i)
	{
		if(vi[i].iid==49 || vi[i].iid==171)
			vi.erase(vi.begin()+i);
	}
	
	for(const Item& it : vi)
		cout << it << '\n';
		
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
