#include <iostream>
#include "Matrix.h"

using namespace Numeric_lib;

int main()
{
	//1.Print the size of a char, a short, an int, a long, a float, a double, 
	//an int*, and a double*
	std::cout << "1.Types size in bytes\n"
		<< "char:\t" << sizeof(char) << '\n'
		<< "short:\t" << sizeof(short) << '\n'
		<< "int:\t" << sizeof(int) << '\n'
		<< "long:\t" << sizeof(long) << '\n'
		<< "float:\t" << sizeof(float) << '\n'
		<< "double:\t" << sizeof(double) << '\n'
		<< "int*:\t" << sizeof(int*) << '\n'
		<< "double*:\t" << sizeof(double*) << '\n';
		
	//2.Print out the size as reported by sizeof of Matrix<int> a(10), 
	//Matrix<int>b(100), Matrix<double> c(10), Matrix<int,2> d(10,10), 
	//Matrix<int,3>e(10,10,10).
	Matrix<int> a(10);
	Matrix<int> b(100);
	Matrix<double> c(10);
	Matrix<int,2> d(10,10);
	Matrix<int,3>e(10,10,10);
	
	std::cout << "\n2.Size of matrixes\n"
		<< "Matrix<int> a(10):\t" << sizeof(a) << '\n'
		<< "Matrix<int> b(100):\t" << sizeof(b) << '\n'
		<< "Matrix<double> c(10):\t" << sizeof(c) << '\n'
		<< "Matrix<int,2> d(10,10):\t" << sizeof(d) << '\n'
		<< "Matrix<int,3> e(10,10,10):\t" << sizeof(e) << '\n';
		
	//3.Print out the number of elements of each of the Matrixes from 2.
	std::cout << "\n3.Number of elements in each matrix\n"
		<< "Matrix<int> a(10):\t" << a.size() << '\n'
		<< "Matrix<int> b(100):\t" << b.size() << '\n'
		<< "Matrix<double> c(10):\t" << c.size() << '\n'
		<< "Matrix<int,2> d(10,10):\t" << d.size() << '\n'
		<< "Matrix<int,3> e(10,10,10):\t" << e.size() << '\n';
	return 0;
}
