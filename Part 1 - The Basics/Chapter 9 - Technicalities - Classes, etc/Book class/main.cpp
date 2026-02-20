#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 9 Drills\std_lib_facilities.h"
//#include "C:\Users\Marco Fadda\Documents\C++\Esercizi C++\Stroustrup\Chapter 9 Drills\Chrono.h"
//#include "Chrono.h"
#include "book.h"

int main()
{
	/*
	Book bk1 { "The Green Mile", "Stephen King",Genre::fiction, 1996, "976-16-3-14574" };
	Book bk2 { "Harry Potter", "J.K. Rowling", Genre::fiction, 1995, "564-12-57-123" };
	Book bk3 { "Game of Thrones", "Pinco Pallino", Genre::biography, 2005, "834-457-121-b" };

	Patron pat1{ "George Stanton","506342" };
	Patron pat2{ "Dean Moores", "959211" };

	pat2.set_fee(10.55);

	cout << pat1 << '\n'
		<< pat2 << '\n';
	*/

	Book bk1{ "book1", "author1",Genre::fiction, 2000, "1-1-1-1" };
	Book bk2{ "book2", "author2",Genre::nonfiction, 2000, "1-1-1-2" };
	Book bk3{ "book2", "author3",Genre::periodical, 2000, "1-1-1-3" };
	Book bk4{ "book4", "author4",Genre::biography, 2000, "1-1-1-4" };

	cout << bk1 <<'\n';

	Patron pt0{ "patron0","00" };
	cout << pt0 << '\n';
	pt0.set_fee(10.50);
	cout << pt0 << '\n';

	Library lb1;
	lb1.add_book(bk1);
	lb1.add_book(bk2);
	lb1.add_book(bk3);
	lb1.add_book(bk4);

	lb1.add_patron(Patron{ "patron1","11" });
	lb1.add_patron(Patron{ "patron2","22" });
	lb1.add_patron(Patron{ "patron3","33" });
	lb1.add_patron(Patron{ "patron4","44" });

	lb1.check_out_book(lb1.get_patrons()[1], lb1.get_books()[0], Chrono::Date{2001,6,25});

	return 0;
}