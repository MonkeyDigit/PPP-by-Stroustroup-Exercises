#include "std_lib_facilities.h"
#include <map>

map<string,int> get_pairs()
{
	map<string,int> msi;
	
	
	char ch1;
	while(cin>>ch1)
	{
		string ss{""};
		int val;
		char ch2;
		cin>>ch2;
		if(!cin) error("Bad input");
		if(ch1!='(' || ch2!='\"') error("Incorrect input format");
		
		for(char ch;cin.get(ch);)
		{
			if(ch=='\"') break;
			
			ss+=ch;
		}
		
		cin>>val>>ch1;
		if(!cin) error("Bad input");
		if(ch1!=')') error("Incorrect input format");
		
		msi[ss]=val;
	}
	return msi;
}

int main()
try
{
	map<string,int> msi;
	
	msi["lecture"]=21;
	msi["stroustrup"]=54;
	msi["photography"]=10;
	msi["homework"]=43;
	msi["tractor"]=62;
	msi["dragonfly"]=39;
	msi["sweatshirt"]=16;
	msi["microphone"]=29;
	msi["company"]=58;
	msi["theatre"]=76;
	
	//the pairs are ordered as they are inserted
	for(const auto& p : msi)
		cout << p.first << ' ' << p.second << '\n';
		
	cout << "\nThe map after erasing the elements: \n";
	
	msi.erase(msi.begin(),msi.end());
	
	for(const auto& p : msi)
		cout << p.first << ' ' << p.second << '\n';
		
	cout << "\nEnter new elements (\"string\" value): \n";
	
	msi=get_pairs();
	for(const auto& p : msi)
		cout << p.first << ' ' << p.second << '\n';
		
	cout << "\nSum of the int values in msi: " 	//lambda function
		<< accumulate(msi.begin(), msi.end(), 0, 
			[](int v,const pair<string,int>& p) {return v+p.second;}) << '\n';
			
	
	cout << "\nmis (not msi) after copying from msi: \n";
	map<int,string> mis;
	for(const auto& p : msi)
		mis[p.second]=p.first;
		
	for(const auto& p : mis)
		cout << p.first << ' ' << p.second << '\n';
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
