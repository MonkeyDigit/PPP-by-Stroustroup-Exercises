#include <iostream>
#include <random>

int randint(int min, int max)
{ 
	static std::default_random_engine ran;
	return std::uniform_int_distribution<>{min,max}(ran);
}

int main()
{
	int n,d;
	std::cout << "Enter the value range ([0,n]) and number of draws: ";
	std::cin >> n >> d;
	
	if(!std::cin)
	{
		std::cerr << "Bad input";
		exit(1);
	}
	
	if(!n || !d)
	{
		std::cerr << "Non positive number";
		exit(2);
	}
	
	std::cout << "\nValues drawn:\n";
	for(int i=0;i<d;++i)
		std::cout << randint(0,n) << '\n';
	
	return 0;
}
