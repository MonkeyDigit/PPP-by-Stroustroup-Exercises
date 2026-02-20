#include "Simple_window.h"
#include "Graph.h"

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;
//reading		Cambridge - town in Massachussets and England
// (1,2.5,2.1) - (month,mass,eng)
class Reading {
public:
	Reading(int month, double mass_temp, double eng_temp);
	Reading() {};
	int month() const { return m; }
	double mass_temp() const { return mt; }
	double eng_temp() const { return et; }
private:
	int m;
	double mt;	//mas temp
	double et;	//eng temp
};

Reading::Reading(int month, double mass_temp, double eng_temp)
	:m(month), mt(mass_temp), et(eng_temp)
{
	if (mt > implausible_max || mt > implausible_max) error("Temperature too high");
	if (mt < implausible_min || mt < implausible_min) error("Temperature too low");
	if (m <= 0 || 12 < m) error("Invalid month");
}

istream& operator>>(istream& is, Reading& r)
{
	char ch1, ch2, ch3,ch4;
	int month;
	double mas_t;
	double eng_t;
	is >>ch1 >> month>> ch2 >> mas_t >> ch3 >> eng_t >> ch4;
	if (!is) return is;
	if (ch1 != '(' || ch2 != ',' || ch3!=',' || ch4 != ')')
	{
		is.clear(ios_base::failbit);
		return is;
	}

	r=Reading{ month,mas_t,eng_t };
	return is;
}

class Scale { // data value to coordinate conversion
	int cbase; // coordinate base
	int vbase; // base of values
	double scale;
public:
	Scale(int b, int vb, double s) :cbase{ b }, vbase{ vb }, scale{ s } { }
	int operator()(int v) const { return cbase + (v-vbase)*scale; } // see §21.4
};

using namespace Graph_lib;
int main()
{
	/*
	std::cout << "Please enter input file name: ";
	string iname;
	std::cin >> iname;
	*/
	ifstream ifs{ "Cambridge_temps.txt"};
	if (!ifs) error("Couldn't open input file ");

	constexpr int xmax = 600; // window size
	constexpr int ymax = 600;
	constexpr int xoffset = 50; // distance from left-hand side of window to y axis
	constexpr int yoffset = 60; // distance from bottom of window to x axis
	constexpr int xspace = 40; // space beyond axis
	constexpr int yspace = 40;
	constexpr int xlength = xmax-xoffset-xspace; // length of axes
	constexpr int ylength = ymax-yoffset-yspace;
	Point tl(150, 150);
	Simple_window win(tl, xmax, ymax, "Cambridge temperatures");
	win.wait_for_button();

	Axis xa{ Axis::x,Point(xoffset,ymax - yoffset),xlength,12,"Month     Jan     Feb     Apr     May     "
		"Jun    Jul     Aug     Sep     Oct     Nov     Dec" };
	Axis ya{ Axis::y,Point(xoffset,ymax - yoffset),ylength,40,"Celsius temps in 0 - 40 C" };
	xa.label.move(-150, 0);

	constexpr double xscale = double(xlength) / 12;
	constexpr double yscale = double(ylength) / 40;

	Scale xs{ xoffset,0,xscale };
	Scale ys{ ymax-yoffset,0,-yscale };
	Open_polyline mass_temps;
	Open_polyline eng_temps;
	for (Reading r; ifs >> r;)
	{
		mass_temps.add(Point(xs(r.month()-1), ys(r.mass_temp())));
		eng_temps.add(Point(xs(r.month()-1), ys(r.eng_temp())));
		std::cout << '(' << r.month() << ',' << r.mass_temp() << ',' << r.eng_temp() << ')'<<'\n';
	}

	mass_temps.set_color(Color::red);
	eng_temps.set_color(Color::blue);

	win.attach(xa);
	win.attach(ya);
	win.attach(mass_temps);
	win.attach(eng_temps);
	win.wait_for_button();
	return 0;
}