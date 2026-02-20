#include "std_lib_facilities.h"
struct Person{
	Person(string first_name,string second_name,int age);
	Person() {}
	string first_name() const {return fn;}
	string second_name() const {return sn;}
	int age() const {return a;}
private:
	string fn;
	string sn;
	int a;
};

Person::Person(string first_name,string second_name, int age)
	: fn(first_name),sn(second_name), a(age)
{
	if(a<0 || 125<a) error("Invalid age");
	if(fn.length()<=0) error("Invalid first name");
	if(sn.length()<=0) error("Invalid second name");
	
	for(char& ch : fn)
	{
		if(!isalpha(ch)) error("Invalid first name");
	}
	
	for(char& ch : sn)
	{
		if(!isalpha(ch)) error("Invalid second name");
	}
}
ostream& operator<<(ostream& os,const Person& per)
{
	return os << "Name: " << per.first_name() << ',' 
			<< per.second_name()
			<< " Age: " << per.age();
}

istream& operator>>(istream& is,Person& per)
{
	string first_name;
	string second_name;
	int age;
	is >> first_name >> second_name >> age;
	per = Person(first_name,second_name,age);
	return is;
}

int main()
try
{
	/*
	Person per;
	per.name="Goofy";
	per.age=63;
	cout << "Name: " << per.name << " Age: " << per.age << '\n';
	*/
	/*
	Person per2;
	cout << "Enter a person - name age: ";
	cin>>per2;
	cout<<per2<<'\n';
	*/
	
	vector<Person> people;
	cout<<"Please enter a list of people. Enter X end\n";
	for(char check;cin>>check;)
	{
		if (check == 'X') break;
		cin.putback(check);
		Person p1;
		cin >> p1;
		people.push_back(p1);
	}
	
	cout<<"------------------------------\n";
	for(Person& p : people)
	{
		cout << p << '\n';
	}
	keep_window_open();
	return 0;
}

catch (exception& e) 
{
	cout << e.what() << endl;
	return 1;
}
catch (...)
{
	cout << "Exiting" << endl;
	return 2;
}
