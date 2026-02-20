#include "std_lib_facilities.h"

using Line = vector<char>; // a line is a vector of characters

class Text_iterator { // keep track of line and character position within a line
	list<Line>::iterator ln;
	Line::iterator pos;
public:
	// start the iterator at line ll’s character position pp:
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		:ln{ll}, pos{pp} { }
		
	char& operator*() { return *pos; }
	
	Text_iterator& operator++();
	Text_iterator& operator--();
	
	bool operator==(const Text_iterator& other) const
	{ return ln==other.ln && pos==other.pos; }
	
	bool operator!=(const Text_iterator& other) const
	{ return !(*this==other); }
};

Text_iterator& Text_iterator::operator++()
{
	++pos; // proceed to next character
	if (pos==(*ln).end())
	{
		++ln; // proceed to next line
		pos = (*ln).begin(); // bad if ln==line.end(); so make sure it isn’t
	}
	
	return *this;
}

Text_iterator& Text_iterator::operator--()
{
	if(pos==(*ln).begin())
	{
		--ln;
		pos = (*ln).end();
		--pos;
	}
	else
		--pos;
	return *this;
}

struct Document {
	list<Line> line; // a document is a list of lines
	Document() { line.push_back(Line{}); }
	Text_iterator begin() // first character of first line
	{ return Text_iterator(line.begin(), (*line.begin()).begin()); }
	
	Text_iterator end() // one beyond the last character of the last line
	{
		auto last = line.end();
		--last; // we know that the document is not empty
		return Text_iterator(last, (*last).end());
	}
};

template<typename Iter> // requires Forward_iterator<Iter>
void advance(Iter& p, int n)
{
	if(0<n)
		while (0<n) { ++p; --n; }
	else if(n<0)
		while (n<0) {--p; ++n; }
}

void erase_line(Document& d, int n)
{
	if (n<0 || d.line.size()-1<=n) return;
	auto p = d.line.begin();
	advance(p,n);
	d.line.erase(p);
}


istream& operator>>(istream& is, Document& d)
{
	for (char ch; is.get(ch); )
	{
		d.line.back().push_back(ch); // add the character
		if (ch=='\n')
		d.line.push_back(Line{}); // add another line
	}
	
	if (d.line.back().size()) d.line.push_back(Line{}); // add final empty line
	return is;
}

//counts spaces
int char_count(Document& doc)
{
	int count{0};
	for(auto p : doc.line)
	{
		for(const char& ch : p)
			if(ch!='\n') count++;
	}
	
	return count;
}

int main()
try
{
	ifstream ifs{"document.txt"};
	
	Document doc;
	
	ifs>>doc;
	
	cout << char_count(doc)<<'\n';
	return 0;
}
catch(exception & e)
{
	cerr<< "Exception: " << e.what() <<'\n';
	keep_window_open();
	return 1;
}
catch(...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}
