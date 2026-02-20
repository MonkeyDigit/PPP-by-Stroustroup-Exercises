#include <iostream>
using namespace std;
//IMPORTANTE:
//Assegnando un char ad un int, la variabile assumerà il valore ASCII di quel carattere
// se int x='|' x=124 ; se x='a' x=97;

// devo specificare 1.0/100 al posto di 1/100, per ottenere un risultato double
int main()
{
	double x;
	double max=0;
	double min;
	int equal_c{1};
	int c{};
	
	cout<<"Inserisci dei valori\n";
	while(cin>>x && x!='|')
	{
		if(c==0)
		{
			min=x;
		}
		if(x>max)
		{
			cout<<"\nNumero piu' grande mai inserito: "<<x;
			max=x;
		}
		if(x<min)
		{
			cout<<"\nNumero piu' piccolo mai inserito: "<<x;
			min=x;
		}
		cout<<'\n';
		c++;
	}
	
}
