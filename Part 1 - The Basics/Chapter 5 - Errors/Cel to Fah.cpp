#include "std_lib_facilities.h"


double ctof(double c) //Converts Celsius to Fahrenheit
{
	double f=c*9/5+32;
	return f;
}
double ftoc(double f)
{
	double c=(f-32)*5/9;
	return c;
}

int main()
{
	double celsius{};
	double fahrenheit{};
	cout<<"Insert temperature in Celsius: ";
	cin>>celsius;
	/*Se l'input non è double, viene eseguita la funzione error, 
	che prende e stampa una stringa,il messaggio d'errore, e termina subito il programma.*/
	if(!cin) error("Couldn't read a double into celsius!");
	
	fahrenheit=ctof(celsius);
	cout<<celsius<<" C = "<<fahrenheit<<" F\n";
	
	cout<<"Insert temperature in Fahrenheit: ";
	cin>>fahrenheit;
	if(!cin) error("Couldn't read a double into fahrenheit!");
	
	celsius=ftoc(fahrenheit);
	cout<<fahrenheit<<" F = "<<celsius<<" C\n";
	
}
