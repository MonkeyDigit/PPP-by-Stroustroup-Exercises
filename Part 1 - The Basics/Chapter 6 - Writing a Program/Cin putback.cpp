#include "std_lib_facilities.h"

int main()
{
	char ch;
	cin>>ch;
	
	cin.putback(ch);	//rimetto ch nello stream input, e quando arriva l'inserimento di val, viene fatto automaticamente
	double val;			//perchè val assume il valore buffer, che ha la precedenza, che appunto era ch.
	cin>>val;			//se inserisco un numero, ch assumerà la sua prima cifra mentre val il numero intero. Se metto un valore non rappresentabile
						//da val, quest'ultimo assumerà come valore 0
	cout<<"ch: "<<ch<<"\nval: "<<val<<'\n';
	return 0;
}
