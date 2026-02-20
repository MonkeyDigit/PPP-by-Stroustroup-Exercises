#include <iostream>
#include <map>
#include <chrono>
#include <algorithm>

int main()
{
	srand(time(nullptr));
	
	constexpr int ascii_characters = 128;
	constexpr int str_length_range=100;
	int map_size = 500000;
	
	for(int i=0;i<2;++i)
	{
		std::map<int,std::string> m;
		
		auto t1 = std::chrono::system_clock::now();
		
		for(int j=0;j<map_size;++j)
		{
			int str_length = rand()%str_length_range;
			std::string s{""};
			
			for(int k=0;k<str_length;++k)
				s+= rand()%ascii_characters;
				
			m.insert(make_pair(j,s));
		}
		
		auto t2 = std::chrono::system_clock::now();
		
		std::cout << "Making and inserting " << map_size << " elements: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
		<< " ms\n";
		
		map_size*=10;
	}
	
	return 0;
}
