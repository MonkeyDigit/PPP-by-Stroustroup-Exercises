#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

int main()
{
	srand(time(nullptr));
	
	constexpr int ascii_characters = 128;
	constexpr int str_length_range=100;
	int vec_size = 500000;
	
	for(int i=0;i<2;++i)
	{
		std::vector<std::string> v;
		for(int j=0;j<vec_size;++j)
		{
			int str_length = rand()%str_length_range;
			std::string s{""};
			
			for(int k=0;k<str_length;++k)
				s+= rand()%ascii_characters;
				
			v.push_back(s);
		}
		
		
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
