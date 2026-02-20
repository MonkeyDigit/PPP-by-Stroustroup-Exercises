#include "Simple_window.h"
#include "Graph.h"
#include "GUI.h"
#include "std_lib_facilities.h"

class Purchase {
	string name;
	double unit_price;
	int count;
public:
	Purchase() : name{}, unit_price{}, count{} {}
	Purchase(string prod_name, double unit_price, int count);

	string get_name() const { return name; }
	double get_unit_price() const { return unit_price; }
	int get_count() const { return count; }
};

Purchase::Purchase(string prod_name, double unit_price, int count)
	: name{ prod_name }, unit_price{ unit_price }, count{ count }
{
	if (unit_price < 0) error("Negative unit_price");
	if (count < 0) error("Negative count");
}

istream& operator>>(istream& is, Purchase& p)
{
	char ch, ch2;

	is >> ch;

	if (!is) return is;
	if (ch != '(')
	{
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	is >> ch2;

	if (ch2 != '\"')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	string name;
	getline(is, name, '\"');	//get the line from is until we encounter "

	double unit_price;
	int count;

	is >> unit_price >> count >> ch;

	if (!is) return is;
	if (ch != ')')
	{
		is.clear(ios_base::failbit);
		return is;
	}

	p = Purchase{ name,unit_price,count };
	return is;
}

ostream& operator<<(ostream& os, const Purchase& p)
{
	return os << "(\"" << p.get_name() << "\" " << p.get_unit_price() << ' ' << p.get_count() << ')';
}

class Order {
	string name;
	string address;
	string data;
	vector<Purchase> purchases;
public:
	Order() : name{}, address{}, data{}, purchases{} {}
	Order(string name, string addr, string data, vector<Purchase> purchases);

	string get_name() const { return name; }
	string get_address() const { return address; }
	string get_data() const { return data; }
	vector<Purchase> get_purchases() const { return purchases; }
};

Order::Order(string name, string addr, string data, vector<Purchase> purchases)
	: name{ name }, address{ addr }, data{ data }, purchases{ purchases } {}


istream& operator>>(istream& is, Order& o)
{
	char ch, ch2;

	is >> ch;

	if (!is) return is;
	if (ch != '{')	//it might be something else
	{
		is.unget();
		is.clear(ios_base::failbit); // set the fail bit
		return is;
	}

	is >> ch2;

	if (ch2 != '\"')
	{
		is.clear(ios_base::failbit); // set the fail bit
		return is;
	}

	string name, address, data;
	getline(is, name, '\"');

	is >> ch2;

	if (ch2 != '\"')
	{
		is.clear(ios_base::failbit);
		return is;
	}

	getline(is, address, '\"');
	is >> ch2;

	if (ch2 != '\"')
	{
		is.clear(ios_base::failbit);
		return is;
	}

	getline(is, data, '\"');

	vector<Purchase> purchases;

	Purchase p;
	for (Purchase p; is >> p;)
		purchases.push_back(p);

	if (is.eof())
	{
		is.clear(ios_base::failbit);
		return is;
	}

	if (!is) is.clear();	//we need to clear is when the Purchase input fails, that is, we are terminating the order
	//if we don't do this the input won't accept any further characters and gets stuck in an infinite loop

	is >> ch;
	if (ch != '}')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	o = Order{ name,address,data,purchases };
	return is;
}

ostream& operator<<(ostream& os, const Order& order)
{
	os << '{'
		<< "\"" << order.get_name() << "\" "
		<< "\"" << order.get_address() << "\" "
		<< "\"" << order.get_data() << "\" ";

	for (int i = 0; i < order.get_purchases().size(); ++i)
	{
		os << order.get_purchases()[i];
		if (i < order.get_purchases().size() - 1)
			os << ' ';
	}

	return os << '}';
}

struct Orders_window : Window {
	Orders_window(Point xy, int w, int h, const string& title);
private:

	Button insert_button;
	Button add_purchase_button;
	Button quit_button;

	Text order_head;
	Text purchase_head;

	Graph_lib::Rectangle order_rect;
	Graph_lib::Rectangle purchase_rect;

	//which file to write to
	In_box in_file_out;

	//for purchases
	In_box in_purchase_name;
	In_box in_unit_price;
	In_box in_count;

	//for the order
	In_box in_order_name;
	In_box in_address;
	In_box in_data;

	Out_box status_out;

	ofstream ofs;
	string ofname;
	vector<Purchase> purchases;

	void add_purchase();
	void insert();
	void quit();

};

Orders_window::Orders_window(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	quit_button{ Point(x_max() - 70, 0), 70, 20, "Quit", [](Address, Address pw) {reference_to<Orders_window>(pw).quit(); } },
	insert_button{ Point(13, 145), 105, 20, "Insert order", [](Address, Address pw) {reference_to<Orders_window>(pw).insert(); } },
	add_purchase_button{ Point(317,145),105,20,"Add purchase", [](Address, Address pw) {reference_to<Orders_window>(pw).add_purchase(); } },
	order_rect{ Point(5,5),300, 170 },
	purchase_rect{ Point(310,5),300,170 },
	order_head{ Point(10,30),"ORDER" },
	purchase_head{ Point(315,30),"PURCHASE" },
	in_file_out{ Point{80,200},200,20,"Output file:" },
	in_purchase_name{ Point{380,50},200,20,"Name:" },
	in_unit_price{ Point{380,80},200,20,"Unit price:" },
	in_count{ Point{380,110},200,20,"Count:" },
	in_order_name{ Point{80,50},200,20,"Name:" },
	in_address{ Point{80,80},200,20,"Address:" },
	in_data{ Point{80,110},200,20,"Data:" },
	status_out{ Point{335,200},340,20,"Status:" }
{
	order_rect.set_color(Color::black);
	purchase_rect.set_color(Color::black);
	attach(order_rect);
	attach(purchase_rect);

	order_head.set_font(Font::times_bold);
	order_head.set_font_size(25);
	order_head.set_color(Color::black);
	purchase_head.set_font(Font::times_bold);
	purchase_head.set_font_size(25);
	purchase_head.set_color(Color::black);
	attach(order_head);
	attach(purchase_head);

	attach(quit_button);
	attach(insert_button);
	attach(add_purchase_button);

	attach(in_file_out);
	attach(in_purchase_name);
	attach(in_unit_price);
	attach(in_count);
	attach(in_order_name);
	attach(in_address);
	attach(in_data);
	attach(status_out);
}

void Orders_window::quit()
{
	hide();
}

void Orders_window::add_purchase()
{
	string prod_name=in_purchase_name.get_string();

	stringstream ss{ in_unit_price.get_string() };

	int count=in_count.get_int();

	if (prod_name.length() == 0 || ss.str().length() == 0 || count == 0)
	{
		cout << "Empty purchase field/s\n";
		status_out.put("Empty purchase field/s");
		return;
	}

	double unit_price;
	ss >> unit_price;
	if (!ss)
	{
		cout << "Wrong unit price format\n";
		status_out.put("Wrong unit price format");
		return;
	}
	purchases.push_back(Purchase{ prod_name,unit_price,count });
	cout << "Purchase succesfully inserted!\n";
	status_out.put("Purchase succesfully inserted!");
}
void Orders_window::insert()
{
	string fname=in_file_out.get_string();

	if (!ofs.is_open())
	{
		if (fname.length() == 0)
		{
			cout << "Error: No output file entered\n";
			status_out.put("Error: No output file entered");
			return;
		}

		ofs.open(fname+".txt", ios_base::app);
		if (!ofs)
		{
			cout << "Couldn't open output file " << fname << '\n';
			status_out.put("Couldn't open output file "+fname);
			return;
		}
		ofname = fname;
	}

	if (ofname != fname && ofs.is_open())
	{
		ofs.close();
		ofs.open(fname + ".txt", ios_base::app);

		if (!ofs)
		{
			cout << "Couldn't open output file " << fname << '\n';
			status_out.put("Couldn't open output file " + fname);
			return;
		}

		ofname = fname;
	}



	string name = in_order_name.get_string();
	string address = in_address.get_string();
	string data = in_data.get_string();

	if (name.length() == 0 || address.length() == 0 || data.length() == 0)
	{
		cout << "Empty order field/s\n";
		status_out.put("Empty order field/s");
		return;
	}

	if (purchases.size() == 0)
	{
		cout << "The order has no purchases!\n";
		status_out.put("The order has no purchases!");
		return;
	}
	Order order{in_order_name.get_string(),in_address.get_string(),in_data.get_string(),purchases};
	ofs << order << '\n';
	ofs.close();	//By closing the file, each time we insert an order it gets written to the file in real time
	cout << "Order succesfully inserted in file " << fname << "!\n";
	status_out.put("Order succesfully inserted in file "+fname);
	purchases = vector<Purchase>{};	//reset the vector
}

int main()
try
{
	using namespace Graph_lib;
	Point tl{ 400,150 };

	Orders_window owin{ tl,700,250,"Orders" };
	return gui_main();
}
catch (exception& e)
{
	cerr << "Exception: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...)
{
	cerr << "Unknown exception\n";
	keep_window_open();
	return 2;
}