#include "std_lib_facilities.h"
#include "mycalc.h"

//MAIN--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int main()			//when there is only one function (try{}), {} are not needed. REMEMBER: when they are not put, the function executes ONLY the first one block
{
	Token_stream ts;
	try {				//this applies to loops as well
		cout << "Welcome to our simple calculator!\nPlease enter a statement. \n"
			<< "Enter " << quitkey << " to exit, and " << print << " to end an insertion. \n"
			<< "To read the complete instructions, enter: '" << helpkey << "'. \n";
		while (true)
		{
			cout << prompt;
			Token t = ts.get();
			while (t.kind == print) t = ts.get();
			if (t.kind == quit) break;
			else if (t.kind == help) instructions();
			else
			{
				ts.unget(t);
				calculate(ts);
			}
		}
		return 0;
	}
	catch (exception& e) {							//catch any exception thrown by the try block
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >> c && c != ';');				//eats all characters different from ';', if ';' exit
		return 1;
	}
	catch (...) {				//catch unknown exceptions
		cerr << "exception\n";
		char c;
		while (cin >> c && c != ';');
		return 2;
	}
}

//--------------------------------------------------------------------------------------------