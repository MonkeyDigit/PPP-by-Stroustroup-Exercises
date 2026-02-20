#include "std_lib_facilities.h"
/*
1 I
2 II
3 III
4 IV
5 V
6 VI
7 VII
8 VIII
9 IX
10 X
-
11 XI
12 XII
13 XIII
14 XIV
15 XV
16 XVI
17 XVII
18 XVIII
19 XIX
20 XX
-
50 L
100 C
500 D
1000 M
*/
struct Roman_int {
	string rom_num;
	int as_int();
};


int Roman_int::as_int()
{
	int r_as_int {};
	for(char c : rom_num)
	{
		switch(c)
		{
			case 'M':
				r_as_int+=1000;
				break;
			case 'D':
				r_as_int+=500;
				break;
			case 'C':
				r_as_int+=100;
				break;
			case 'L':
				r_as_int+=50;
				break;
			case 'X':
				r_as_int+=10;
				break;
			case 'V':
				r_as_int+=5;
				break;
			case 'I':
				r_as_int+=1;
				break;
			default:
				error("Impossible!");
		}
	}
	
	return r_as_int;	
}

istream& operator>>(istream& is, Roman_int& r)
{
	return is >> r.rom_num;
}

ostream& operator<<(ostream& os, const Roman_int& r)
{
	return os << r.rom_num;
}


int main()
{
	Roman_int r;
	cin>>r;
	cout << "Roman " << r << " equals " << r.as_int() << '\n';
	return 0;
}
