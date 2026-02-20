#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <regex>
#include <chrono>
#include <unordered_map>

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
	Mail_file mfile{"big_mail.txt"};	//initialize mfile from a file
	
	//first gather messages from each sender together in a multimap
	multimap<string, const Message*> sender1;
	auto mm_begin=chrono::system_clock::now(); // begin time
	for(const auto& m : mfile)
	{
		string s;
		if(find_from_addr(&m,s))
			sender1.insert(make_pair(s,&m));
	}
	auto mm_end=chrono::system_clock::now(); // end time
	
	
	unordered_multimap<string, const Message*> sender2;	
	auto um_begin=chrono::system_clock::now();
	for(const auto& m : mfile)
	{
		string s;
		if(find_from_addr(&m,s))
			sender2.insert(make_pair(s,&m));
	}
	auto um_end=chrono::system_clock::now();
	
	cout << "multimap time: " << (double)chrono::duration_cast<chrono::milliseconds>(mm_end-mm_begin).count() << "ms \n";
	cout << "unordered_multimap time: " << (double)chrono::duration_cast<chrono::milliseconds>(um_end-um_begin).count() << "ms \n";
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
			m.push_back(Message(first,p));
			first=p+1;		//---- not part of message
		}
	}
}

bool find_from_addr(const Message* m, string& s)
{
	regex pat{R"(^From:\s?)"};
	for(const auto& x : *m)
	{
		smatch matches;
		if(regex_search(x,matches,pat))
		{
			s=string(x,matches[0].length());
			return true;
		}
	}
	return false;
}

string find_subject(const Message* m)
{
	regex pat{R"(^Subject:\s?)"};
	for(const auto& x : *m)
	{
		smatch matches;
		if(regex_search(x,matches,pat))
			return string(x,matches[0].length());
	}
		
	return "";
}
