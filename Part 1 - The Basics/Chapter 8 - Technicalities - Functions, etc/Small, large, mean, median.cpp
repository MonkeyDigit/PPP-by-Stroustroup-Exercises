#include "std_lib_facilities.h"
//function to find the smallest, the largest, the mean the median value in a vector
void small_larg_mm(vector<double>& v,double& sm, double& larg, double& mean, double& median);	//the results are passed by reference
void print(vector<double>& v)
{
	for(double x : v) cout<<x<<'\n';
}


int main()
{
	vector<double> v {3,1,4,5,2,6};
	double small{};
	double larg{};
	double mean{};
	double median{};
	
	print(v);
	
	small_larg_mm(v,small,larg,mean,median);
	cout<<"Smallest: "<<small<<'\n'
		<<"Largest: "<<larg<<'\n'
		<<"Mean: "<<mean<<'\n'
		<<"Median: "<<median<<'\n';
	return 0;
}

void small_larg_mm(vector<double>& v,double& sm, double& larg, double& mean, double& median)
{	//local variables
	double loc_small=v[0];
	double loc_max=0;
	double loc_mean=0;
	double loc_med=0;
	double sum=0;
	
	for(int i=0;i<v.size();i++)
	{
		if(v[i]<loc_small) loc_small=v[i];
		if(v[i]>loc_max) loc_max=v[i];
		sum+=v[i];
	}
	
	loc_mean=sum/v.size();	//the Mean = sum of the values / the number of values
	
	vector<double> loc_v=v;
	sort(loc_v);			//The median is the central element in a sorted set of numbers
	
	if(v.size() % 2 != 0)
		loc_med=loc_v[loc_v.size()/2];	//In this case (the number of elements is odd), i need to find the central element, which normally, would need to be
								//to be found by doing an integer division (loc_v.size/2) and add 1 (because it removes the decimal part), but since
								//a vector starts from 0, i won't need to add 1.
	//EXAMPLE: In a vector of five elements, the central element is the third, and if the elements start from 0 {0,1,2,3,4}, then it will go from 0 to 4
	//and the central element will be 2
	
	else if(v.size() % 2 == 0)						//If the number of elements is even, then i must calculate the median between the two elements closest
		loc_med=(loc_v[loc_v.size()/2-1]+loc_v[loc_v.size()/2])/2;	//to the center
	else 
		error("Impossible");
	
	sm=loc_small;
	larg=loc_max;
	mean=loc_mean;
	median=loc_med;
}
