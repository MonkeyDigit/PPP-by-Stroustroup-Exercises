#include "std_lib_facilities.h"

void print_array(ostream& os, int* a, int n);
void print_vector(ostream& os, const vector<int>& vect);

int main()
try
{
	
	int x{7};
	int* p1=&x; //p1 can hold addresses for int objects - with & (address of) operator, we initialize p1 with x's address
	
	//will output the address of p1 in hexadecimal base, and then by adding the prefix * (content of) we output its content (x's value)
	cout << "p1 - address("<<p1<<") content("<<*p1<<")\n";
	
	int* p2 = new int[7];
	double prec{0.5};
	for(int i=0;i<7;++i)
	{
		p2[i]=prec*2;
		prec=prec*2;
	}
	
	cout << "p2 - address("<<p2<<") content(";
	print_array(cout,p2,7);
	cout<<")\n";
	
	int* p3=p2;
	
	p2=p1;
	p2=p3;
	
	cout << "p1 - address("<<p1<<") content("<<*p1<<")\n";
	cout << "p2 - address("<<p2<<") content(";
	print_array(cout,p2,7);
	cout<<")\n";
	
	delete p1;	//just holds an address of a single value object, not an array
	delete[] p2;
	delete[] p3;
	
	p1 = new int[10];
	prec = 0.5;
	for(int i=0;i<10;++i)
	{
		p1[i]=prec*2;
		prec=prec*2;
	}
	cout << "p1 - address("<<p1<<") content(";
	print_array(cout,p1,10);
	cout<<")\n";
	
	p2 = new int[10];
	for(int i=0;i<10;++i)
	{
		p2[i]=i;
	}
	cout << "p2 - address("<<p2<<") content(";
	print_array(cout,p2,10);
	cout<<")\n";
	
	for(int i=0;i<10;++i)
	{
		p2[i]=p1[i];
	}
	cout << "p2 - address("<<p2<<") content(";
	print_array(cout,p2,10);
	cout<<")\n";
	
//using vector
	vector<int> vect1;
	prec = 0.5;
	for(int i=0;i<10;++i)
	{
		vect1.push_back(prec*2);
		prec=prec*2;
	}
	cout << "vect1 - content(";
	print_vector(cout,vect1);
	cout<<")\n";
	
	vector<int> vect2;
	for(int i=0;i<10;++i)
	{
		vect2.push_back(i);
	}
	cout << "vect2 - content(";
	print_vector(cout,vect2);
	cout<<")\n";
	
	for(int i=0;i<10;++i)
	{
		vect2[i]=vect1[i];
	}
	cout << "vect2 - content(";
	print_vector(cout,vect2);
	cout<<")\n";
	
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
