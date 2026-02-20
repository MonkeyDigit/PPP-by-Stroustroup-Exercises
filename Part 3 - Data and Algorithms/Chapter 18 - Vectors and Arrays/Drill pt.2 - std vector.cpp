#include "std_lib_facilities.h"

vector<int> gv {1,2,4,8,16,32,64,128,256,512};

void f(const vector<int>& v)	//we just read the vector, and we pass it by reference
{
	vector<int> lv(v.size());
	
	for(int i=0;i<gv.size();++i)
		lv[i] = gv[i];
	
	for(int i=0; i<lv.size();++i)
		cout << lv[i] << '\n';
	
	vector<int> lv2 = v;
	
	for(int i=0; i<lv2.size();++i)
		cout << lv2[i] << '\n';
}

int main()
try
{
	f(gv);
	vector<int> vv;
	for(int i=0;i<10;++i)
	{
		int fac{1};
		for(int j=i+1;j>1;--j)
			fac*=j;
		vv.push_back(fac);
	}
	
	f(vv);
	
	return 0;
}

catch(exception& e)
{
	cerr<<"error: "<<e.what()<<'\n';
	keep_window_open();
	return 1;
}

catch(...)
{
	cerr<<"Unknown exception\n";
	keep_window_open();
	return 2;
}
