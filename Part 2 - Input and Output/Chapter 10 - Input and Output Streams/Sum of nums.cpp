#include "std_lib_facilities.h"

int main()
{
	int sum {}; //sum initialized to 0
	string iname="nums.txt"; //the file name
	ifstream ist {iname}; //insert in the input file stream the contents of the file nums.txt
	if(!ist) error("Couldn't open file ",iname);
	
	//Note the ist (variable of type ifstream declared earlier) instead of cin, this means that 
	//the input is taken from the input file stream directly instead of user input
	for(int n;ist>>n;)
	{
		cout << n <<' ';
		sum+=n;
	}
	
	//The input will terminate depending on its state:
	//good() - Operations succeded
	//eof()  - We hit end of input (“end of file”).
	//fail() - Something unexpected happened (e.g., we looked for a digit and found 'x')
	//bad()  - Something unexpected and serious happened (e.g., a disk read error).
	
	//if, for example, inside of nums.txt is written  5 6 b 8  - Since b is a character and not an integer, the input will terminate with state fail()
	//however nothing will be done unless we make a block to handle the fail state, so the program will continue and sum will be equal to 11
	
	if(!ist) //ist is not good()
	{
		if (ist.bad()) error("cin is bad"); // stream corrupted: let’s get out of here!
		if (ist.eof())
		{
			// no more input
			// this is often how we want a sequence of input operations to end
		}
		if (ist.fail()) 
		{ // stream encountered something unexpected
			error("Fail - wrong type");
			//ist.clear(); // make ready for more input
			// somehow recover
		}
	}
	cout<<"\nSum: "<<sum<<'\n';
	return 0;
}
