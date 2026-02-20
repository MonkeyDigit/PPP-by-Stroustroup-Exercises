#include "std_lib_facilities.h"
#include "mycalc.h"
#include <conio.h>
#include <Windows.h>

//const characters to describe token's kinds
const char help = 'H';				//help token type
const char let = 'L';				//declaration token type
const char assign = 'A';			//assignment type
const char constch = 'C';			//for declaring constants, only used in declaration() and get()
const char quit = 'Q';				//quit type
const char sq_root = 'R';			//square root type
const char powc = 'P';				//powchar for power type
const char print = ';';				//print type
const char number = '8';			//number type
const char name = 'a';				//name type
//const string quitkey = "quit";		//string commands
const string quitkey = "exit";		//exit key
const char helpkey = '?';			//instructions key
const char declkey = '#';			//declaration key
const char asskey = '@';			//assignment key
const char constkey = '[';			//const declaration key
const string sqrtkey = "sqrt";		//square root key sqrt(x)
const string powkey = "pow";		//power key pow(b,e) or just pow(b)
//for the output
const string prompt = "> ";
const string result = "= ";
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

void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}

//INPUT AND OUTPUT CALCULATIONS------------------------------------

//ERROR HANDLING: When an error is thrown by functions inside calculate() (expression, primary...), all lines contained in the functions
//are analyzed to look for a catch clause, the first found will be executed.
//For example, if an error from primary() is thrown, the first catch that it finds is the one in calculate().
void calculate(Token_stream& ts)
{
	//while (true) 
	try {							//the try block is executed and the while loop makes it so that after an error is caught, it countinues the loop
		//Token t = ts.get();
		//while (t.kind == print) t = ts.get();         //Eat all print tokens
		//if (t.kind == quit) return;					  //Exit from calculate when entering quit command
		//ts.unget(t);							//Else pass the token to statement
		cout << result << statement(ts) << endl;
	}
	catch (runtime_error& e) {			//Error handling
		cerr << "error: " << e.what() << endl;
		clean_up_mess(ts);
	}
}

//HANDLE STATEMENTS------------------------------------------------
double statement(Token_stream& ts)
{
	Token t = ts.get();			//STATEMENTS: Declarations; Expressions.
	switch (t.kind) {
	case let:					//If the first input is of type let, then it means a declaration is to be done
		return declaration(ts);
	case assign:					//for assignments
		return assignment(ts);
	default:
		ts.unget(t);			//else pass that token to expression()
		return expression(ts);
	}
}

//HANDLE EXPRESSIONS----------------------------------------------
double expression(Token_stream& ts)
{
	double left = term(ts);
	while (true) {			//Switch inside loop to keep calculating unless we want to print or quit
		Token t = ts.get();
		switch (t.kind) {
		case '+':			//Handle addition
			left += term(ts);
			break;
		case '-':			//Handle subtraction
			left -= term(ts);
			break;
		default:
			ts.unget(t);	//Put back token
			return left;
		}
	}
}

//HANDLE TERMS----------------------------------------------------
double term(Token_stream& ts)
{
	double left = primary(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':								//Handle multiplications
			left *= primary(ts);
			break;
		case '/':								//Handle divisions, throw an error when trying to divide by zero
		{	double d = primary(ts);
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%':
		{
			double d = primary(ts);
			if (d == 0) error("divide by zero");
			left = fmod(left, d);
			break;
		}
		case name:					//error("Unknown operand");	//If i input "2bc", without this, it would ouput 2 and then give an error for bc as a variable;
			left *= get_value(t.name);
			break;
		default:
			ts.unget(t);						//Put back the token in the Token stream to use it in other functions ( just expression() )
			return left;
		}
	}
}

//HANDLE PRIMARIES------------------------------------------------
double primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {					//Token's kind based on the input
	case '(':									//Write an expression when opening parenthesis			
	{	double d = expression(ts);
	t = ts.get();
	if (t.kind != ')') error("')' expected");	//Must close parenthesis after the expression
	return d;
	}
	case '-':						//Negative numbers
		return -primary(ts);
	case number:					//Positive numbers
		return t.value;
	case name:						//Return the constant or variable's value after confronting its name
		return get_value(t.name);
	case sq_root:					//if the token returned is of type sq_root, it means 'sqrt(' has been entered already, so just ask for the expression and ')'
	{
		double b = expression(ts);
		if (b < 0) error("Negative root");
		double sq = sqrt(b);
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return sq;
	}
	case powc:						//in this case, if the user enters pow(b,e), it returns b^e, if it's just pow(b) then it returns b^2
	{
		double b = expression(ts);
		t = ts.get();
		if (t.kind == ')') return pow(b, 2);
		if (t.kind != ',') error("',' expected in pow()");
		double e = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("')' expected in pow()");
		return pow(b, e);
	}
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
Vector<Variable> vnames;
//CONSTANT STRUCT-------------------------------------------------
struct Constant {
	string name;
	const double value;
	Constant(string n, double v) :name(n), value(v) { }
};
vector<Constant> cnames
{ Constant("pi",3.1415926535897932384626433832795028841971693993751058209),
Constant("e",2.7182818284),
Constant("k",1000) };

//HANDLE VARIABLE DECLARATIONS------------------------------------
double declaration(Token_stream& ts)
{
	Token t = ts.get();
	bool decl_const = false;
	if (t.kind == constch)
	{
		decl_const = true;
		t = ts.get();
	}
	if (t.kind != name) error("name expected in declaration");			//Variable's names must start with a letter
	string sname = t.name;
	if (is_declared(sname)) error(sname, " declared twice");				//Check whether the variable is already declared or not. Throw an error if so
	if (is_aconst(sname)) error("Can't redefine a constant");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", sname);	//After entering "let name" (name as example), an expression must be assigned with '='
	double d = expression(ts);
	if (decl_const)
		cnames.push_back(Constant(sname, d));
	else
		vnames.push_back(Variable(sname, d));							//Enter an expression, and then add a variable with name as the name, and d as the value
	return d;
}

//HANDLE ASSIGNMENT-----------------------------------------------
double assignment(Token_stream& ts)
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in assignment");
	string sname = t.name;
	if (is_aconst(sname)) error("assign: can't redefine constants");
	if (!is_declared(sname)) error("assign: undeclared name");
	Token t2 = ts.get();
	if (t2.kind != '=') error("assign: '=' expected");
	double d = expression(ts);
	set_value(sname, d);
	return d;

}

//FIND THE VARIABLE'S VALUE----------------------------------------
double get_value(string s)
{
	for (int i = 0; i < vnames.size(); ++i)				//this loop is used to extrapolate the value of a variable, by confronting a name to all variables stored
		if (vnames[i].name == s) return vnames[i].value;	//if the variable is actually stored in the vector, return its value, else throw an error

	for (int i = 0; i < cnames.size(); ++i)
		if (cnames[i].name == s) return cnames[i].value;
	error("get: undefined name ", s);
}

//SET THE VARIABLE'S VALUE-----------------------------------------
void set_value(string s, double d)
{
	for (int i = 0; i < vnames.size(); ++i)
		if (vnames[i].name == s) {
			vnames[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

//DETERMINE IF A VARIABLE IS ALREADY DECLARED--------------------
bool is_declared(string s)
{
	for (int i = 0; i < vnames.size(); ++i)
		if (vnames[i].name == s) return true;
	return false;
}

//DETERMINE IF S IS THE NAME OF A CONSTANT-------------------------
bool is_aconst(string s)
{
	for (int i = 0; i < cnames.size(); ++i)
		if (cnames[i].name == s) return true;
}


//-----------------------------------------------------------------
Token Token_stream::get()		//class method defined outside of class. [type classname :: func name()]
{
	if (full) { full = false; return buffer; }		//if the buffer is full, return the buffer as token
	char ch;
	cin >> ch;
	switch (ch) {				//cases for operators and commands implemented in the program
	case declkey:				//return a decl type token
		return Token(let);
	case asskey:
		return Token(assign);
	case constkey:
		return Token(constch);
	case helpkey:
		return Token(help);
	case print:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case ',':
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
	default:
		if (isalpha(ch) || ch == '_') {		//isalpha() checks that the (first) character is exclusively a letter of the alphabet
			string s;						//for variables (they can't start with a number or operator)
			s += ch;														//start building a string
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;		//until ch is a letter or number, add it to the name
			cin.unget();											//istream function, same as putback
			//if (s == declkey) return Token(let);						//if s= declkey, return a token which of kind let, to declare a variable
			if (s == sqrtkey)						//if the users write the sqrt, if they also enter '(' then it means they want to use the sqrt() function
			{										//and return a token of type square root
				cin >> ch;
				if (ch == '(') return Token(sq_root);
				cin.unget();						//if not, then it might just be a variable name, so proceed as normal
			}
			if (s == powkey)						//same logic as the square root above
			{
				cin >> ch;
				if (ch == '(') return Token(powc);
				cin.unget();
			}
			if (s == quitkey) return Token(quit);

			return Token(name, s);						//else it might be a variable name, so kind: name (const type defined earlier in line 34), and name: s
		}
		error("Bad token");		//gets executed if ch is not a number, a letter, or an implemented function(es. ! is factiorial), for example '@'
	}							//note:factorial not implemented yet
}

void instructions()
{
	system("cls");
	cout << "Welcome to our simple calculator!\nPlease enter a statement. \n"
		<< "Enter " << quitkey << " to exit, and " << print << " to end an insertion. \n"
		<< "To read the complete instructions, enter: '" << helpkey << "'. \n\n"
		<< "In the simple calculator you can write one or multiple statements to evaluate.\n"
		<< "1.EXPRESSION STATEMENTS: \n\n"

		<< "		" << "It's possible to evaluate expressions with positive and negative floating point numbers, \n"
		<< "		" << "and the calculator follows the PEMDAS mathematic order.\n"
		<< "		" << "The '" << prompt << "'symbol is the prompt, where you can write an expression (ex. 2+2), \n"
		<< "		" << "then, to terminate the input, enter '" << print << "'.\n"
		<< "		" << "If an error message appears, to continue calculating, enter '" << print << "'.\n\n"
		<< "		" << "Mathematic operators implemented: \n"
		<< "		" << "Plus: +\n"
		<< "		" << "Minus: -\n"
		<< "		" << "Multiply: *\n"
		<< "		" << "Divide: /\n"
		<< "		" << "Remainder: %\n"
		<< "		" << "Parenthesis: ( )\n"
		<< "		" << "-----------------------------------------------------\n"
		<< "		" << "The calculator will print the result, which is a floating point number, like so: \n"
		<< "		" << result << "Result \n"
		<< "		" << "and another input is prompted.\n\n"

		<< "2.FUNCTIONS IMPLEMENTED: \n\n"

		<< "		" << "Quit: " << quitkey << '\n'
		<< "		" << "Print: " << print << '\n'
		<< "		" << "Power(base,exponent): pow(b,e) <----(pow(2,3) = 8; pow(3) = 9)\n"
		<< "		" << "Square root(base): sqrt(b) <--------(sqrt(144) = 12)\n\n"

		<< "3.CONSTANTS: \n\n"

		<< "		" << "In this version of the calculator these are the constants available: \n";
	for (int i = 0; i < cnames.size(); ++i)
		cout << "		" << cnames[i].name << ": " << cnames[i].value << '\n';

	cout << "\n4.VARIABLES AND CONSTANTS DECLARATION STATEMENTS\n\n"

		<< "		" << "It is possible to have user declared variables and constants.\n"
		<< "		" << "To make a variable declaration, use the following syntax: \n"
		<< "		" << declkey << " name = expression; <-------(ex. " << declkey << " b = 3*4;)\n\n"

		<< "		" << "NOTE: Variables and constant names cannot have symbols (except '_') in their name, \n"
		<< "		" << "		 and numbers as their first character\n"
		<< "		" << "NOTE: an error will be printed out in case it is tried to declare a variable twice, \n"
		<< "		" << "		 or to redifine a constant, to use an undeclared variable, or the declaration syntax is incorrect.\n\n"

		<< "		" << "For constants the syntax is: \n"
		<< "		" << declkey << constkey << " name = expression; <------(ex." << declkey << constkey << " c = 4.52;)\n\n"

		<< "5.ASSIGNMENT STATEMENTS: \n"
		<< "		" << "As you might have guessed the purpose of separating variables and constants is to use assignments.\n"
		<< "		" << "To make an assignment, use the following syntax: \n"
		<< "		" << asskey << " name = expression; <--------(ex." << asskey << " c = 6;)\n\n"

		<< "		" << "NOTE: an error will be printed out if it is tried to assign a value to an undeclared variable, \n"
		<< "		" << " or to a constant, or the syntax is incorrect.\n\n"

		<< "6.USES OF VARIABLES AND CONSTANTS: \n"
		<< "		" << "Variables and constants can be used in expressions like normal numbers. Input example: \n\n"
		<< "		" << declkey << " b = 4+2; 3+b+1;\n"
		<< "		" << result << "10\n\n"

		<< "		" << "But they can also be used like this: \n"
		<< "		" << declkey << " b = 4+2;\n"
		<< "		" << prompt << "3b;\n"
		<< "		" << result << "18\n"
		<< "-----------------------------------------------------------------------------------------------------------------\n"
		<< "PRESS ANY KEY TO CLOSE INSTRUCTIONS\n";
	char c = _getch();
	system("cls");
}
