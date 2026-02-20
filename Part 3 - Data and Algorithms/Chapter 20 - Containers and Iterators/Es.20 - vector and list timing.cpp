#include "std_lib_facilities.h"
#include <chrono>

void make_vector(const int n)
{
	srand(time(NULL));
	vector<int> v1;
	for(int i=0;i<n;++i)
	{
		int rand_num=rand()%n;
		auto it=v1.begin();
		while(it!=v1.end())
		{
			if(rand_num<=*it)
			{
				v1.insert(it,rand_num);
				break;
			}
			++it;
		}
		
		if(it==v1.end()) v1.push_back(rand_num);
	}
}

void make_list(const int n)
{
	srand(time(NULL));
	list<int> l1;
	for(int i=0;i<n;++i)
	{
		int rand_num=rand()%n;
		auto it=l1.begin();
		while(it!=l1.end())
		{
			if(rand_num<=*it)
			{
				l1.insert(it,rand_num);
				break;
			}
			++it;
		}
		
		if(it==l1.end()) l1.push_back(rand_num);
	}
}

int main()
try
{
	int n_elems{0};
	while(true)
	{
		n_elems+=3000;
		auto tv1 = chrono::system_clock::now(); // begin time
		make_vector(n_elems);
		auto tv2 = chrono::system_clock::now(); // end time
		
		int vec_time=chrono::duration_cast<chrono::milliseconds>(tv2-tv1).count();
		cout << "making the vector took " << vec_time << " milliseconds\n";
		
		auto tl1 = chrono::system_clock::now(); // begin time
		make_list(n_elems);
		auto tl2 = chrono::system_clock::now(); // end time
		
		int list_time=chrono::duration_cast<chrono::milliseconds>(tl2-tl1).count();
		cout << "making the list took " << list_time << " milliseconds\n\n";
		
		if(vec_time<list_time)
			break;
	}
	
	cout << "List is faster when using less than around " << n_elems << " elements\n";
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
