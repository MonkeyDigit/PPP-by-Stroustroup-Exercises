#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
using namespace std;

template<class It, class T>
It Binary_search(It first, It last, const T& val)
{
	It real_last = last;
	while(first != last)
	{
		It p = first + (last - first) / 2;
		
		if(*p == val)
			return p;
		
		if(*p < val && last != p+1)
			first = p;
		else if(val < *p)
			last = p;
		else
			break;
	}
	
	return real_last;
}

int main()
{
	srand(time(NULL));
	
	constexpr int arr_size = 10;
	int arr[arr_size];
	
	const int value_range = arr_size * 2;
	
	for(int i = 0; i < arr_size; ++i)
	{
		arr[i] = 0;
		int r{0};
		
		do
		{
			r = rand() % value_range + 1;
			
			arr[i] = r;
			for(int j = 0; j < arr_size; ++j)
			{
				if(r == arr[j] && j != i)
				{
					arr[i] = 0;
				}
			}
			
		} while(arr[i] != r);
		
	}
		
	sort(arr,arr+arr_size);
	
	cout << "Numbers in array:\n";
	for(int i = 0; i < arr_size; ++i)
		cout << arr[i] << '\n';
		
	const string yes_str = "YES";
	const string no_str = "NO";
	
	map<int,string> binary_search_map;
	
	cout << "\nIs this value contained? (normal binary search)\n";
	for(int i = 0; i < value_range; ++i)
	{
		cout << setw(2) << i << ": ";
		if(Binary_search(arr, arr + arr_size, i) != arr + arr_size)
		{
			cout << yes_str << '\n';
			binary_search_map.insert(make_pair(i, yes_str));
		}
		else
		{
			cout << no_str << '\n';
			binary_search_map.insert(make_pair(i, no_str));
		}
	}
	
	return 0;
}
