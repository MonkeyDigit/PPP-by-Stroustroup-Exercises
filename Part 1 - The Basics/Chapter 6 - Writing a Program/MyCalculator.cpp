#include "std_lib_facilities.h"

class Token{						//Classe token per inserire numeri e operandi
	public:
		char kind;					//tipo
		double value;				//valore
		Token(char ch)				//chiamando questa funzione ritorno come object tipo Token, ch in kind, e 0 in value (per operandi e simboli)
		:kind(ch), value(0) { }
		Token(char ch, double val)	//con questa ritorno ch in kind e val in value (per i numeri)
		:kind(ch), value(val) { }
};

class Token_stream {				//classe Token stream per avere un flusso input e usare o inserire nel buffer i token
	public:							//inserisco i token e se necessario li rimetto nello stream per essere utilizzati da altre funzioni
		Token get();
		void putback(Token t);
	private:						//membri in private perchè non si interfacciano con l'utente, solo le funzioni esclusive a Token_stream
		bool full {false};			//se un token viene rimesso nello stream, full=true, e buffer, di tipo token, diventa appunto quel token
		Token buffer {'0'};
};

Token Token_stream::get()			//definizione della funzione get() fuori dalla sua classe (Token_stream)
{
	if(full)					//quando get() è chiamata, se il buffer è pieno ritorna il suo token, che "ha la precedenza", altrimenti procedi con l'input
	{
		full=false;
		return buffer;
	}
	char ch;
	cin>>ch;
	
	switch(ch)
	{
		case 'q':
		case ';':
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
			return Token{ch};			//i simboli rappresentano loro stessi
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '9':
			cin.putback(ch);
			double val;
			cin>>val;
			return Token{'8',val};
		default:
			error("Bad Token!");
	}
}

void Token_stream::putback(Token t)		//chiamo putback e metto il token nel buffer
{
	full=true;
	buffer=t;
}

Token_stream ts;						//variabile di tipo Token_stream per gestire tutte le sue funzioni
										//le seguesti funzioni sono dichiarate in ordine "gerarchico"
double expression();					//gestisce operazioni con + e -

double term();							//gestisce operazioni con *,/

double primary()						//gestisce i numeri, e le espressioni dentro parentesi
{
	Token t=ts.get();
	switch(t.kind)						//se il token e di tipo (, allora inserisci un'espressione da chiudere, altrimenti se è un numero ritorna il suo valore
	{
		case '(':
			{
				double d=expression();
				t=ts.get();
				if(t.kind!=')') error("Expected ')'"); //t in questo caso dovrà sempre essere )
				return d;
				break;
			}
		case '8':
			return t.value;
			break;
		default:
			error("Expected a primary!");
			
	}
}

int main()
try										//blocco try, per usare throw, e poi catch, di eventuali errori
{
	cout<<"Enter an expression: \n";
	while(cin)							//nota che per l'inserimento non ho bisogno di separare tutti i token con lo spazio,
	{									//ogni token assume un valore (un carattere char, o un numero), e il resto viene reinserito nel buffer
		cout<<'='<<expression()<<'\n';	//per inserire ~ premere alt e poi in sequenza 1 2 6 dal blocco numerico non attivo
		keep_window_open("~0");
	}
}
catch(exception& e)
{
	cerr<<"error: "<<e.what()<<'\n';
	keep_window_open("~1");
	return 1;
}
catch(...)
{
	cerr<<"exception \n";
	keep_window_open("~2");
}
	

double expression()
{
	double left=term();
	Token t=ts.get();
	
	while (true)					//questo è in un ciclo, perchè dopo aver fatto un'operazione, richiedo un token, quindi se è un + per esempio
	{								//lo posso e devo utilizzarlo
		switch(t.kind)
		{
			case '+':
				left+=term();
				t = ts.get();
				break;
			case '-':
				left-=term();
				t = ts.get();
				break;
			default:
				ts.putback(t);
				return left;
		}
	}
}

double term()
{
	double left=primary();
	Token t=ts.get();
	
	while (true)
	{
		switch (t.kind)
		{
			case '*':
				left*=primary();
				t=ts.get();
				break;
			case '/':
				{
					double d = primary();				//Se voglio definire delle variabili in uno switch statement, devo per forza farlo dentro un blocco (le {})
					if(d==0) error("Can't divide by 0!"); //non posso dividere per 0
					left/=d;
					t = ts.get();
					break;
				}
			default:
				ts.putback(t);
				return left;	
		}
	}
}

