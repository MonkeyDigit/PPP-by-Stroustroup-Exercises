#include "std_lib_facilities.h"

void print(vector<string>& s,vector<double>& v);

int main()
{
	vector<string> name;
	vector<double> age;
	vector<string> name_copy;	//needed to order the ages 
	vector<double> age_copy;
	
	cout<<"Enter a name and age\n";
	while(true)
	{
		double a;
		string s;
		cout<<"Name: "; cin>>s;
		cout<<"Age: "; cin>>a;
		if(!cin) error("Couldn't read a double in age");
		if(s!="NoName" || a!=0)
		{
			name.push_back(s);
			age.push_back(a);
		}
		else break;
	}
	
	for(string x : name) name_copy.push_back(x);	//copying the names
	//for(double x : age) age_copy.push_back(x);
	
	print(name,age);
	sort(name.begin(),name.end());
	
	cout<<"Vector sorted: \n";
	for(int i=0;i<name.size();i++)		//for each name in the vector sorted, check
	{
		for(int j=0;j<name.size();j++)	//if any name corresponds, if so, get the age
		{
			if(name[i]==name_copy[j])
			{
				age_copy.push_back(age[j]);
			}
		}
	}
	
	print(name,age_copy);
}

void print(vector<string>& s,vector<double>& v)
{
	for(int i=0;i<s.size();i++)
	cout<<s[i]<<": "<<v[i]<<'\n';
}
