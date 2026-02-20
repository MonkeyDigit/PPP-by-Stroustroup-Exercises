#include <iostream>
#include <vector>
using namespace std;

constexpr double cmax_temp=100;
constexpr double cmin_temp=-100;
/*Questa è la versione corretta del programma. Per evitare che venisserò registrate temperature massime 
e minime sbagliate, ho definito delle costanti, che hanno come valori delle temperature irraggiungibili (si spera) 
quindi tutte le temperature inserite, rientreranno in questo range (-100:100), permettendo la corretta rilevazione 
della temperatura minima e massima.
Come base quindi, max e min assumeranno questi valori*/
int main()
{
	vector<double>temps;
	
	for(double temp;cin>>temp;)
	{
		temps.push_back(temp);
	}
	
	double sum{};
	double min{cmax_temp};
	double max{cmin_temp};
	
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
