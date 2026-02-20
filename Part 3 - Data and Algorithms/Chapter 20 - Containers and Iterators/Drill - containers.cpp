#include "std_lib_facilities.h"

template<typename Iter1, typename Iter2>
// requires Input_iterator<Iter1>() && Output_iterator<Iter2>()
Iter2 my_copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	for(Iter1 p=f1; p!=e1; ++p)
	{	//it first assigns *p to *f2, then it increases the iterator f2
		*f2++ = *p;
	}
	
	return f2;
}

int main()
try
{	//we can do: int a1[10];  but we can also omit the array size
	int a1[] 		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };	
	vector<int> v1 	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	list<int> l1 	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	//we can't initialize an array by copy
	int a2[10];
	for(int i=0;i<10;++i)
		a2[i]=a1[i];
	vector<int> v2=v1;
	list<int> l2=l1;
	
	//increase each element in the array by 2
	//in the vector by 3
	//in the list by 5
	cout << "a1:\n";
	for(int& n : a1)
	{
		n+=2;
		cout << n << '\n';
	}
	
	cout << "v1:\n";
	for(int& n : v1)
	{
		n+=3;
		cout << n << '\n';
	}
	
	cout << "l1:\n";
	for(int& n : l1)
	{
		n+=5;
		cout << n << '\n';
	}
	
	my_copy(a1, a1+10,v1.begin());
	
	cout << "\nmy_copy(a1, a1+10,v1.begin()); v1:\n";
	for(int& n : v1)
	{
		cout << n << '\n';
	}
	
	my_copy(l1.begin(), l1.end(), a1);
	
	cout << "\nmy_copy(l1.begin(), l1.end(), a1); a1:\n";
	for(int& n : a1)
	{
		cout << n << '\n';
	}
	
	//if the value isn't found, find() will return v1.end()
	//by the way, we could have avoided writing vector<int>::iterator by simply using auto
	vector<int>::iterator v_iter = std::find(v1.begin(),v1.end(),3);
	if(v_iter != v1.end())
		cout << "\nfind(v1.begin(),v1.end(),3); position: " << v_iter-v1.begin() << '\n';
	else
		cout << "\nfind(v1.begin(),v1.end(),3); value not found!\n";
		
	list<int>::iterator l_iter = std::find(l1.begin(), l1.end(),27);
	if(l_iter != l1.end())
	{
		int index{0};
		for(auto p=l_iter;p!=l1.begin();--p)
			index++;
		cout << "\nfind(l1.begin(),l1.end(),27); position: " << index << '\n';
	}
	else
		cout << "\nfind(l1.begin(),l1.end(),27); value not found!\n";
	
	return 0;
}
catch(exception& e)
{
	cerr << "Exception: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
