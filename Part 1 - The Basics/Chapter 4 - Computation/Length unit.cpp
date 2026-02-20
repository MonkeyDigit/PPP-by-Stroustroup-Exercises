#include <iostream>
#include <windows.h>
using namespace std;
//IMPORTANTE:
//Assegnando un char ad un int, la variabile assumerà il valore ASCII di quel carattere
// se int x='|' x=124 ; se x='a' x=97;

// devo specificare 1.0/100 al posto di 1/100, per ottenere un risultato double
int main()
{
	double x=0;
	double max=0;
	double min;
	string unit="cm";
	int equal_c{1};
	int c{};
	
	while(x!='|' && unit!="|")
	{
		cout<<"1 m is equal to: \n"<<"100 cm\n"<<"39.3701 inches\n"<<"3.28084 feet\n";
		cout<<"\n1 cm is equal to: \n"<<"0.393701 inches\n"<<"0.0328084 feet\n"<<"0.01 m\n";
		cout<<"\n1 inch is equal to: \n"<<"2.54 cm\n"<<"0.0833333 feet\n"<<"0.0254 metres\n";
		cout<<"\n1 foot is equal to: \n"<<"30.48 cm\n"<<"12 inches\n"<<"0.3048 metres\n"<<"\n";
		
		cin>>x>>unit;
		system("cls");
		cout<<x<<" "<<unit<<"=\n";
		if(unit=="cm")
		{
			
			cout<<x/100<<" m\n";
			cout<<x/2.54<<" in\n";
			cout<<x/2.54/12<<" ft\n";
		} 
		else if(unit=="m")
		{
			cout<<x*100<<" cm\n";
			cout<<x/0.0254<<" in\n";
			cout<<x/0.0254/12<<" ft\n";
		}
		else if(unit=="in")
		{
			cout<<x*2.54<<" cm\n";
			cout<<x*0.0254<<" m\n";
			cout<<x/12<<" ft\n";
		}
		else if(unit=="ft")
		{
			cout<<x/0.0328084<<" cm\n";
			cout<<x/3.28084<<" m\n";
			cout<<x*12<<" in\n";
		}
	}
	
}
