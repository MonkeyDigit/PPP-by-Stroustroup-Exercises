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
	vector<T> seq;
	bool res;
};

//i made it so that if the input fails, the Test variable isn't modified
template<class T>
istream& operator>>(istream& is, Test<T>& t)
{
	char ch1, ch2;
	string lab;
	T val;
	vector<T> seq;
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
		
		T t;
		is >> t;
		
		if(!is)
		{
			is.clear(ios_base::failbit);
			return is;
		}
		
		seq.push_back(t);
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

template<class T>
ostream& operator<<(ostream& os, const Test<T>& t)
{
	os << "{ " << t.label << ' ' << t.val << " { ";
	
	for(const T& t : t.seq)
		os << t << ' ';
	
	os << "} " << t.res << " } ";
	
	return os;
}

bool compare_strings(const string& a, const string& b)
{
	
	for(int i=0; i<a.length();++i)
	{
		if(i < b.length())
		{
			if(tolower(a[i]) < tolower(b[i]))
				return true;
			else
				return false;
		}
		else
			return false;
	}
	
	return false;
}

int test_all(istream& is)
{
	int error_count{0};
	
	for(Test<string> t; is>>t;)
	{
		//bool r = Binary_search(t.seq.begin(),t.seq.end(),t.val, [](const string& a, const string& b) { return a<b;});
		bool r = Binary_search(t.seq.begin(),t.seq.end(),t.val, compare_strings);
		
		if(r != t.res)
		{
			cout << "failure: test " << t.label << " Binary_search: "
				<< t.seq.size() << " elements ( ";
			
			for(const string& s : t.seq)
				cout << s << ' ';
				
			cout << "), val == " << t.val << " -> " << t.res << '\n';
			++error_count;
		}
	}
	return error_count;
}

int main()
try
{
	ifstream ifs {"my_tests2.txt"};
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
