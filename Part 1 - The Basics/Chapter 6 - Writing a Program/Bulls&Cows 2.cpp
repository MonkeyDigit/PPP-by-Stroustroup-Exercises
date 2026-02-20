#include "std_lib_facilities.h"
#include <conio.h>

int main()
{
	vector<char> comb{'c','o','m','b'};
	vector<char> ch_guess(comb.size());
	int bulls=0;
	int cows=0;
	while(bulls<4)
	{
		bulls=0;
		cows=0;
		for(int i=0;i<comb.size();i++)
		{
			bool repeat;
			char ch;
			do
			{
				ch=getch();
				repeat=false;
				for(int j=0;j<i;j++)
				{
					if(ch==ch_guess[j] || ch>='0' && ch<='9') repeat=true;
				}
			}while(repeat);
			cout<<ch<<' ';
			ch_guess[i]=ch;
		}		
		
		for(int i=0;i<comb.size();i++)
		{
			for(int j=0;j<comb.size();j++)
			{
				if(ch_guess[i]==comb[j])
				{
					if(i==j) bulls++;
					else cows++;
				}
			}
		}
		cout<<"\nBulls: "<<bulls<<"\nCows: "<<cows<<"\n\n";
	}
	
	cout<<"Congratulations! the word was: ";
	for(char x : comb) cout<<x;
	cout<<'\n';
	
	return 0;
}

