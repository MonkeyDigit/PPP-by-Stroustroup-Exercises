#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

template<class Iter, class T>
bool Binary_search(Iter first, Iter last, const T& val)
{
	while(first != last)
	{
		Iter p = first + (last - first) / 2;
		
		if(*p == val)
			return true;
		
		if(*p < val && last != p+1)
			first = p;
		else if(val < *p)
			last = p;
		else
			break;
	}
	
	return false;
}

struct Test
{
	string label;
	int val;
	vector<int> seq;
	bool res;
};

//i made it so that if the input fails, the Test variable isn't modified
istream& operator>>(istream& is, Test& t)
{
	char ch1, ch2;
	string lab;
	int val;
	vector<int> seq;
	bool res;
	
	is >> ch1 >> lab >> val >> ch2;
	
	if(!is)
		return is;
		
	if(ch1 != '{' || ch2 != '{')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	
	for(char ch; is >> ch;)
	{
		if(ch == '}')	// the sequence ends
			break;
		
		is.unget();
		
		int n;
		is >> n;
		
		if(!is)
		{
			is.clear(ios_base::failbit);
			return is;
		}
		
		seq.push_back(n);
	}
	
	if(!is)
		return is;
	
	is >> res >> ch2;
	
	if(!is)
		return is;
	
	if(ch2 != '}')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	
	t.label = lab;
	t.val = val;
	t.seq = seq;
	t.res = res;
	
	return is;
}

ostream& operator<<(ostream& os, const Test& t)
{
	os << "{ " << t.label << ' ' << t.val << " { ";
	
	for(const int n : t.seq)
		os << n << ' ';
	
	os << "} " << t.res << " } ";
	
	return os;
}

int test_all(istream& is)
{
	int error_count{0};
	
	for(Test t; is>>t;)
	{
		bool r = Binary_search(t.seq.begin(),t.seq.end(),t.val);
		
		if(r != t.res)
		{
			cout << "failure: test " << t.label << " Binary_search: "
				<< t.seq.size() << " elements, val==" << t.val 
				<< "-> " << t.res << '\n';
			++error_count;
		}
	}
	return error_count;
}

int main()
try
{
	ifstream ifs {"my_tests.txt"};
	if(!ifs)
	{
		throw runtime_error("Couldn't open input file\n");
	}
	
	int errors = test_all(ifs);
	
	cout << "number of errors: " << errors << '\n';
		
	return 0;
}
catch(exception& e)
{
	cerr << "Error: " << e.what() << '\n';
	exit(1);
}
catch(...)
{
	cerr << "Unknown exception\n";
	exit(2);
}
