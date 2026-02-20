#include "std_lib_facilities.h"

int main()
{
	int birth_year {2005};
	/*
	cout  << birth_year << "\t(decimal)" << '\n' 
	<< hex << birth_year << "\t(hexadecimal)" << '\n'
	<< oct << birth_year << "\t(octal)"<< '\n';
	*/
	//showbase sticks, so it remains enabled as long as we don't disable it
	cout  << showbase << birth_year << "\t(decimal)" << '\n' 
	<< hex << birth_year << "\t(hexadecimal)" << '\n'
	<< oct << birth_year << "\t(octal)"<< '\n';
	int age {17};
	//the base change done by the manipulator remains enabled
	//cout <<age<<'\n';
	cout << noshowbase << dec << age <<'\n';
	/*
	int a,b,c,d;
	//cin>>2005	2005	2005	2005
	//cin>>1234 4d2 2322 2322
	cin >> a >> oct >> b >> hex >> c >> d;
	//cout<<2005    1029    8197    8197
	//cout<<1234	1234	1234	1234
	cout << a << '\t'<< b << '\t'<< c << '\t'<< d << '\n' ; //we input a,b,c,d as decimal, octal, and hexadecimal ints, but since the output is decimal,
	//this will print out the values in decimal base
	*/
	
	//NOTE:won't compile because devc++ doesn't include defaultfloat, but visual studio does
	cout << defaultfloat << 1234567.89 <<"\t(defaultfloat)\n"
		<< fixed << 1234567.89 << "\t(fixed)\n"
		<< 1234567.89 << "\t(scientific)\n"
		<< scientific << 1234567.89 << "\t(scientific)\n";
	
	cout << setw(7) << "Fadda" << '|' << setw(7) << "Marco" << '|' << setw(12) << "976955436228" << '|' << setw(23) << "marcofadda@gmail.com" << "|\n"
		 << setw(7) << "Rossi" << '|' << setw(7) << "Mario" << '|' << setw(12) << "764272937528" << '|' << setw(23) << "mariorossi@gmail.com" << "|\n"
		 << setw(7) << "Bianchi" << '|' << setw(7) << "Andrea" << '|' << setw(12) << "289752533425" << '|' << setw(23) << "andreabianchi@gmail.com" << "|\n"
		 << setw(7) << "Sanna" << '|' << setw(7) << "Antonio" << '|' << setw(12) << "628756532399" << '|' << setw(23) << "antoniosanna@gmail.com" << "|\n"
		 << setw(7) << "Biagi" << '|' << setw(7) << "Stefano" << '|' << setw(12) << "387112459674" << '|' << setw(23) << "stefanobiagi@gmail.com" << "|\n";
	return 0;
}
