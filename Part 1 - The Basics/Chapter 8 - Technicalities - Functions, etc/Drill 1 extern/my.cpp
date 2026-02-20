#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 8 Drills\std_lib_facilities.h"
#include "my.h"
int foo;			//Even though foo was declared in my.h as an extern, it needs to be defined somewhere, but in this case we didn't need to assign
void print_foo()	//a value to it just yet
{
	std::cout << foo << std::endl;
}

void print(int i)
{
	std::cout << i << std::endl;
}
