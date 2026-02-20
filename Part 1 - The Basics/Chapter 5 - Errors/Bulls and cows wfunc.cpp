#include "std_lib_facilities.h"
#include <conio.h>

vector<int> ntog;
vector<int> guessnum;
int bulls;
int cows;
bool repeat;
int tries;
bool running;
char retry;

void setup();
void input_num();
void check_num();

int main()

{
	do
	{
		
		setup();
		
		system("cls");
		cout<<"Try to guess a number of 4 values:\n"<<"Bulls = right guessed values in the right position\n"
		<<"Cows = right guessed values but not in right position\n\n";
		do
		{
			bulls=0;
			cows=0;
			
			input_num();
			
			check_num();
			
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

void setup()
{
	srand(time(NULL));
	bulls=0;
	cows=0;
	tries=0;
	repeat=false;
	running=true;
	ntog.resize(4);
	guessnum.resize(ntog.size());
	
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
}

void input_num()
{
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
}

void check_num()
{
	//Ciclo confronto
	for(int i=0;i<ntog.size();i++)
	{
		for(int j=0;j<ntog.size();j++)
		{
			if(guessnum[i]==ntog[j] && i==j) bulls++;
			else if(guessnum[i]==ntog[j]) cows++;
		}
	}
}
