#include "std_lib_facilities.h"

struct Token {				//A token can be an operator, number or command, a number can be expressed either with an explicit value or a variable which contains it
	char kind;				//kind of token: of type number, operator, name (for variables), declaration, print and quit
	double value;			//value of token assigned only if it's a number
	string name;			//name for variables
	//Constructors for constructing token
	Token(char ch) :kind(ch), value(0) { }					//for functions that represent themselves (operators, commands)
	Token(char ch, double val) :kind(ch), value(val) { }	//for numbers 
	Token(char ch,string n) :kind(ch), name(n) { }			//for variables (type name, name)
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

Token_stream ts;		//Variable of type Token stream

//-----------------------------------------------------------------
//const characters to describe token's kinds
const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const string declkey = "let";

//FUNCTION DECLARATIONS--------------------------------------------
//Token Token_stream::get();
//void Token_stream::ignore(char c);	//have been declared inside class
void clean_up_mess();			//To continue calculating after an error
void calculate();				//Handle Input and Output of statements
double statement();				//Handle expression and declarations
double expression();			//Handle set of operands [+;-]
double term();					//Handle set of operands [*;/]
double primary();				//Handle numbers, parenthesis and variables
double declaration();			//Handle declarations
struct Variable;				//Variable type
vector<Variable> names;			//vector of type Variable to store the variables
bool is_declared(string s);		//Check if a variable has been declared already
double get_value(string s);		//Read the expression of a variable

//MAIN--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int main()			//when there is only one function (try{}), {} are not needed. REMEMBER: when they are not put, the function executes ONLY the first one block
try {				//this applies to loops as well
	cout<<"Welcome to our simple calculator!\nPlease enter expressions using floating-point numbers.\n"
		<<"Operators available: [+, -, *, /, (, ).] \nTo declare a variable write let 'name' = 'expression' \n"
		<<"Enter "<<quit<<" to exit, and "<<print<<" to print the result\n\n";
	calculate();
	return 0;
}
catch (exception& e) {							//catch any exception thrown by the try block
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');				//eats all characters different from ';', if ';' exit
	return 1;
}
catch (...) {				//catch unknown exceptions
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}

//--------------------------------------------------------------------------------------------
//FUNCTION DEFINITIONS------------------------------------------------------------------------
void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)			//this loop eats all input after an error is caught, and to continue evaluation, it seeks for c (in this case it will be print)
		if (ch == c) return;	//and exits the loop only after it is found
}

void clean_up_mess()	
{
	ts.ignore(print);
}

//INPUT AND OUTPUT CALCULATIONS------------------------------------

/*ERROR HANDLING: When an error is thrown by functions inside calculate() (expression, primary...), all lines contained in the functions
are analyzed to look for a catch clause, the first found will be executed.
For example, if an error from primary() is thrown, the first catch that it finds is the one in calculate().*/
const string prompt = "> ";
const string result = "= ";
void calculate()
{
	while (true) try {							//the try block is executed and the while loop makes it so that after an error is caught, it countinues the loop
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();         //Eat all print tokens                        
		if (t.kind == quit) return;					  //Exit from calculate when entering quit command
		ts.unget(t);							//Else pass the token to statement
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {			//Error handling
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

//HANDLE STATEMENTS------------------------------------------------
double statement()
{
	Token t = ts.get();			//STATEMENTS: Declarations; Expressions.
	switch (t.kind) {
	case let:					//If the first input is of type let, then it means a declaration is to be done
		return declaration();
	default:
		ts.unget(t);			//else pass that token to expression()
		return expression();
	}
}

//HANDLE EXPRESSIONS----------------------------------------------
double expression()
{
	double left = term();
	while (true) {			//Switch inside loop to keep calculating unless we want to print or quit
		Token t = ts.get();
		switch (t.kind) {
		case '+':			//Handle addition
			left += term();
			break;
		case '-':			//Handle subtraction
			left -= term();
			break;
		default:
			ts.unget(t);	//Put back token
			return left;
		}
	}
}

//HANDLE TERMS----------------------------------------------------
double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':								//Handle multiplications
			left *= primary();
			break;
		case '/':								//Handle divisions, throw an error when trying to divide by zero
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		default:
			if(t.kind == name) error("Unknown operand");	//If i input "2bc", without this, it would ouput 2 and then give an error for bc as a variable;
			ts.unget(t);						//Put back the token in the Token stream to use it in other functions ( just expression() )
			return left;
		}
	}
}

//HANDLE PRIMARIES------------------------------------------------
double primary()
{
	Token t = ts.get();
	switch (t.kind) {					//Token's kind based on the input
	case '(':									//Write an expression when opening parenthesis			
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("'(' expected");	//Must close parenthesis after the expression
	return d;
	}
	case '-':						//Negative numbers
		return -primary();
	case number:					//Positive numbers
		return t.value;
	case name:						//Return the variable's value after confronting its name
		return get_value(t.name);
	default:
		error("primary expected");	//This is theoretically never executed, because character errors are already handled by get(). Can be disputed
	}
}

//VARIABLE STRUCT--------------------------------------------------
struct Variable {								//STRUCTS are like classes but its members are public by default. in this case it was appropriate as
	string name;								//there weren't any functions to be used exclusive to variables
	double value;
	Variable(string n, double v) :name(n), value(v) { }		//variable constructor to declare variables and store them
};

//HANDLE VARIABLE DECLARATIONS------------------------------------
double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");			//Variable's names must start with a letter
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");				//Check whether the variable is already declared or not. Throw an error if so
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);	//After entering "let name" (name as example), an expression must be assigned with '='
	double d = expression();
	names.push_back(Variable(name, d));									//Enter an expression, and then add a variable with name as the name, and d as the value
	return d;
}

//FIND THE VARIABLE'S VALUE----------------------------------------
double get_value(string s)
{
	for (int i = 0; i < names.size(); ++i)				//this loop is used to extrapolate the value of a variable, by confronting a name to all variables stored
		if (names[i].name == s) return names[i].value;	//if the variable is actually stored in the vector, return its value, else throw an error
	error("get: undefined name ", s);
}

/*----------------------------------------------------------------
void set_value(string s, double d)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

*///DETERMINE IF A VARIABLE IS ALREADY DECLARED------------------
bool is_declared(string s)						
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

//-----------------------------------------------------------------
Token Token_stream::get()		//class method defined outside of class. [type classname :: func name()]
{
	if (full) { full = false; return buffer; }		//if the buffer is full, return the buffer as token
	char ch;
	cin >> ch;
	switch (ch) {				//cases for operators and commands implemented in the program
	case print:
	case quit:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
		return Token(ch);		//let each character represent themselves
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget();			//if the token is a number, insert it into o double variable
	double val;
	cin >> val;
	return Token(number, val);	//NOTE: if input is "5;" val is going to assume 5, and in the istream, NOT Token stream, there will be left the ;
	}
	default:					//for variables (they can't start with a number or operator)
		if (isalpha(ch)) {		//isalpha() checks that the (first) character is exclusively a letter of the alphabet
			string s;
			s += ch;														//start building a string
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+= ch;		//until ch is a letter or number, add it to the name
			cin.unget();											//istream function, same as putback
			if (s == declkey) return Token(let);						//if s= declkey, return a token which of kind let, to declare a variable
			return Token(name, s);						//else it might be a variable name, so kind: name (const type defined earlier in line 34), and name: s
		}
		error("Bad token");		//gets executed if ch is not a number, a letter, or an implemented function(es. ! is factiorial), for example '@'
	}							//note:factorial not implemented yet
}

