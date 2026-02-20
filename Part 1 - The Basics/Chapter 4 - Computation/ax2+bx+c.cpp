#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double a,b,c,x,delta;
	cout<<"ax^2+bx+c=0"<<endl;
	cout<<"a: ";cin>>a;
	cout<<"b: ";cin>>b;
	cout<<"c: ";cin>>c;
	
	delta= b*b - 4*a*c;
	cout<<"delta: "<<delta<<endl;
	if(delta<0)
	{
		cout<<"x is not real"<<endl;
	}
	else
	{
		cout<<"x1: "<<(-b+sqrt(delta))/2*a<<endl;
		cout<<"x2: "<<(-b-sqrt(delta))/2*a;
	}
}
