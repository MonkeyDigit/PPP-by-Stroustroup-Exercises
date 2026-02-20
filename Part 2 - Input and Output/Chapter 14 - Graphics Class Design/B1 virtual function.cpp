#include "std_lib_facilities.h"

class B1{
public:
	virtual void vf() const {cout<<"B1::vf()\n";}		//virtual functions can be overridden by derived classes
	void f() const {cout<<"B1::f()\n";}
};

//a derived class inherits members from the base class
//by placing the prefix public, we let D1 access the public and protected (although there aren't in this case) functions of B1
class D1 : public B1{
public:
	void vf() const {cout<<"D1::vf()\n";}
	//added for different result
	void f() const { cout<<"D1::f()\n";}
};

void call(B1& b)
{
	b.vf();
	b.f();
}

int main()
{
	B1 b;
	b.vf();
	b.f();
	cout<<'\n';
	
	D1 d;
	d.vf();
	d.f();	//because D1 is a derived class of B1, we can call f() because it's an inherited function - this was before adding f() to D1
	cout<<'\n';
	
	call(d);	//same thing as before, a derived class can be used where its base class is needed
				//after adding f() to D1, B1's f() will still be called because the function needs to call a B1 object's f(),
				//and since it's not a virtual function, it cannot be overriden by derived classes.
				
				//Using the same name and type is not enough to inherit the function, it needs to be made as virtual
	return 0;
}
