#include "std_lib_facilities.h"

template<typename T, typename U>
class Pair{
public:
	Pair(T label, U value): t(label), u(value) {}
	T label() const { return t; };
	U value() const { return u; };
private:
	T t;
	U u;	
};

int main()
try
{
	vector<Pair<string,double>> symbol_table;
	
	symbol_table.push_back({"PI", 3.14159});
	symbol_table.push_back({"e", 2.71828});
	
	for(int i=0;i<symbol_table.size();++i)
		cout<<symbol_table[i].label()<<": "<<symbol_table[i].value()<<'\n';
		
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
	cerr<<"Unknown error\n";
	keep_window_open();
	return 2;
}
