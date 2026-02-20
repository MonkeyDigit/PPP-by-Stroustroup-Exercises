#pragma once
//MODIFICATION: Token_stream ts is now passed by reference to the functions, so now it's declared in main and it's not a global variable anymore
//NOTE: the token type implementations could have been improved using enums, that is, each command (help,let,assign) can be a symbolic value
#include "std_lib_facilities.h"

struct Token {			//A token can be an operator, number or command, a number can be expressed either with an explicit value or a variable which contains it
	char kind;			//kind of token: of type number, operator, name (for variables), declaration, print and quit
	double value;		//value of token assigned only if it's a number
	string name;		//name for variables
	//Constructors for constructing token
	Token(char ch) :kind(ch), value(0) { }					//for functions that represent themselves (operators, commands)
	Token(char ch, double val) :kind(ch), value(val) { }	//for numbers 
	Token(char ch, string n) :kind(ch), name(n) { }			//for variables (type name, name)
};

//TOKEN STREAM CLASS------------------------------------------------
class Token_stream {
public:
	Token_stream() :full(0), buffer(0) { }	//constructor

	Token get();					//function to get tokens
	void unget(Token t) { buffer = t; full = true; }		//renamed putback function: puts tokens back in the input stream via the buffer

	void ignore(char);					//ignores all characters before a ';' in case of error, and continue calculating

private:			//private unget variables
	bool full;
	Token buffer;
};

//-----------------------------------------------------------------
//const characters to describe token's kinds
extern const char help;				//help token type
extern const char let;				//declaration token type
extern const char assign;			//assignment type
extern const char constch;			//for declaring constants, only used in declaration() and get()
extern const char quit;				//quit type
extern const char sq_root;			//square root type
extern const char powc;				//powchar for power type
extern const char print;			//print type
extern const char number;			//number type
extern const char name;				//name type
//string commands
extern const string quitkey;		//exit key
extern const char helpkey;			//instructions key
extern const char declkey;			//declaration key
extern const char asskey;			//assignment key
extern const char constkey;			//const declaration key
extern const string sqrtkey;		//square root key sqrt(x)
extern const string powkey;			//power key pow(b,e) or just pow(b)
//for the output
extern const string prompt;
extern const string result;

//FUNCTION DECLARATIONS--------------------------------------------
void clean_up_mess(Token_stream& ts);			//To continue calculating after an error
void calculate(Token_stream& ts);				//Handle Input and Output of statements
double statement(Token_stream& ts);				//Handle expression and declarations
double expression(Token_stream& ts);			//Handle set of operands [+;-]
double term(Token_stream& ts);					//Handle set of operands [*;/]
double primary(Token_stream& ts);				//Handle numbers, parenthesis and variables
double declaration(Token_stream& ts);			//Handle declarations
double assignment(Token_stream& ts);			//Handle assignments
//for declarations and assignments
struct Variable;				//Variable type
//vector<Variable> vnames;		//vector of type Variable to store the variables
bool is_declared(string s);		//Check if a variable has been declared already
bool is_aconst(string s);		//Check if s is the name of a constant
struct Constant;				//Constant types
//vector<Constant> cnames;		//Constant vector (declared later)
double get_value(string s);		//Read the expression of a variable
void set_value(string s, double d); //Set the variable's value
void instructions();				//instructions