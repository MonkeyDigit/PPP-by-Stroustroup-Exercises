#include <iostream>
using namespace std;

//Funzione che calcola il quadrato di x senza usare moltiplicazioni
int square(int b);

int main()
{
	int base;
	cout<<"Inserisci la base: ";
	cin>>base;
	
	cout<<'\n'<<base<<"^2 = "<<square(base);
}
//IMPORTANTE:RICORDARE DI METTERE RETURN VALUE
int square(int b)
{
	int square_b=0;
	
	for(int i=0;i<b;i++)
	{
		square_b+=b;
	}
	return square_b;
	
	
}
