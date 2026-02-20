#include <iostream>
#include "Matrix.h"
using namespace Numeric_lib;
int main()
{
	Matrix<double> mat(10);
	for(int i=0;i<10;++i)
	{
		float val;
		std::cin>>val;
		mat[i]=val;
	}
	
	std::cout << '\n';
	for(int i=0;i<mat.dim1();++i)
	{
		std::cout << mat[i] << '\n';
	}
	return 0;
}
