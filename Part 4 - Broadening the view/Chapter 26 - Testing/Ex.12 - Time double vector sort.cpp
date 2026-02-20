#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

int main()
{
	int vec_size = 500000;
	for(int i=0;i<2;++i)
	{
		std::vector<double> v;
		for(int j=0;j<vec_size;++j)
			v.push_back(rand() % vec_size);
		
		
		auto t1 = std::chrono::system_clock::now();
		
		std::sort(v.begin(),v.end());
		
		auto t2 = std::chrono::system_clock::now();
		
		std::cout << "Sorting " << vec_size << " elements: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
		<< " ms\n";
		
		vec_size*=10;
	}
	
	return 0;
}
