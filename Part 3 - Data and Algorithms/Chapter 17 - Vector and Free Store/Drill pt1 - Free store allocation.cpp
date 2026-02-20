#include "std_lib_facilities.h"

void print_array10(ostream& os, int* a);
void print_array(ostream& os, int* a, int n);
void print_vector(ostream& os, const vector<int>& v);
int main()
try
{
	//Allocating an array of ten ints on the free store using new
	int* ten_ints = new int[10];
	for(int i=0;i<10;++i)
	{
		ten_ints[i]=i*11;
	}
	
	for(int i=0;i<10;++i)
	{
		cout<<ten_ints[i]<<'\n';
	}
	
	//deleting the array from the free store memory
	delete[] ten_ints;	
	
	//We can reuse ten_ints
	ten_ints = new int[10];
	
	for(int i=0;i<10;++i)
	{
		ten_ints[i]=i+100;
	}
	print_array10(cout,ten_ints);
	delete[] ten_ints;
	
//eleven ints
	int* eleven_ints = new int[11];
	
	for(int i=0;i<11;++i)
	{
		eleven_ints[i]=i+100;
	}
	
	cout << '\n';
	for(int i=0;i<11;++i)
	{
		cout<<eleven_ints[i]<<'\n';
	}
	delete[] eleven_ints;
	
//twenty ints
	int* twenty_ints = new int[20];
	
	for(int i=0;i<20;++i)
	{
		twenty_ints[i]=i+100;
	}
	print_array(cout,twenty_ints,20);
	delete[] twenty_ints;
	
//vector
	vector<int> ten_ints_vect;
	for(int i=0;i<10;++i)
	{
		ten_ints_vect.push_back(i+100);
	}
	cout<<"\nvector\n";
	print_vector(cout,ten_ints_vect);
	
	vector<int> eleven_ints_vect;
	for(int i=0;i<11;++i)
	{
		eleven_ints_vect.push_back(i+100);
	}
	cout<<'\n';
	print_vector(cout,eleven_ints_vect);
	
	vector<int> twenty_ints_vect;
	for(int i=0;i<20;++i)
	{
		twenty_ints_vect.push_back(i+100);
	}
	cout<<'\n';
	print_vector(cout,twenty_ints_vect);
	
	return 0;
}

catch(exception& e)
{
	cerr<<"error: "<<e.what();
	keep_window_open();
	return 1;
}

catch(...)
{
	cerr<<"exception";
	keep_window_open();
	return 2;
}

//---------------------------------------------------
void print_array10(ostream& os, int* a)
{
	for(int i=0;i<10;++i)
	{
		os <<a[i];
		if(i<9) os << ", ";
	}
}

void print_array(ostream& os, int* a, int n)
{
	for(int i=0;i<n;++i)
	{
		os <<a[i];
		if(i<n-1) os << ", ";
	}
}

void print_vector(ostream& os, const vector<int>& vect)
{
	for(int i=0;i<vect.size();++i)
	{
		os <<vect[i];
		if(i<vect.size()-1) os << ", ";
	}
}
