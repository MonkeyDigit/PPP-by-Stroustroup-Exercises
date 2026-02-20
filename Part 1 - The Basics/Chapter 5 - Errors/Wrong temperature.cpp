#include <iostream>
#include <vector>
using namespace std;
//Questo programma non funziona, perchè inizializzando max e min con '0',
//se la temperatura minima è maggiore di 0, verrà comunque segnata come 0
//se la temperatura massima è minore di 0 (posti freddi), verrà segnata come 0
int main()
{
	vector<double>temps;
	
	for(double temp;cin>>temp;)
	{
		temps.push_back(temp);
	}
	
	double sum{};
	double min{};
	double max{};
	
	for(double x:temps)
	{
		if(x>max)
		{
			max=x;
		}
		if(x<min)
		{
			min=x;
		}
		sum+=x;
	}
	
	cout<<"Max temp: "<<max<<"\n";
	cout<<"Min temp: "<<min<<"\n";
	cout<<"Average temp: "<<sum/temps.size()<<"\n";
}
