#include "std_lib_facilities.h"
double calc_index(vector<double>&,vector<double>&);	//takes 2 vectors argument, price and weight

int main()
{
	vector<double> price;
	vector<double> weight;
	double index{0};		// index= sum of all (price*weight)
	
	cout<<"Enter price and weight\n";
	while(true)
	{
		double p;
		double w;
		cout<<"Price: $"; cin>>p;
		cout<<"Weight: "; cin>>w;
		
		if(p==0 || w==0) break;
		else
		{
			price.push_back(p);
			weight.push_back(w);
		}
	}
	
	index=calc_index(price,weight);
	cout<<"Index (Assets value): $"<<index<<'\n';
	
	return 0;
}

double calc_index(vector<double>& p,vector<double>& w)
{
	double tot{};
	for(int i=0;i<p.size();i++)
	{
		tot+=p[i]*w[i];
	}
	return tot;
}
