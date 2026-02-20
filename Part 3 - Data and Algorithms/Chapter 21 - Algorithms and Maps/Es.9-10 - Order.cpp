#include "std_lib_facilities.h"

class Purchase{
	string name;
	double unit_price;
	int count;
public:
	Purchase(): name{}, unit_price{}, count{} {}
	Purchase(string prod_name, double unit_price, int count);
	
	string get_name() const {return name;}
	double get_unit_price() const {return unit_price;}
	int get_count() const {return count;}
};

Purchase::Purchase(string prod_name, double unit_price, int count)
	: name{prod_name}, unit_price{unit_price}, count{count}
{
	if(unit_price<0) error("Negative unit_price");
	if(count<0) error("Negative count");
}

istream& operator>>(istream& is, Purchase& p)
{
	char ch,ch2;
	
	is >> ch;
	
	if(!is) return is;
	if(ch!='(')
	{
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	
	is >> ch2;
	
	if(ch2!='\"')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	string name;
	getline(is,name,'\"');	//get the line from is until we encounter "
	
	double unit_price;
	int count;
	
	is >> unit_price >> count >> ch;
	
	if(!is) return is;
	if(ch!=')')
	{
		is.clear(ios_base::failbit);
		return is;
	}
		
	p=Purchase{name,unit_price,count};
	return is;
}

ostream& operator<<(ostream& os, const Purchase& p)
{
	return os << "(\"" << p.get_name() << "\" " << p.get_unit_price() << ' ' << p.get_count() << ')';
}

class Order{
	string name;
	string address;
	string data;
	vector<Purchase> purchases;
public:
	Order(): name{}, address{}, data{}, purchases{} {}
	Order(string name,string addr, string data,vector<Purchase> purchases);
	
	string get_name() const {return name;}
	string get_address() const {return address;}
	string get_data() const {return data;}
	vector<Purchase> get_purchases() const {return purchases;}
};

Order::Order(string name,string addr, string data,vector<Purchase> purchases)
	: name{name}, address{addr}, data{data}, purchases{purchases} {}
	

istream& operator>>(istream& is, Order& o)
{
	char ch,ch2;
	
	is >> ch;
	
	if(!is) return is;	
	if(ch!='{')	//it might be something else
	{
		is.unget();
		is.clear(ios_base::failbit); // set the fail bit
		return is;
	}
	
	is >> ch2;
	
	if(ch2!='\"')
	{
		is.clear(ios_base::failbit); // set the fail bit
		return is;
	}
	
	string name,address,data;
	getline(is,name,'\"');
	
	is >> ch2;
	
	if(ch2!='\"')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	
	getline(is,address,'\"');
	is >> ch2;
	
	if(ch2!='\"')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	
	getline(is,data,'\"');
	
	vector<Purchase> purchases;
	
	Purchase p;
	for(Purchase p; is >> p;)
		purchases.push_back(p);
		
	if(is.eof()) 
	{
		is.clear(ios_base::failbit);
		return is;
	}
	
	if(!is) is.clear();	//we need to clear is when the Purchase input fails, that is, we are terminating the order
						//if we don't do this the input won't accept any further characters and gets stuck in an infinite loop
	
	is >> ch;
	if(ch!='}')
	{
		is.clear(ios_base::failbit);
		return is;
	}
	o = Order{name,address,data,purchases};
	return is;
}

ostream& operator<<(ostream& os, const Order& order)
{
	os << '{' 
		<< "\"" << order.get_name() << "\" "
		<< "\"" << order.get_address() << "\" "
		<< "\"" << order.get_data() << "\" ";
		
	for(int i=0;i<order.get_purchases().size();++i)
	{
		os << order.get_purchases()[i];
		if(i<order.get_purchases().size()-1)
			os << ' ';
	}
	
	return os << '}';
}

double price(double v, const Purchase& p)
{
 return v + p.get_unit_price() * p.get_count(); // calculate price and accumulate
}

int main()
try
{
	ifstream ifs{"orders.txt"};
	
	vector<Order> client_orders;
	
	for(Order o; ifs>>o;)
		client_orders.push_back(o);
		
	cout << "The orders: \n";
	for(const Order& ord : client_orders)
		cout << ord << '\n';
		
	sort(client_orders.begin(),client_orders.end(),[](const Order& a, const Order& b) {return a.get_name()<b.get_name();});
	
	ofstream ofs{"sorted_orders.txt"};
	
	cout << "\nSorted the orders by client name\n";
	
	for(const Order& ord : client_orders)
		ofs << ord << '\n';
	
	double tot_value{0.0};
	//don't know why accumulate is not working
	for(const Order& ord : client_orders)
	{
		for(const Purchase& p : ord.get_purchases())
		{
			tot_value+=price(0.0,p);
		}
	}
	
	cout << "\nTotal value of orders: " << tot_value << '\n';
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
