#include "std_lib_facilities.h"
#include <conio.h>

int main()
{
	bool running=true;
	
	
	do
	{
		srand(time(NULL));
		vector<int> ntog(4);
		vector<int> guessnum(ntog.size());
		int bulls{};
		int cows{};
		bool repeat;
		char retry;
		int tries{};
		
		for(int i=0;i<ntog.size();i++)		//Ciclo per fare il numero random di 4 cifre
		{
			do
			{
				ntog[i]=rand()%10;
				
				repeat=false;
				for(int j=0;j<i;j++)
				{
					if(ntog[i]==ntog[j]) repeat=true;
				}
			}while (repeat);
		}
		
		system("cls");
		cout<<"Try to guess a number of 4 values:\n"<<"Bulls = right guessed values in the right position\n"
		<<"Cows = right guessed values but not in right position\n\n";
		do
		{
			bulls=0;
			cows=0;
			//Ciclo input
			for(int i=0;i<ntog.size();i++)
			{
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
			//Ciclo confronto
			for(int i=0;i<ntog.size();i++)
			{
				for(int j=0;j<ntog.size();j++)
				{
					if(guessnum[i]==ntog[j] && i==j) bulls++;
					else if(guessnum[i]==ntog[j]) cows++;
				}
			}
			tries++;
			cout<<'\n'<<"Bulls: "<<bulls<<"\nCows: "<<cows<<"\n\n";
		} while (bulls<ntog.size());
		
		cout<<"You won! the number was ";
		for(int i=0;i<ntog.size();i++)
		{
			cout<<ntog[i];
		}
		
		cout<<"\nTries: "<<tries<<"\n\nRetry?(y/n): ";
		cin>>retry;
		switch(retry)
		{
			case 'y':
				break;
			case 'n':
				running=false;
				break;
			default:
				error("Invalid response!");
		}
	}while (running);
	
	return 0;
}
