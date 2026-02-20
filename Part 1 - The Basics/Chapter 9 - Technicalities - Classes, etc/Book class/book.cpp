#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 9 Drills\std_lib_facilities.h"
//#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 9 Drills\Chrono.h"
//#include "Chrono.h"
#include "book.h"
//---------------------------------------------------------------------------------------------------------------------------------
//Book memebers' definition--------------------------------------------------------------------------------------------------------
Book::Book(string tt, string aa, Genre gg, int crdate, string isbn)
	: title(tt), author(aa), genre(gg), copyright_date(crdate), ISBN(isbn), is_checked_in{false}, is_checked_out{false}
{
	if (!is_isbn_valid()) throw Invalid{};
}

void Book::check_in()
{
	if (is_checked_out) error("Book has been checked out");
	if (is_checked_in) error("Book has been already checked in");
	is_checked_in = true;
}

void Book::check_out()
{
	if (is_checked_out) error("Book has been already checked out");
	if (!is_checked_in) error("Book isn't checked in");
	is_checked_out = true;
	is_checked_in = false;
}
//to check the ISBN and patron card------------------------------------------
bool is_int(char& ch)
{
	switch (ch)
	{
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		return true;

	default:
		return false;
	}
}
//n-n-n-x     where n= int  and  x= int or letter
bool Book::is_isbn_valid()
{
	int hyphen_count{ 0 };	//hyphen = '-'

	for (int i = 0; i < ISBN.length(); ++i)
	{
		if (ISBN[i] == '-')
		{
			++hyphen_count;
		}
		else if (!is_int(ISBN[i]) && i < ISBN.length() - 1 || !is_int(ISBN[i]) && !isalpha(ISBN[i])) //if it's not a number, or if at the
		{																							//last place it's not a number or letter
			return false;
		}

		if (i > 0)
		{
			if (ISBN[i] == '-' && ISBN[i - 1] == '-' || ISBN[0] == '-') return false;
		}

	}
	if (hyphen_count < 3 || hyphen_count > 3) return false;

	return true;
}

//book operator overloading--------------------------------------------
ostream& operator<<(ostream& os, const Book& b)
{
	return os << "Title: " << b.get_title() << '\n'
		<< "Author: " << b.get_author() << '\n'
		<< "Genre: " << int(b.get_genre()) << '\n'
		<< "Copyright: " << b.get_cr_date() << '\n'
		<< "ISBN: " << b.get_isbn();
}

bool operator==(const Book& a, const Book& b)
{
	return a.get_isbn() == b.get_isbn();
}
bool operator!=(const Book& a, const Book& b)
{
	return !(a == b);
}


//---------------------------------------------------------------------------------------------------------------------------------
//Patron memebers' definition-------------------------------------------------------------------------------------------------------
//constructor
Patron::Patron(string pname, string cardnum) 
	: name(pname), card_number(cardnum), lib_fees{0}
{
	if (!is_card_valid()) throw Invalid{};
}

//must be only numbers - it's a string because it can't be used for mathematic operations
bool Patron::is_card_valid()
{
	for (int i = 0; i < card_number.length(); ++i)
		if (!is_int(card_number[i])) return false;

	return true;
}

void Patron::set_fee(double f)
{
	if (f < 0) error("Invalid fee");
	lib_fees = f;
}

//Patron helper functions------------------------------------------
bool owe_fee(const Patron& p)
{
	if (p.get_fees() > 0) return true;
	return false;
}

//patron operator overloading----------------------------------------
ostream& operator<<(ostream& os, const Patron& p)
{
	os << "Name: " << p.get_name() <<'\n'
	<< "Card number: " << p.get_card_num() << '\n';
	if (owe_fee(p)) os << "Fees owed: " << p.get_fees() << '\n';
	return os;
}

bool operator==(const Patron& a, const Patron& b)
{
	return a.get_card_num() == b.get_card_num();
}

bool operator!=(const Patron& a, const Patron& b)
{
	return !(a == b);
}


//---------------------------------------------------------------------------------------------------------------------------------
//Library memebers' definition-----------------------------------------------------------------------------------------------------
void Library::add_book(const Book& b)
{
	for (int i = 0; i < book_list.size(); ++i)
	{
		if (b == book_list[i]) error("This book is already in the library");
	}
		book_list.push_back(b);
}
void Library::add_patron(const Patron& p)
{
	for (int i = 0; i < patron_list.size(); ++i)
	{
		if (p == patron_list[i]) error("This patron is already in the library");
	}
		patron_list.push_back(p);
}

void Library::check_out_book(const Patron& p, const Book& b, const Chrono::Date dt)
{
	if (!is_patron_present(p)) error("This patron is not in the library");
	if (!is_book_present(b)) error("This book is not in the library");
	if (owe_fee(p)) error("This patron already owes fees");
	transactions.push_back(Transaction(b, p, dt));

}

//Checkout implementation functions the checkout----------------------------------
bool Library::is_patron_present(const Patron& p)
{
	for (int i = 0; i < patron_list.size(); ++i)
	{
		if (p == patron_list[i]) return true;
	}
	return false;
}

bool Library::is_book_present(const Book& b)
{
	for (int i = 0; i < book_list.size(); ++i)
	{
		if (b == book_list[i]) return true;
	}
	return false;
}


//Helper functions--------------------------------------------
//Print patrons who owe fees
void print_debtors(const Library& lb)
{
	for (int i=0; i<lb.get_patrons().size(); ++i)
	{
		if ( owe_fee(lb.get_patrons()[i]) ) cout << lb.get_patrons()[i] << '\n';
	}
}