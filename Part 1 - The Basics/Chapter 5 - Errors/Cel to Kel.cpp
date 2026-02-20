#include "std_lib_facilities.h"
constexpr double celkel_converter{273.15};


double ctok(double c) //Converts Celsius to Kelvin
{
	if(c < -celkel_converter) error("No temperature lower than absolute zero!");		//-273.15C= 0K, oltre questo limite non si può scendere, quindi stampa un errore
	double k=c+celkel_converter;
	return k;
}
double ktoc(double k)
{
	if(k<0) error("No temperature lower than absolute zero!");
	double c=k-celkel_converter;
	return c;
}

int main()
{
	double celsius{};
	double kelvin{};
	cout<<"Insert temperature in Celsius: ";
	cin>>celsius;
	/*Se l'input non è double, viene eseguita la funzione error, 
	che prende e stampa una stringa,il messaggio d'errore, e termina subito il programma.*/
	if(!cin) error("Couldn't read a double into celsius!");
	
	kelvin=ctok(celsius);
	cout<<celsius<<" C = "<<kelvin<<" K\n";
	
	cout<<"Insert temperature in Kelvin: ";
	cin>>kelvin;
	if(!cin) error("Couldn't read a double into kelvin!");
	
	celsius=ktoc(kelvin);
	cout<<kelvin<<" K = "<<celsius<<" C\n";
	
}
