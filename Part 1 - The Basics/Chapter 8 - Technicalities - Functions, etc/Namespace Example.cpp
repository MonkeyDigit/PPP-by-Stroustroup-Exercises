#include "std_lib_facilities.h"
/*Write a program using a single file containing three namespaces X, Y, and Z so that the following main() works correctly:
int main()
{
	X::var = 7;
	X::print(); // print X’s var
	using namespace Y;
	var = 9;
	print(); // print Y’s var
	{ using Z::var;
	using Z::print;
	var = 11;
	print(); // print Z’s var
	}
	print(); // print Y’s var
	X::print(); // print X’s var
}

//Each namespace needs to define a variable called var and a function called 
  print() that outputs the appropriate var using cout.*/

namespace X {
	int var;
	void print()
	{
		cout<<var<<'\n';
	}
	
}

namespace Y {
	int var;
	void print()
	{
		cout<<var<<'\n';
	}
	
}

namespace Z {
	int var;
	void print()
	{
		cout<<var<<'\n';
	}
	
}

/*FROM THE BOOK:
That construct is called a using declaration; it is the programming equivalent to 
using plain “Greg” to refer to Greg Hansen, when there are no other Gregs in the 
room.
Sometimes, we prefer an even stronger “shorthand” for the use of names 
from a namespace: “If you don’t find a declaration for a name in this scope, look 
in X.” The way to say that is to use a using directive
*/

int main()
{
	X::var = 7;
	X::print(); // print X’s var
	using namespace Y;
	var = 9;
	print(); // print Y’s var
	
	{ 							//just a normal block to be executed
		using Z::var;
		using Z::print;
		var = 11;
		print(); // print Z’s var
	}
	
	print(); // print Y’s var
	X::print(); // print X’s var
}
