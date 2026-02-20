/*
3. Based on §26.3.2.3, complete a program that generates
a. A very large sequence (what would you consider very large, and why?)
b. Ten sequences with a random number of elements
c. Ten sequences with 0, 1, 2 . . . 9 random elements (but still ordered)
 4. Repeat these tests for sequences of strings, such as { Bohr Darwin Einstein 
Lavoisier Newton Turing }.
*/
#include "std_lib_facilities.h"

void make_test(const string& lab, int n, int base, int spread)
	// write a test description with the label lab to cout
	// generate a sequence of n elements starting at base
	// the average distance between elements is uniformly distributed
	// in [0:spread)
{
	cout << "{ " << lab << ' ' << n << " { ";
	
	vector<int> v;
	int elem{base};
	
	for(int i=0;i<n;++i)	//make elements
	{
		elem += randint(spread);
		v.push_back(elem);
	}
	
	int val = base + randint(elem-base); //make search value
	bool found{false};
	
	for(int i=0; i<n; ++i)	//print elements and see if val is found
	{
		if(v[i] == val)
			found = true;
		cout << v[i] << ' ';
	}
	
	cout << "} " << found << "}\n";
}

int main()
{
	//make_test("test 1", 10000, 0, 6);	
	
	for(int i=0;i<10;++i)
	{
		make_test("sequence no."+to_string(i+1), randint(30), 0, 8);
	}
	return 0;
}
