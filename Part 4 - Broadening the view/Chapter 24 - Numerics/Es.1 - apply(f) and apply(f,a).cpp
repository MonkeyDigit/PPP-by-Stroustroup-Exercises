#include <iostream>
#include "Matrix.h"
using namespace Numeric_lib;

void triple_a(int& a)
{a*=3;}

int triple_b(int a)
{return a*3;}

//not used
void triple_c(int& a,const int b)
{a=b*3;}

int main()
{
	Matrix<int> mat1(5);
	Matrix<int> mat2(5);
	
	std::cout << "mat1:\n";
	for(int i=0;i<5;++i)
	{
		mat1(i)=i+1;
		std::cout << mat1(i) << '\n';
	}
	
	std::cout << "\nmat1.apply(triple_a):\n";
	//with a lambda expression
	//mat1.apply([](int& a){a*=3;});
	mat1.apply(triple_a);
	
	for(int i=0;i<mat1.dim1();++i)
		std::cout << mat1(i) << '\n';
		
	std::cout << "\nmat2 = apply(triple_b,mat1):\n";
	mat2 = apply(triple_b,mat1);
	for(int i=0;i<mat2.dim1();++i)
		std::cout << mat2(i) << '\n';
	return 0;
}
