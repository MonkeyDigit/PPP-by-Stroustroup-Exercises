#include <iostream>
#include <complex>
#include "Matrix.h"

using namespace Numeric_lib;

using cmplx = std::complex<double>;

int main()
{
	Matrix<cmplx> complex_matrix(10);
	std::cout << "Please enter ten complex<double> (r,i): \n";
	for (int i=0;i<10;++i)
	{
		std::cin>>complex_matrix(i);
	}
	
	if(!std::cin)
	{
		std::cerr << "Bad input\n";
		exit(1);
	}
	
	cmplx sum{};
	
	for (int i=0;i<10;++i)
	{
		sum+=complex_matrix(i);
	}
	std::cout << "Sum: " << sum << '\n';
	return 0;
}
