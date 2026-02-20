#include "std_lib_facilities.h"

class String_stream{				//String_stream class to enter strings
	public:
		string get_s();				//get string
		void putback_s(string s);		//put string back in the input stream, using the buffer
	
	private:
		bool full {false};	//buffer starts empty
		string buffer {"0"};
};

string String_stream :: get_s()
{
	if(full)				//if the buffer is full, return the buffer
	{
		full=false;
		return buffer;
	}
	
	string s;				//get string
	cin>>s;
	return s;
}

void String_stream :: putback_s(string s)
{
	if(full) error("Impossible!");
	full=true;						//filling the buffer
	buffer=s;
}

String_stream ss;		//ss of type String_stream
//---------------------------------------------------
//deals with conjunctions and period
string sentence();
//deals with verbs
string noun_verb();
//deals with nouns
string art_noun();
//deals with articles
string article()
{
	string art;
	art=ss.get_s();
	if(art != "The" && art != "the")
	{
		ss.putback_s(art);			//a sentence can start without article, if art isn't an article
		art="";						//then put it back in the input stream, it might be a noun
		return art;
	}
	return art+" ";
}
//-----------------------------------------------
int main()
try
{
	cout<<"Enter a sentence terminated by '.'\n"<<"Enter p to print\n"<<"Enter x to exit\n\n";
	string op;
	string fullsen {"0"};
	while(cin)
	{
		op=ss.get_s();
		if(op== "p")
		{
			cout<<fullsen<<'\n';
		}
		else if(op=="x") break;
		else ss.putback_s(op);
		fullsen=sentence();
		cout<<"OK!\n";			//if sentence is executed without errors, then the sentence is correct
	}
	keep_window_open();
	
	
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}

//----------------------------------------------------------------------
string sentence()
{
	string sen=noun_verb();			//get a sentence
	
	string conj=ss.get_s();		//get a conjunction or period
	//cin>>conj;
	
	if(conj=="and" || conj=="but" || conj=="or")		//if conj is any of those, then add it to the sentence, and ask a sentence to add
	{
		sen=sen+" "+conj+" "+sentence();
		return sen;
	}
	else if(conj==".")									//if conj is a period, the sentence is terminated
	{
		return sen;
	}
	else error("Expected '.' or conjunction");
}
string noun_verb()
{
	string noun_verb=art_noun();			//get the noun
	string verb;
	verb=ss.get_s();						//get the verb
	
	if(verb=="fly"||verb=="swim"||verb=="rules")
	{
		noun_verb=noun_verb+" "+verb;
		return noun_verb;
	}
	else error("Incorrect verb");
}
string art_noun()
{
	string art_noun=article();		//get the article, or directly the noun
	string noun;
	noun=ss.get_s();		//get noun
	
	if(noun=="birds"||noun=="Birds"||noun=="fish"||noun=="Fish"||noun=="C++")
	{
		art_noun=art_noun+noun;
		return art_noun;
	}
	else error ("Incorrect noun");
}
