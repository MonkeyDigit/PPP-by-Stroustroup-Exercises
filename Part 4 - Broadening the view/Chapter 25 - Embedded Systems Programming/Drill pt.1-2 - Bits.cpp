#include <iostream>
using namespace std;

int main()
{
	//with a signed int
	int v = 1; 
	cout << "Left bitshifting on a signed integer for sizeof(int)*8 times:\n";
	for (int i = 0; i<sizeof(v)*8; ++i) 
	{
		cout << v << '\n'; v <<=1;
	}
	
	//note: the last number will be negative because signed integers reserve 1
	//bit for the sign. 0 = +;  1 = -;
	
	unsigned int uv = 1; 
	cout << "\nLeft bitshifting on an unsigned integer for sizeof(unsigned int)*8 times:\n";
	for (int i = 0; i<sizeof(uv)*8; ++i) 
	{
		cout << uv << '\n'; uv <<=1;
	}
	
	return 0;
}
