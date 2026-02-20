#include "Simple_window.h"
#include "Graph.h"

class Distribution {
public:
	Distribution(int year, double young_perc, double middle_perc, double old_perc);
	Distribution() {}
	int get_year() const { return year; }
	double get_young() const { return young; }
	double get_middle() const { return middle; }
	double get_old() const { return old; }
private:
	int year{};
	double young{};
	double middle{};
	double old{};
};

Distribution::Distribution(int year, double young_perc, double middle_perc, double old_perc)
	:year(year), young(young_perc), middle(middle_perc), old(old_perc)
{
	//the check doesn't work for some reason
	//if ((young + middle + old) > 100 || (young + middle + old) < 100) error("Percentages don't make it up to 100 ");
}

istream& operator>>(istream& is, Distribution& d)
{
	int year;
	double young;
	double middle;
	double old;
	char ch1, ch2, ch3; // year : young ,  middle , old

	is >> year >> ch1 >> young >> ch2 >> middle >> ch3 >> old;
	if (!is) return is;
	if (ch1 != ':' || ch2 != ',' || ch3 != ',')
	{
		is.clear(ios_base::failbit);
		return is;
	}

	d = Distribution(year, young, middle, old);
	return is;
}

ostream& operator<<(ostream& os, const Distribution& d)
{
	
	return os << d.get_year() << ':' << d.get_young() << ',' << d.get_middle() << ',' << d.get_old();
}

class Scale {
public:
	Scale(int b, int vb, double s) :cbase{ b }, vbase{ vb }, scale{ s } { }
	int operator()(int v) const { return cbase + (v-vbase)*scale; } // see §21.4
private:
	int cbase;		//axis coordinate base				- in this program, xoffset and yoffset  for x and y respectively
	int vbase;		//starting base value of the axis   - base_year and 0
	double scale;	//how many pixels=1
};
using namespace Graph_lib;
int main()
try
{
	cout << "Please enter input file name: ";
	string iname;
	cin >> iname;
	ifstream ifs{ "Italy_age_distribution.txt" };
	if (!ifs) error("Couldn't open input file");

	Point tl(300, 150);
	constexpr int xmax = 1000;
	constexpr int ymax = 800;
	Simple_window win(tl, xmax, ymax, "My window");
	win.wait_for_button();

	constexpr int xoffset = 200;
	constexpr int yoffset = 60;
	constexpr int xspace = 25;
	constexpr int yspace = 50;
	constexpr int xlength = xmax - xoffset - xspace;
	constexpr int ylength = ymax - yoffset - yspace;
	
	constexpr int base_year = 2002;
	constexpr int end_year = 2022;
	constexpr double xscale = double(xlength) / (end_year-base_year);
	constexpr double yscale = double(ylength) / 100;		//goes up to 100%
	constexpr int xnotches = (end_year - base_year)/2;

	Axis xa{ Axis::x,Point(xoffset,ymax - yoffset),xlength,xnotches,"Anno" };
	Axis ya{ Axis::y,Point(xoffset,ymax - yoffset),ylength,10,"% popolazione" };
	xa.label.set_font(Font::helvetica_bold);
	ya.label.set_font(Font::helvetica_bold);
	xa.label.set_font_size(17);
	ya.label.set_font_size(17);
	xa.label.set_color(Color::dark_blue);
	ya.label.set_color(Color::dark_blue);
	xa.label.move(-xlength/5, 0);
	ya.label.move(-xlength/6, -10);
	win.attach(xa);
	win.attach(ya);

	istringstream xlabel_str{ "2002 2004 2008 2010 2012 2014 2016 2018 2020 2022" };

	Vector_ref<Text> x_labels;
	int notch_count = 0;

	//Fill the x_labels vector, with text and position, and attach them to the window
	for (string year; xlabel_str >> year;)
	{
		double x =xoffset + notch_count * xscale*2 - year.length()*4;		//NOTE: we multiply xscale by 2 because xscale is equal to 1 year
		double y = ymax-yoffset+20;							//but we draw notches every two years, so this must be done to place years correctly
		x_labels.push_back(new Text{ Point(x,y),year});
		x_labels[x_labels.size() - 1].set_font(Font::helvetica_bold);
		x_labels[x_labels.size() - 1].set_font_size(14);
		win.attach(x_labels[x_labels.size() - 1]);
		++notch_count;
	}

	/*
	Vector_ref<Text> y_labels;
	notch_count = 1;
	for (int i = 10; i <= 100; i+=10)
	{
		stringstream perc_str;
		perc_str << i;
		double x = xoffset - 45;
		double y = ymax-yoffset-notch_count*yscale*10+7;	//we add 7 to center the text
		std::cout << y<<'\n';
		y_labels.push_back(new Text{ Point(x,y),perc_str.str()});
		y_labels[y_labels.size() - 1].set_font(Font::helvetica_bold);
		y_labels[y_labels.size() - 1].set_font_size(17);
		win.attach(y_labels[y_labels.size() - 1]);
		++notch_count;

	}
	*/

	//after adjusting the graph, we finally read the data
	Open_polyline young;
	Open_polyline middle;
	Open_polyline old;

	Scale xs{ xoffset,base_year,xscale };
	Scale ys{ ymax-yoffset,0,-yscale };	//NOTE: we use -yscale 
	for (Distribution d; ifs >> d;)
	{
		young.add(Point(xs(d.get_year()), ys(d.get_young())));
		middle.add( Point( xs(d.get_year()), ys(d.get_middle()) ) );
		old.add( Point( xs(d.get_year()), ys(d.get_old()) ) );
	}

	young.set_color(Color::dark_green);
	middle.set_color(Color::blue);
	old.set_color(Color::dark_red);

	Text young_label{ Point(young.point(0).x - 85,young.point(0).y+5),"0-14 anni" };
	Text middle_label{ Point(middle.point(0).x - 85,middle.point(0).y+5),"15-64 anni" };
	Text old_label{ Point(old.point(0).x - 85,old.point(0).y+5),"65+ anni" };
	young_label.set_font(Font::helvetica_bold);
	middle_label.set_font(Font::helvetica_bold);
	old_label.set_font(Font::helvetica_bold);

	young_label.set_color(Color::dark_green);
	middle_label.set_color(Color::blue);
	old_label.set_color(Color::dark_red);
	young_label.set_font_size(17);
	middle_label.set_font_size(17);
	old_label.set_font_size(17);

	win.attach(young);
	win.attach(middle);
	win.attach(old);

	win.attach(young_label);
	win.attach(middle_label);
	win.attach(old_label);
	win.wait_for_button();
	return 0;
}

catch (exception& e)
{
	cerr << "Error: " << e.what();
	return 1;
}

catch (...)
{
	cerr << "Unknown exception";
	return 2;
}