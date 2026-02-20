#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

template<class Iter, class T, class Cmp>
bool Binary_search(Iter first, Iter last, const T& val, Cmp cmp)
{
	while(first != last)
	{
		Iter p = first + (last - first) / 2;
		
		if(*p == val)
			return true;
		
		if(cmp(*p,val) && last != p+1)
			first = p;
		else if(cmp(val,*p))
			last = p;
		else
			break;
	}
	
	return false;
}

template<class T>
struct Test
{
	string label;
	T val;
	int seq_index;
	bool res;
};

//i made it so that if the input fails, the Test variable isn't modified
template<class T>
istream& operator>>(istream& is, Test<T>& t)
{
	char ch1, ch2;
	string lab;
	T val;
	string seq_code;
	bool res;
	
	is >> ch1 >> lab >> val >> seq_code >> res >> ch2;
	
	if(!is)
		return is;
	
	if(ch1 != '{' || 
		ch2 != '}' ||
		seq_code[0] != 's' ||
		!isdigit(seq_code[1]) ||
		seq_code.length() > 2)
	{
		is.clear(ios_base::failbit);
		return is;
	}
	
	int i = (seq_code[1] - 48) - 1;
	
	if(i<0)
	{
		is.clear(ios_base::failbit);
		return is;
	}
	
	t.label = lab;
	t.val = val;
	t.seq_index = i;
	t.res = res;
	
	return is;
}

template<class T>
ostream& operator<<(ostream& os, const Test<T>& t)
{
	os << "{ " << t.label << ' ' << t.val << " { ";
	
	for(const T& t : t.seq)
		os << t << ' ';
	
	os << "} " << t.res << " } ";
	
	return os;
}

template<class T>
istream& operator>>(istream& is, vector<T>& vec)
{
	char ch;
	
	is >> ch;
	
	if(!is)
		return is;
	if(ch != '{')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	
	while(true)
	{
		is >> ch;
		
		if(!is || ch == '}')
			return is;
		
		is.unget();
		
		T t;
		
		is >> t;
		
		if(!is)
			return is;
		
		vec.push_back(t);
	}
	
	return is;
}

int test_all(istream& is)
{
	int error_count{0};
	
	vector<vector<int>> sequences;
	
	is >> sequences;
	
	if(!is)
		throw runtime_error("Bad sequence input");
	
	for(Test<int> t; is>>t;)
	{
		bool r = Binary_search(sequences[t.seq_index].begin(), sequences[t.seq_index].end(), t.val, [](const int a, const int b){return a<b;});
		
		if(r != t.res)
		{
			cout << "failure: test " << t.label << " Binary_search: "
				<< sequences[t.seq_index].size() << " elements ( ";
			
			for(const int& n : sequences[t.seq_index])
				cout << n << ' ';
				
			cout << "), val == " << t.val << " -> " << t.res << '\n';
			++error_count;
		}
	}
	return error_count;
}

int main()
try
{
	ifstream ifs {"my_tests3.txt"};
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
