#include <iostream>
#include<windows.h>
using namespace std;
constexpr __int64 max_int{2147483647};
int main()
{
	cout<<max_int;
	__int64 num=2;
	int c{};
	/*
	do
	{
		c++;
		system("cls");
		cout<<num<<'\n'<<c;
		num*=2;	
		Sleep(250);
	}while(num);
	*/
	for(int i=0;i<63;i--)
	{
		system("cls");
		cout<<num<<'\n'<<i+1;
		num*=num;	
		Sleep(300);
	}
}
