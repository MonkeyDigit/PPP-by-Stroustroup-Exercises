#include "std_lib_facilities.h"

class Name_value{
	public:
		string name;
		double value;
};

int main()
{
	vector<Name_value> name_vec;
	cout<<"Enter NoName 0 to stop the input\n";
	bool insert{true};
	Name_value nv{"0",0};
	do
	{
		cout<<"Name: ";
		cin>>nv.name;
		cout<<"Value: ";
		cin>>nv.value;
		if(!cin) error("Invalid value!");
		
		if (nv.name=="NoName" && nv.value==0) insert=false;			//CURIOSITA': dato che ogni cin è separato andando a capo, o dallo spazio, se inserisco NoName 10,
		else name_vec.push_back(nv);								//tentando di inserire name, name assumerà NoName, il 10, che è comunque una stringa, è mantenuto dal buffer
																	//input, così, quando poi chiede il valore, posso inserire un valore associato a NoName, poi mi chiederà
	}while (insert);												//direttamente il valore del prossimo nome! Questo perchè viene controllato il buffer, e viene trovato quel 10.
	
	cout<<"Print names and values? (y/n)\n";
	char ch;
	cin>>ch;
	if (!cin) error("Invalid response!");
	for(Name_value x : name_vec)
	{
		cout<<"Name: "<<x.name<<"\nValue: "<<x.value<<'\n';
	}
	return 0;
}
