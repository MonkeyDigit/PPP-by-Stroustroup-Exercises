#include <iostream>
#include <vector>
#include <list>
#include <exception>

using Line = std::vector<char>;	//a line is a vector of characters

class Text_iterator{	//keep track of line and character position within a line
	std::list<Line>::iterator ln;
	Line::iterator pos;
public:
	//start the iterator at line ll’s character position pp:
	Text_iterator(std::list<Line>::iterator ll, Line::iterator pp)
		:ln{ll}, pos{pp} { }
		
	char& operator*() {return *pos;}
	Text_iterator& operator++();
	Text_iterator& operator--();
	bool operator==(const Text_iterator& other) const
		{ return ln==other.ln && pos==other.pos;}
	bool operator!=(const Text_iterator& other) const
		{return !(*this==other);}
};

Text_iterator& Text_iterator::operator++()
{
	++pos;					//proceed to the next character
	if(pos==(*ln).end()) {
		++ln;				//proceed to next line
		pos = (*ln).begin(); //bad if ln==line.end(); so make sure it isn't
	}
	
	return *this;
}

Text_iterator& Text_iterator::operator--()
{
	if(pos==(*ln).begin()) {
		
		--ln;				//proceed to previous line
		pos = (*ln).end()-1;
	}
	else
		--pos;
	
	return *this;
}

struct Document{
	std::list<Line> line;	//a document is a list of lines
	
	Text_iterator begin()	//first character of the first line
		{return Text_iterator(line.begin(),(*line.begin()).begin());}
	
	Text_iterator end()	//one beyond the last character of the last line
	{
		auto last = line.end();
		--last; //we know that the document is not empty
		return Text_iterator(last, (*last).end());
	}
	
	Document() {line.push_back(Line{});}
};

std::istream& operator>>(std::istream& is, Document& d)
{
	for(char ch; is.get(ch);)
	{
		d.line.back().push_back(ch); //add the character
		
		if(ch=='\n')
			d.line.push_back(Line{});
	}
	
	if(d.line.back().size())
		d.line.push_back(Line{});	//add a final empty line
	
	return is;
}

//helper functions
void print(Document& d)
{
	for(auto p : d)
		std::cout << p;
}

void erase_line(Document& d, int n)
{
	if (n<0 || d.line.size()-1<=n)
		return;
	auto p = d.line.begin();
	advance(p,n);
	d.line.erase(p);
}

int main()
try
{
	
	return 0;
}
catch(std::exception& e)
{
	std::cerr << "Error: " << e.what() << '\n';
	exit(1);
}
catch(...)
{
	std::cerr << "Unknown exception\n";
	exit(2);
}
