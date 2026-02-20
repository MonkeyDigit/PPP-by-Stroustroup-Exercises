#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 9 Drills\std_lib_facilities.h"
#include "Chrono.h"	//We are using the Chrono namespace, which implements a Date class
int main()
try
{
	Chrono::Date today{ 1978,6,25 };
	//Chrono::Date today{ 2020,2,29 }
	Chrono::Date tomorrow{ today };
	tomorrow.add_day(1);
	cout << "today: " << today << '\n';
	cout << "tomorrow: " << tomorrow << '\n';

	//Chrono::Date test_day{ -1978,6,25 };
	//Chrono::Date test_day{ 1978,-6,25 };
	//Chrono::Date test_day{ 1978,6,-25 };
	//Chrono::Date test_day{ 1978,13,25 };
	//Chrono::Date test_day{ 1978,12,33 };
	//Chrono::Date test_day{ 1980,2,29 };
	//Chrono::Date test_day{ 1981,2,29 };
	//Chrono::Date test_day{ 2022,12,9 };

	today.add_day(38);
	cout << today << '\n';
	return 0;
}

catch (Chrono::Date::Invalid) {							//catch any exception thrown by the try block
	error("Invalid date");
	return 1;
}

catch (exception& e) {							//catch any exception thrown by the try block
	cerr << "exception: " << e.what() << '\n';
	return 2;
}

catch (...) {				//catch unknown exceptions
	cerr << "exception\n";
	return 3;
}

//TEST FEB 29 IN ADD MONTH
//CHECK CASTING IN DAY WEEK