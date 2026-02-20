#include "std_lib_facilities.h"

class B1{
public:
	virtual void vf() const {cout<<"B1::vf()\n";}
	void f() const {cout<<"B1::f()\n";}
	virtual void pvf() const =0;				//the '=0' notation indicates that pvf is virtual and must be overriden by derived classes
};									//this of course also means that we can't declare a B1 object anymore, since having one or more pure virtual functions
									//will make the class abstract.  B1 is now an abstract class
//by just adding pvf(), the file won't compile without further modifications. Like for example removing the declaration of B1 objects.
class D1 : public B1{//now an abstract class
public:
	void vf() const {cout<<"D1::vf()\n";}
	void f() const { cout<<"D1::f()\n";}
};

void call(B1& b)
{
	b.vf();
	b.f();
}

//new
class D2 : public D1{	//derived class of D1
	public:
		void pvf() const {cout<<"D2::pvf()\n";}
};

class B2{	//abstract class
	public:
		virtual void pvf() const =0;
};

class D21 : public B2 { //derived
	public:
		string label{"D21::pvf()"};
		void pvf() const {cout<<label<<'\n';}
		
};

class D22 : public B2 {
	public:
		int number{22};
		void pvf() const {cout<<number<<'\n';}
};

void f(B2& bb)
{
	bb.pvf();
}
int main()
{
	/*		B1 is now an abstract class
	B1 b;
	b.vf();
	b.f();
	cout<<'\n';
	*/
	
	/*IMPORTANT: this section will also not compile, because (in this moment) pvf() is not overridden by D1, so the compiler will warn you
	  that D1 is an abstract class	
	D1 d;
	d.vf();
	d.f();
	cout<<'\n';
	*/
	
	//call(d);
	
	D2 dd;	//this will compile because the D2 has overridden pvf()
	dd.f();
	dd.vf();
	dd.pvf();
	cout<<'\n';
	
	D21 dd21;
	f(dd21);
	cout<<'\n';
	
	D22 dd22;
	f(dd22);
	return 0;
}
