#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

typedef vector<string>::const_iterator Line_iter;

class Message{	//a Message points to the first and the last lines of a message
	Line_iter first;
	Line_iter last;
public:
	Message(Line_iter p1, Line_iter p2): first{p1}, last{p2} {}
	Line_iter begin() const {return first;}
	Line_iter end() const {return last;}
	//...
};

using Mess_iter = vector<Message>::const_iterator;

struct Mail_file{				//a Mail_file holds all the lines from a file
								//and simplifies access to all messages
	string name;				//file name
	vector<string> lines;		//the lines in order
	vector<Message> m;			//Messages in order
	
	Mail_file(const string& n);	//read file n into lines
	
	Mess_iter begin() const {return m.begin();}
	Mess_iter end() const {return m.end();}
};

//find the name of the sender in a message
//return true if found
//if found, place the sender's name in s:
bool find_from_addr(const Message* m, string& s);

//return the subject of the Message, if any, otherwise "":
string find_subject(const Message* m);

int main()
try
{
	Mail_file mfile{"my-mail-file.txt"};	//initialize mfile from a file
	
	//first gather messages from each sender together in a multimap
	multimap<string, const Message*> sender;
	
	for(const auto& m : mfile)
	{
		string s;
		if(find_from_addr(&m,s))
			sender.insert(make_pair(s,&m));
	}
	
	//now iterate through the multimap
	//and extract the subjects of John Doe's messages:
	auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
	for(auto p = pp.first; p!=pp.second; ++p)
		cout << find_subject(p->second) << '\n';
	return 0;
}
catch(exception& e)
{
	cerr << "Exception: " << e.what() << '\n';
	exit(1);
}
catch(...)
{
	cerr << "Unknown exception\n";
	exit(2);
}

Mail_file::Mail_file(const string& n)
	//open file named n
	//read the lines from n into lines
	//find the messages in the lines and compose them in m
	//for simplicity assume every message is ended by a ---- line
{
	ifstream in{n};		//open the file
	if(!in)
	{
		cerr << "no " << n << '\n';
		exit(1);		//terminate the program
	}
	
	for(string s; getline(in,s);)	//build the vector of lines
		lines.push_back(s);
	
	auto first = lines.begin();		//build the vector of Messages
	for(auto p=lines.begin(); p!=lines.end();++p)
	{
		if(*p=="----")	//end of message
		{
			if(p!=first)
				m.push_back(Message(first,p));
			else
				cout << "Warning: empty message ignored in file " << n << '\n';
				
			first=p+1;		//---- not part of message
		}
	}
}

int is_prefix(const string& s, const string& p)
	//is p the first part of s?
{
	int n=p.size();
	if(string(s,0,n)==p) return n;	//string(s,0,n) constructs a string from
	return 0;						//s[0] to s[n-1]
}

bool find_from_addr(const Message* m, string& s)
{
	for(const auto& x : *m)
	{
		if(int n=is_prefix(x,"From: "))	//if n (which gets assigned is_prefix)
		{								//is bigger than 0, assing to s the string
			s=string(x,n);			//string from x[n] to x[x.size()-1]
			return true;
		}
	}
	return false;
}

string find_subject(const Message* m)
{
	for(const auto& x : *m)
		if(int n=is_prefix(x,"Subject: ")) return string(x,n);
		
	return "";
}
