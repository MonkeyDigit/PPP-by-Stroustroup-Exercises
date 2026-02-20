#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<string> input_word;
	vector<string> censor_word{"broccoli", "zucchine", "spinaci"};
	bool censor=false;
	
	cout<<"Inserisci delle parole separate dallo spazio\n";
	
	for(string word; cin>>word;)
	{
		input_word.push_back(word);
	}
	cout<<'\n';
	for(string word : input_word)
	{
		censor=false;
		for(string cword : censor_word)
		{
			if(word==cword)
			{
				censor=true;
			}
		}
		if(!censor)
		{
			cout<<word;
		}
		else
		{
			cout<<"BLEEP";
		}
		cout<<' ';
	}
	
	system("PAUSE");
	return 0;
}
