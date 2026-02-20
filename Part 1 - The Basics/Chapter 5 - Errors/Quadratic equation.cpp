#include "std_lib_facilities.h"

double get_value()
{
	double v;
	cin>>v;
	if(!cin) error("Couldn't read a double!");
	return v;
}

int main()
{
	double a{};
	double b{};
	double c{};
	double delta{};
	double x1{};
	double x2{};
	
	cout<<"Inserisci i coefficenti abc\n"<<"a'x^2 + b'x + c = 0\n";
	cout<<"a: ";
	a=get_value();
	cout<<"b: ";
	b=get_value();
	cout<<"c: ";
	c=get_value();
	
	delta=b*b-4*a*c;
	cout<<"delta: "<<delta<<'\n';
	if(delta<0)
	{
		cout<<"The equation doesn't have real solutions\n";
	}
	else
	{
		x1=(-b+sqrt(delta))/(2*a);
		x2=(-b-sqrt(delta))/(2*a);
		cout<<"x1: "<<x1<<"\nx2: "<<x2;
	}
	
}
