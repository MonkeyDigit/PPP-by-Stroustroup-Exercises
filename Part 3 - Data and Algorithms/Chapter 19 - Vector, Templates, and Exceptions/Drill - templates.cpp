#include "std_lib_facilities.h"

template<typename T> 
struct S {
	explicit S(T value): val{value} {}
	T& get();
	//void set(const T& v);
	T& operator=(const T&);
	const T& get() const;
private:
	T val;
};

template<typename T> 
T& S<T>::get()
{
	return val;
}

/*
template<typename T> 
void S<T>::set(const T& v)
{
	val = v;	
}
*/

template<typename T> 
T& S<T>::operator=(const T& v)
{
	val = v;
	return *this;
}

template<typename T> 
const T& S<T>::get() const
{
	return val;
}

template<typename T>
 void read_val(T& v)
{
	cin>>v;
}

template<typename T>
istream& operator>>(istream& is, vector<T>& vec)
{
	char ch;
	is >> ch; // '{'
	
	if(ch!='{')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	
	for(T val; is>>val;)
	{
		vec.push_back(val);
		is>>ch;
		if(ch == '}') break;
		if(ch != ',')
		{
			is.clear(ios_base::failbit);
			return is;
		}
		
		
	}
	
	if(!is)
	{
		return is;
	}
	
	return is;
}

template<typename T> 
ostream& operator<<(ostream& os, const vector<T>& vec)
{
	os << "{ ";
	for(int i=0;i<vec.size();++i)
	{
		os << vec[i];
		if(i<vec.size()-1)
			os << ", ";
	}
	
	os << '}';
	return os;
}

int main()
try
{
	//variables initialized
	/*
	S<int> s1{1};
	S<double> s2{1.5};
	S<char> s3{'a'};
	S<string> s4{"Hello World!"};
	
	vector<int> vec{1,2};
	S<vector<int>> s5{vector<int>{1,2}};
	*/
	
	//print the values with val
	/*
	cout << s1.val << '\n'
		<< s2.val << '\n'
		<< s3.val << '\n'
		<< s4.val << '\n';
	
	for(int& v : s5.val)
		cout << v << '\n';
	*/
	
	//print the values with get()
	/*
	cout << s1.get() << '\n'
		<< s2.get() << '\n'
		<< s3.get() << '\n'
		<< s4.get() << '\n';
	
	for(int& v : s5.get())
		cout << v << '\n';
	*/
	
	S<int> s1{0};
	S<double> s2{0};
	S<char> s3{0};
	S<string> s4{""};
	//S<vector<int>> s5 {vector<int>{1,2}};
	S<vector<int>> s5{vector<int>{}};
	
	read_val(s1.get());
	read_val(s2.get());
	read_val(s3.get());
	read_val(s4.get());
	read_val(s5.get());
	
	cout << s1.get() << '\n'
		<< s2.get() << '\n'
		<< s3.get() << '\n'
		<< s4.get() << '\n';
	
	cout << s5.get()<<'\n';
	
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
