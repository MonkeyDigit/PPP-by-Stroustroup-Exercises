#include "std_lib_facilities.h"
#include <conio.h>
int main()
{
	vector<int> ntog {1,4,6,7};
	vector<int> guessnum(ntog.size());
	int bulls{};
	int cows{};
	
	do
	{
		bulls=0;
		cows=0;
		for(int i=0;i<ntog.size();i++)
		{
			bool repeat;
			do
			{
				//guessnum assume il valore char del numero, e, se '0' = 48, allora per assumere veramente 1 per esempio, sottraggo 48
				guessnum[i]=getch()-48;
				
				repeat=false;
				for(int j=0;j<i;j++)
				{
					if(guessnum[i]==guessnum[j]) repeat=true;
				}
				
			}while(guessnum[i]<0 || guessnum[i]>9 || repeat);
			
			cout<<guessnum[i];
		}
		
		for(int i=0;i<ntog.size();i++)
		{
			for(int j=0;j<ntog.size();j++)
			{
				if(guessnum[i]==ntog[j] && i==j) bulls++;
				else if(guessnum[i]==ntog[j]) cows++;
			}
		}
		cout<<'\n'<<"Bulls: "<<bulls<<"\nCows: "<<cows<<'\n';
	} while (bulls<ntog.size());
}
