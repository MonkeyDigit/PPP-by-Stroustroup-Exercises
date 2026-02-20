#include "Simple_window.h"
#include "Graph.h"
#include <cmath>
#include <iostream>
# define PI 3.14159265358979
typedef double Fct(double);

double one(double x) { return 1; }
double slope(double x) { return x / 2; }
double square(double x) { return x * x; }
double sloping_cos(double x) { return cos(x) + slope(x); }
double sum_sin_cos(double x) { return sin(x) + cos(x); }
double sum_sin_cos_sq(double x) { return sin(x) * sin(x) + cos(x) * cos(x); }

struct myFct : Shape{
	myFct(Fct* f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
	~myFct() {}
	void calc();
	int get_r1() const { return r1; }
	int get_r2() const { return r2; }
	Point get_orig() const { return xy; }
	int get_count() const { return count; }
	double get_xscale() const { return xscale; }
	double get_yscale() const { return yscale; }
	//reset functions
	void reset(Fct* f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
	void set_f(Fct* p) { f = p; }
	void set_r1(int n) { r1 = n; }
	void set_r2(int n) { r2 = n; }
	void set_orig(Point o) { xy = o; }
	void set_count(int n) { count = n; }
	void set_xscale(double s) { xscale = s; }
	void set_yscale(double s) { yscale = s; }
private:
	Fct* f;
	double r1;
	double r2;
	Point xy;
	int count;
	double xscale;
	double yscale;
};


void myFct::calc()
{
	if (r2 - r1 <= 0) error("bad graphing range");
	if (count <= 0) error("non-positive graphing count");
	double dist = (r2 - r1) / count;
	double r = r1;
	for (int i = 0; i < count; ++i) {
		add(Point{ xy.x + int(r * xscale),xy.y - int(f(r) * yscale) });
		r += dist;
	}
}
myFct::myFct(Fct f, double r1, double r2, Point xy,int count, double xscale, double yscale)
	: f(f),r1(r1),r2(r2),xy(xy),count(count),xscale(xscale),yscale(yscale)
{
	calc();
}

void myFct::reset(Fct* f, double r1, double r2, Point orig, int count, double xscale, double yscale)
{
	set_f(f);
	set_r1(r1);
	set_r2(r2);
	set_orig(orig);
	set_count(count);
	set_xscale(xscale);
	set_yscale(yscale);
	calc();
}

int fac(int n) { return n > 1 ? n * fac(n - 1) : 1; }
double term(double x, int n) { return pow(x, n) / fac(n); } // nth term of series
double expe(double x, int n) // sum of n terms for x
{
	double sum = 0;
	for (int i = 0; i < n; ++i) sum += term(x, i);
	return sum;
}

int expN_number_of_terms = 10;

double expN(double x)
{
	return expe(x, expN_number_of_terms);
}

//Leibniz series
double leibniz_term(int n) 
{
	int denom = 2 * n + 1;
	denom *= n % 2 == 0 ? 1 : -1;

	return 1.0 / denom;
}
double leibniz(double x,int n)
{
	double val = 0;
	for (int i = 0; i < x; ++i)
	{
		if (i >= n) break;
		val += leibniz_term(i);
	}
	return val;
}

int leib_number_of_terms = 10;
double leibN(double x)
{
	return leibniz(x,leib_number_of_terms);
}

//bar graph-------------------------------------------------------------
struct Bar_graph : Shape {
	Bar_graph(Point origin, double xscale, double yscale)
		: orig(origin), xscale(xscale), yscale(yscale) {}
	Bar_graph(Point origin, vector<double> data, double xscale, double yscale);

	void add_value(double v);
	vector<double> get_values() const { return values; }
	void set_bar_color(int i, Color col) { rects[i].set_fill_color(col); }
	void set_graph_label(string label) { glab.set_label(label); }
	void set_bar_label(int i, string label);
	void draw_lines() const;
private:
	vector<double> values;
	Vector_ref<Graph_lib::Rectangle> rects;
	Point orig;
	double xscale;
	double yscale;
	Text glab{ Point(orig.x,orig.y + 20),"" };
	Vector_ref<Text> blabs;
	void add_rect(double x,double v);	//the x coordinate and the height of the rectngle (the value)
};
Bar_graph::Bar_graph(Point origin, vector<double> data, double xscale, double yscale)
	: orig(origin), values(data),xscale(xscale), yscale(yscale)
{
	for (int i = 0; i < values.size(); ++i)
		add_rect(i, values[i]);
}

void Bar_graph::add_value(double v)
{
	values.push_back(v);			//store the value and generate its corresponding rectangle
	add_rect(values.size()-1,v);
}

void Bar_graph::add_rect(double x,double v)
{
	Point tl;
	int ww;
	int hh;
	double scaled_x = x * xscale;
	double scaled_y = v * yscale;
	if (v > 0)
	{
		//we add the scaled x value to orig. so orig.x  +  x*xscale; same thing for y
		tl=Point( orig.x + scaled_x,orig.y - scaled_y);
		//we add 1 pixel so that the rectangle fits perfectly
		ww = xscale+1;
		hh = scaled_y+1;
	}
	else if (v < 0)
	{
		tl = Point(orig.x + scaled_x, orig.y);
		ww = xscale + 1;
		hh = -scaled_y + 1;
	}

	if (v != 0)
	{
		rects.push_back(new Graph_lib::Rectangle{ tl,ww,hh });
		rects[rects.size() - 1].set_fill_color(Color::red);
	}
}
void Bar_graph::set_bar_label(int i, string label)
{
	blabs.push_back(new Text{ Point(orig.x+i * xscale,rects[i].point(0).y-4),label });
	blabs[blabs.size() - 1].set_color(rects[i].fill_color());
}
void Bar_graph::draw_lines() const
{
	if (color().visibility())
	{
		for (int i = 0; i < rects.size(); ++i)
			rects[i].draw();

		//labels
		if (glab.label().length() > 0) glab.draw();
		for (int i = 0; i < blabs.size(); ++i)
			if (blabs[i].label().length() > 0) blabs[i].draw();
	}
}

int main()
try
{
	using namespace Graph_lib;

	Point tl(150, 150);
	constexpr int xmax{ 1000 };
	constexpr int ymax{ 1000 };
	Simple_window win(tl, xmax, ymax, "My window");
	win.wait_for_button();

	const Point orig{xmax/2,ymax/2};
	constexpr int x_offset{ 50 };
	constexpr int y_offset{ 50 };
	constexpr int x_length{ xmax - x_offset * 2 };
	constexpr int y_length{ ymax - y_offset * 2 };
	Axis xa{ Axis::x,Point(x_offset,orig.y),x_length,30,"1==30" };
	Axis ya{ Axis::y,Point(orig.x,ymax-y_offset),y_length,30,"1==30" };
	win.attach(xa);
	win.attach(ya);
	constexpr int r_min{ -15 };
	constexpr int r_max{ 15};
	constexpr int x_scale{ 30 };
	constexpr int y_scale{ 30 };
	constexpr int n_points{ 400 };
	//myFct can't work because we can't reset the actual shape points once created
	//myFct f1{cos,r_min,r_max,orig,n_points,x_scale,y_scale };
	//f1.reset(cos,r_min, r_max, orig, 50, x_scale, y_scale);
	//f1.set_color(Color::blue);
	//win.attach(f1);

	/*
	Function f1{ cos,r_min,r_max,orig,n_points,x_scale,y_scale };
	f1.set_color(Color::blue);
	win.attach(f1);
	Function f2{ sin,r_min,r_max,orig,n_points,x_scale,y_scale };
	f2.set_color(Color::green);
	win.attach(f2);
	Function f3{ sum_sin_cos,r_min,r_max,orig,n_points,x_scale,y_scale };
	f3.set_color(Color::cyan);
	win.attach(f3);
	Function f4{ sum_sin_cos_sq,r_min,r_max,orig,n_points,x_scale,y_scale };
	f4.set_color(Color::magenta);
	win.attach(f4);

	Text scsq_label(Point(x_offset, orig.y - 60), "sin(x) * sin(x) + cos(x) * cos(x)");
	scsq_label.set_color(Color::magenta);
	win.attach(scsq_label);
	Text sg_label(Point(x_offset, orig.y + 60), "sin(x)");
	sg_label.set_color(Color::green);
	win.attach(sg_label);
	Text cg_label(Point(x_offset, orig.y + 80), "cos(x)");
	cg_label.set_color(Color::blue);
	win.attach(cg_label);
	Text scg_label(Point(x_offset, orig.y + 100), "sin(x) + cos(x)");
	scg_label.set_color(Color::cyan);
	win.attach(scg_label);
	*/

	/*
	Function real_exp{ exp,r_min,r_max,orig,n_points,x_scale,y_scale };
	real_exp.set_color(Color::blue);
	win.attach(real_exp);
	for (int n = 0; n < 50; ++n) {
		ostringstream ss;
		ss << "exp approximation; n==" << n;
		win.set_label(ss.str());
		// get next approximation:
		//lambda expression not working
		//Function e{[n](double x){ return expe(x,n); },r_min,r_max,orig,n_points,x_scale,y_scale };
		//we had to declare a global variable to get around this
		expN_number_of_terms = n;
		Function e{expN,r_min,r_max,orig,n_points,x_scale,y_scale };
		win.attach(e);
		win.wait_for_button();
		win.detach(e);
	}
	*/
	/*
	for (int n = 0; n < 100; ++n) {
		ostringstream ss;
		ss << "n approximation; n==" << n;
		win.set_label(ss.str());
		leib_number_of_terms = n;
		Function e{ leibN,r_min,r_max,orig,n_points,x_scale,y_scale };
		e.set_color(Color::blue);
		win.attach(e);
		win.wait_for_button();
		win.detach(e);
	}

	Bar_graph my_graph{ orig,x_scale,y_scale };

	for (int i = 7; i >-8; --i)
	{
		my_graph.add_value(i);
	}

	win.attach(my_graph);
	win.wait_for_button();
	*/

	vector<double> vals{ -1,2,4,2,-5,5,6,9,15,4 };
	Bar_graph my_graph2{ orig,vals,x_scale,y_scale };
	my_graph2.set_bar_color(0, Color::blue);
	my_graph2.set_bar_color(3, Color::white);
	my_graph2.set_bar_color(4, Color::green);
	my_graph2.set_graph_label("my_graph2");
	my_graph2.set_bar_label(2,"apples");
	my_graph2.set_bar_label(4,"bananas");
	my_graph2.set_bar_label(7,"kiwis");
	win.attach(my_graph2);
	win.wait_for_button();
	return 0;
}

catch (exception& e)
{
	cout << e.what() << endl;
	return 1;
}
catch (...)
{
	cout << "Exiting" << endl;
	return 2;
}