#include <iostream>
#include "Matrix.h"
#include <iomanip>
using namespace Numeric_lib;

int main()
{
	int m,n;
	std::cout << "Enter the dimensions of the table (height,width): ";
	std::cin>>m>>n;
	
	if(!std::cin)
	{
		std::cerr<<"Bad input\n";
		exit(1);
	}
	
	Matrix<int,2> mult_table(m,n);
	
	std::cout << '\n';
	
	for(int i=0;i<m;++i)
		for(int j=0;j<n;++j)
			mult_table(i,j) = (i == 0 || j == 0) ? (i + j) : (i * j);
	
	for(int i=0;i<m;++i)
	{
		for(int j=0;j<n;++j)
			std::cout << std::setw(5) << mult_table(i,j);
			
		std::cout << "\n\n";
	}
	return 0;
}
