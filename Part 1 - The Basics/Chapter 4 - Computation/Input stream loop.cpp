#include <iostream>
using namespace std;
//IMPORTANTE:
//Assegnando un char ad un int, la variabile assumerà il valore ASCII di quel carattere
// se int x='|' x=124 ; se x='a' x=97;

// devo specificare 1.0/100 al posto di 1/100, per ottenere un risultato double
int main()
{
	double x,y;
	int equal_c{1};
	
	cout<<"Inserisci dei valori\n";
	while(cin>>x>>y && x!='|' && y!='|')
	{	
		equal_c+=6;
		cout<<"x: "<<x<<"\ny: "<<y;
		cout<<'\n';
		if(x>y)
		{
			if(x-y<=1.0/100)
			{
				cout<<"x e' quasi uguale a y\n";
			}
			else
			{
				cout<<"x>y\n";
			}
			cout<<"diff: "<<x-y;
		} 
		else if(x<y)
		{
			if(y-x<=1.0/100)
			{
				cout<<"y e' quasi uguale a x\n";
			}
			else
			{
				cout<<"y>x\n";
			}
			cout<<"diff: "<<y-x;
		}
		 else
		{
			cout<<"x=y\n";
			cout<<"Riga: "<<equal_c-5;
		}
		cout<<'\n';
	}
	
}
