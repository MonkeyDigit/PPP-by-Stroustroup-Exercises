#include <iostream>
#include <complex>
#include "Matrix.h"

using namespace Numeric_lib;

int main()
{
	Matrix<int,2> mat(2,3);
	std::cout << "Please enter six integers: \n";
	for (int i=0;i<mat.dim1();++i)
		for(int j=0;j<mat.dim2();++j)
			std::cin>>mat(i,j);
	
	if(!std::cin)
	{
		std::cerr << "Bad input\n";
		exit(1);
	}
	
	std::cout << "Values: \n";
	for (int i=0;i<mat.dim1();++i)
	{
		for(int j=0;j<mat.dim2();++j)
			std::cout<<mat(i,j) << ' ';
		
		std::cout << '\n';
	}
	return 0;
}
