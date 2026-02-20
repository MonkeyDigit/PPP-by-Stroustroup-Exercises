#include <iostream>
/*
Il vector, è un array dinamico con cui si possono usare delle funzioni (size(), pushback()) per inserire i valori
o sapere quant'è la sua dimensione
*/
//INCLUDI VECTOR
#include <vector>

using namespace std;

int main()
{				// 0 1 2 3 4 5    ---> la dimensione (v.size()) = 6
	vector<int> v {5,7,9,3,6,8};
	vector<string> str(5);        //vettore stringa di 5 stringhe (ma estendibile) //IMPORTANTE, LE PARENTESI DEVONO ESSERE TONDE
	
	v[3]=4; 			//posso assegnare le posizioni
	
	str[0]="ciao1";
	str[1]="ciao2";
	str[2]="ciao3";
	str[3]="ciao4";
	str[4]="ciao5";
	
	//METODI PER TRAVERSARE IL VECTOR
	//1
	for(int x : v) // verrà stampato 5 7 9 4 6 8  //PER OGNI INT X IN V
	{
		cout<<x<<'\n';
	}
	//2
	for(int i=0; i<str.size(); i++)
	{
		cout<<str[i]<<'\n';
	}
	
	//AGGIUNGO ELEMENTI AL VETTORE
	v.push_back(1); 				//aggiungo a v[6] (il posto successivo all'ultimo) il valore 1, v.size()=7
	
	cout<<v[6];
}


