#include <iostream>
#include <vector>
#include <chrono>
#include "Matrix.h"

using namespace Numeric_lib;

double row_sum(Matrix<double,2> m, int n) // sum of elements in m[n]
{
	double s{0};
	for(int i=0;i<m.dim2();++i)
		s+=m(n,i);
	return s;
}

double row_accum(Matrix<double,2> m, int n) // sum of elements in m[0:n)
{
	double s = 0;
	for (int i=0; i<n; ++i)
		s+=row_sum(m,i);
	return s;
}


int main()
{
	int mat_size{100};
	while(true)
	{
		Matrix<double,2> mat (mat_size,mat_size);
		
		//generate random numbers
		for(int j=0;j<mat.dim1();++j)
		{
			for(int k=0;k<mat.dim2();++k)
				mat(j,k) = (rand() % 20) - 10;
		}
		
		// compute accumulated sums of rows of m:
		std::vector<double> v;
		
		auto t1 = std::chrono::system_clock::now();
		
		//very slow
		/*
		for (int i = 0; i<mat.dim1(); ++i)
		{
			v.push_back(row_accum(mat,i+1));
		}
		*/
		
		//much faster
		/*
		*/
		v.push_back(row_sum(mat,0));
		for (int i = 1; i<mat.dim1(); ++i)
			v.push_back(row_sum(mat,i)+v[v.size()-1]);
			
		auto t2 = std::chrono::system_clock::now();
		
		std::cout << "Sum of " << mat_size*mat_size << " values: " 
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() 
		<< " ms\n";
		
		mat_size*=2;
	}
}
