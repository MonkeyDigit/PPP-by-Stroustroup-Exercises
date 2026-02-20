#include "std_lib_facilities.h"
/*In this file we implement all the functions as class members, but anyway, we have to consider this: even if the function we want to implement
can theoretically be implemented outside of the class, we must consider the invariant (the rule that determines what costitutes a valid value),
and if we need to check if the values used by the functions are valid, then it's better to implement it inside the class, so that it does its own
error checking.*/

//determine what's public and what's not
//remember to implement error handling
class Name_pairs {
	public:
		void read_names();
		void read_ages();
		void sort_names();
		void print();
	private:
		vector<string> name;
		vector<int> age;
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
			name.push_back(s); //since this is a member function, the name referred here is the one in Name_pairs
		}
		else break;
	}
}

void Name_pairs::read_ages()
{
	int a;
	for (string n : name)
	{
		cout << n << ": ";
		cin >> a;
		if(!cin || a < 0) error("Invalid age");
		else age.push_back(a);
	}
	if(age.size() != name.size()) error ("Name and age vector sizes doesn't match");
}
void Name_pairs::sort_names()
{
	vector<string> name_copy = name;	//copy the unsorted vectors
	vector<int> age_copy = age;
	
	sort(name.begin(),name.end());	//sort names and ages
	for (int i=0; i<name.size();++i)	//do this for each name
	{
		for(int j=0; j<name.size(); ++j)	//find its position in the unsorted name vector (name_copy) and assign its age to the corresponding sorted position
		{
			if (name[i] == name_copy[j]) age[i] = age_copy[j];
		}
	}
}

void Name_pairs::print()
{
	if(age.size() != name.size()) error ("Name and age vector sizes doesn't match");
	for (int i=0; i<name.size(); ++i)
	{
		cout << name[i] << ": " << age[i] << '\n';
	}
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
	clients.print();
	return 0;
}
