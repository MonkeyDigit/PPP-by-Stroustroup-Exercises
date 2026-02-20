#include <iostream>
#include <iomanip>

int main()
{
	float x = 1.0/333;
	float sum = 0;
	for (int i=0; i<333; ++i) sum+=x;
	std::cout << std::setprecision(15) << sum << "\n";
	
	//weird
	float y = 1.0/10;
	sum = 0;
	for (int i=0; i<10; ++i) sum+=y;
	std::cout << std::setprecision(15) << sum << "\n";
	
	return 0;
}
