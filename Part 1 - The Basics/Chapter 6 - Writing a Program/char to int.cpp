#include "std_lib_facilities.h"

int main()
{
	char ch;
	vector<char> ch_num;
	int num{};
	while (cin)
	{
		cin>>ch;
		if(ch=='x') break;
		ch_num.push_back(ch);
	}
	
	int exp=ch_num.size();
	for(int i=0;i<ch_num.size();i++)
	{
		exp--;
		num=num+(ch_num[i]-'0')*pow(10,exp);
		cout<<(ch_num[i]-'0')*pow(10,exp)<<'\n';
	}
	return 0;
}
