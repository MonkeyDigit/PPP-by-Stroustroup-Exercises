#include "std_lib_facilities.h"
//References are useful when, for example, a function has to operate on large vectors or arrays, as it can directly read and/or write its elements,
//thus optimizing time and memory
void swap_v(int,int);				//No variables modified: the arguments are just copies of the variables passed
void swap_r(int&,int&);				//Variables modified: Uses pass-by-reference, so it operates (can read,write) on the actual variables passed
//void swap_cr(const int&, const int&);//Variables just read: Uses pass-by-const reference, so it's the same as the previous one, except an error
									 // is thrown if an assignment is tried
									 //The variables can only be read
//NOTE:In the functions above, we wrote (int,int) without giving the parameters a name, this is fine, as long as we give it at some point
//with this, we are just saying that the function will take some integers

//NOTE: A const value must be determinable at compile time
int main()
{
	int x = 7;
	int y =9;
	const int cx = 7;
	const int cy = 9;
	double dx = 7.7;
	double dy = 9.9;
	
	cout<<"int x = "<<x<<'\n'
		<<"int y = "<<y<<'\n'
		<<"const int cx = "<<cx<<'\n'	
		<<"const int cy = "<<cy<<'\n'
		<<"double dx = "<<dx<<'\n'
		<<"double dy = "<<dy<<'\n';
	// replaced ? by v, r, or cr
	
	/*-------------------------------------------------------------------------------------------------------------------------------------------
	swap_v(x,y); //no errors
	swap_v(7,9); //no errors
	
	swap_v(cx,cy);	//no errors - they are const types, but swap_v just uses its local variables
	//swap_v(7.7,9.9); //error! - won't compile since swap_v takes ints, the conversion will have a loss of information (7.7->7; 9.9->9)
	
	//swap_v(dx,dy); //error! - same error as the previous one, this time the values are just obtained from variables
	--------------------------------------------------------------------------------------------------------------------------------------------*/
	/*
	swap_r(x,y); //no errors - the variables get modified
	//swap_r(7,9); //error! - this won't compile, as a reference works with variables, not expressions and literals
	
	//swap_r(cx,cy);	//error! - won't compile: reference of type int& from expression of type const int
	//swap_r(7.7,9.9); //error! - won't compile: not only is it wrong because the arguments must be variables, but they also aren't ints
	
	//swap_r(dx,dy); //error! won't compile: invalid initialization of reference of type 'int&' from expression of type 'double'
	*/
	
	//Can't use swap_cr because constants are, well, constants...
	cout<<"-------------------\n"
		<<"int x = "<<x<<'\n'
		<<"int y = "<<y<<'\n'
		<<"const int cx = "<<cx<<'\n'	
		<<"const int cy = "<<cy<<'\n'
		<<"double dx = "<<dx<<'\n'
		<<"double dy = "<<dy<<'\n';
	
	
	return 0;
}
 
void swap_v(int a,int b) { int temp; temp = a, a=b; b=temp; }
void swap_r(int& a,int& b) { int temp; temp = a, a=b; b=temp; }
//void swap_cr(const int& a, const int& b) { int temp; temp = a, a=b; b=temp; } --------->Can't modify const types

