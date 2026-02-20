#include "std_lib_facilities.h"
/*In this file we implement all the functions as class members, but anyway, we have to consider this: even if the function we want to implement
can theoretically be implemented outside of the class, we must consider the invariant (the rule that determines what costitutes a valid value),
and if we need to check if the values used by the functions are valid, then it's better to implement it inside the class, so that it does its own
error checking.*/

//determine what's public and what's not
//remember to implement error handling
class Name_pairs {
	public:
		vector<string> names() const { return n; };
		vector<int> ages() const { return a; };
		void read_names();
		void read_ages();
		void sort_names();
		void print();
	private:
		vector<string> n;
		vector<int> a;
};

void Name_pairs::read_names()
{
	string s{};
	while(true)
	{
		cout << "> ";
		cin >> s;
		if (s != "NoName")
		{
			n.push_back(s); //since this is a member function, the name referred here is the one in Name_pairs
		}
		else break;
	}
}

void Name_pairs::read_ages()
{
	int age;
	for (string name : n)
	{
		cout << name << ": ";
		cin >> age;
		if(!cin || age < 0) error("Invalid age");
		else a.push_back(age);
	}
	if(a.size() != n.size()) error ("Name and age vector sizes doesn't match");
}
void Name_pairs::sort_names()
{
	vector<string> name_copy = n;	//copy the unsorted vectors
	vector<int> age_copy = a;
	
	sort(n.begin(),n.end());	//sort names and ages
	for (int i=0; i<n.size();++i)	//do this for each name
	{
		for(int j=0; j<n.size(); ++j)	//find its position in the unsorted name vector (name_copy) and assign its age to the corresponding sorted position
		{
			if (n[i] == name_copy[j]) a[i] = age_copy[j];
		}
	}
}
/*
void Name_pairs::print()
{
	if(a.size() != n.size()) error ("Name and age vector sizes doesn't match");
	for (int i=0; i<n.size(); ++i)
	{
		cout << n[i] << ": " << a[i] << '\n';
	}
}
*/
bool operator==(const Name_pairs& x, const Name_pairs& y)
{
	return x.names() == y.names()
		&& x.ages() == y.ages();
}

bool operator!=(const Name_pairs& x, const Name_pairs& y)
{
	return !(x == y);
}
	
ostream& operator<<(ostream& os, const Name_pairs& np)
{
	if(np.names().size() != np.ages().size()) error ("Name and age vector sizes doesn't match");
	
	for(int i=0; i<np.names().size(); ++i)
	{
		os << np.names()[i] << ": " << np.ages().size() << '\n';
	}
	
	return os;
}

//MAIN---------------------------------------------------
int main()
{
	Name_pairs clients;
	cout << "Enter the clients' names" << '\n';
	clients.read_names();
	clients.read_ages();
	clients.sort_names();
	cout << "Sorted names:" << '\n';
	cout << clients << '\n';
	//clients.print();
	return 0;
}
