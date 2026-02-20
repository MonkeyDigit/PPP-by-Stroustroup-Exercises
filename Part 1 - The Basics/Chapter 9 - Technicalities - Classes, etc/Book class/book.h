#pragma once
#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 9 Drills\std_lib_facilities.h"
#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 9 Drills\Chrono.h"
//#include "Chrono.h"
//Genre enum-----------------------------------------------------------------
enum class Genre { fiction = 1, nonfiction, periodical, biography, children };

//--------------------------------------------------------------------------------------------------------------------
//Book class----------------------------------------------------------------------------------------------------------
class Book {
public:
	//constructor
	Book(string tt, string aa, Genre gg, int crdate, string isbn);
	//Retrieve values
	string get_title() const { return title; };
	string get_author() const { return author; };
	string get_isbn() const { return ISBN; };
	Genre get_genre() const { return genre; };
	int get_cr_date() const { return copyright_date; };
	//Check in and check out
	void check_in();
	void check_out();
private:
	string title;
	string author;
	int copyright_date;
	string ISBN;
	Genre genre;
	bool is_isbn_valid();
	bool is_checked_in;	//if it's in the library
	bool is_checked_out; //to check out, means to buy: if the book has been bought already
	class Invalid {};
};

//book operator overloading-------------------------------------------------------
ostream& operator<<(ostream& os, const Book& b);
bool operator==(const Book& a, const Book& b);
bool operator!=(const Book& a, const Book& b);


//----------------------------------------------------------------------------------------------------------------------
//Patron class----------------------------------------------------------------------------------------------------------
class Patron {
public:
	Patron(string pname, string cardnum);
	//Retrieve values
	string get_name() const { return name; };
	string get_card_num() const { return card_number; };
	double get_fees() const { return lib_fees; };
	//Set fee
	void set_fee(double);
private:
	string name;		//user's name
	string card_number;	//library card number
	double lib_fees;		//library fees
	class Invalid{};		//to throw when a patron variable is invalid
	bool is_card_valid();	//returns true if the library card is valid
};

//Patron operator overloading-------------------------------------------------
ostream& operator<<(ostream& os, const Patron& p);
bool operator==(const Patron& a, const Patron& b);
bool operator!=(const Patron& a, const Patron& b);


//----------------------------------------------------------------------------------------------------------------------
//Transaction class-----------------------------------------------------------------------------------------------------
struct Transaction {
	//constructor
	Transaction(Book bk, Patron pt, Chrono::Date dt) : book(bk), patron(pt), date(dt) {};
	//members
	Book book;
	Patron patron;
	Chrono::Date date;
};


//----------------------------------------------------------------------------------------------------------------------
//Library class----------------------------------------------------------------------------------------------------------
class Library {
public:
	//Get books,patrons, and transitions list
	vector<Book> get_books() const { return book_list; };
	vector<Patron> get_patrons() const { return patron_list; };
	vector<Transaction> get_trans() const { return transactions; };
	//add books and patrons. check out a book
	void add_book(const Book& b);
	void add_patron(const Patron& p);
	void check_out_book(const Patron& p, const Book& b, const Chrono::Date dt);
private:
	vector<Book> book_list;
	vector<Patron> patron_list;
	vector<Transaction> transactions;
	bool is_patron_present(const Patron& p);
	bool is_book_present(const Book& b);
};
