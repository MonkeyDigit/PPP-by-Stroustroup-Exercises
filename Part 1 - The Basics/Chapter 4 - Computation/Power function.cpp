#include <iostream>
using namespace std;

//Funzione che calcola il quadrato di x senza usare moltiplicazioni
int power(int b,int e);

int main()
{
	int base,exp;
	
	cout<<"Inserisci la base: ";
	cin>>base;
	
	cout<<"Inserisci l'esponente: ";
	cin>>exp;
	
	cout<<'\n'<<base<<"^"<<exp<<" = "<<power(base,exp);
}
//IMPORTANTE:RICORDARE DI METTERE RETURN VALUE
int power(int b,int e)
{
	int power_b=b;
	int add_value=b;
	
	for(int i=0;i<e-1;i++)
	{
		for(int j=0;j<b-1;j++)
		{
			power_b+=add_value;
		}
		add_value=power_b;
	}
	if(e==0)
	{
		return 1;
	} else 
	{
	return power_b;
	}
	
}
