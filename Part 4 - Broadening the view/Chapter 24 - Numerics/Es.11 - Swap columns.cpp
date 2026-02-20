#include <iostream>
#include "Matrix.h"
#include <iomanip>

using namespace Numeric_lib;

template<class T>
void swap_columns(Matrix<T,2>& m, int i, int j)
{
	if(i<0 || j<0)
	{
		std::cerr << "Negative column indexes\n";
		exit(1);
	}
	
	if(i>m.dim2()-1 || j>m.dim2()-1)
	{
		std::cerr << "Out of range column indexes\n";
		exit(1);
	}
	
	for(int row=0;row<m.dim1();++row)
	{
		T temp = m(row,i);
		m(row,i) = m(row,j);
		m(row,j) = temp;
	}
}

int main()
{
	Matrix<double,2> mat(3,4);
	
	for(int i=0;i<mat.dim1();++i)
	{
		for(int j=0;j<mat.dim2();++j)
		{
			mat(i,j) = j+i*mat.dim2()+1;
			std::cout << std::setw(3) << mat(i,j) << ' ';
		}
		std::cout << '\n';
	}
	
	swap_columns(mat,1,2);
	std::cout << "\nswap_columns(mat,1,2):\n";
	for(int i=0;i<mat.dim1();++i)
	{
		for(int j=0;j<mat.dim2();++j)
			std::cout << std::setw(3) << mat(i,j) << ' ';
			
		std::cout << '\n';
	}
	
	swap_columns(mat,0,3);
	std::cout << "\nswap_columns(mat,0,3):\n";
	for(int i=0;i<mat.dim1();++i)
	{
		for(int j=0;j<mat.dim2();++j)
			std::cout << std::setw(3) << mat(i,j) << ' ';
			
		std::cout << '\n';
	}
		
	return 0;
}
