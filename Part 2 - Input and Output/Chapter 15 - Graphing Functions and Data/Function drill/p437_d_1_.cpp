#include "Simple_window.h"
#include "Graph.h"

double one(double x) { return 1; }
double slope(double x) { return x / 2; }
double square(double x) { return x * x; }
double sloping_cos(double x) { return slope(x)+cos(x); }
int main()							//IT IS IMPORTANT TO USE SYMBOLIC CONSTANTS - to avoid magic ones
{
	using namespace Graph_lib;

	Point tl(150, 150);
	constexpr int xmax{ 600 };
	constexpr int ymax{ 600 };
	Simple_window win(tl, xmax, ymax, "My window");
	win.wait_for_button();

	constexpr int x_length{ 400 };
	constexpr int y_length{ 400 };
	Point orig{ 300,300 };

	Axis xa{ Axis::x,Point(orig.x - x_length / 2,orig.y),x_length,20,"1==20" };
	Axis ya{ Axis::y,Point(orig.x,orig.y+y_length/2),x_length,20,"1==20" };
	xa.set_color(Color::red);
	ya.set_color(Color::red);

	win.attach(xa);
	win.attach(ya);

	constexpr int r_min{ -10 };	//range min and max (both included)
	constexpr int r_max{ 10 };
	constexpr int n_points{ 400 };	//how many points to calculate for a function - the more there are, the more "complex" the shape will be
	constexpr int x_scale{ 20 };	//amount of pixels equal to 1 unit
	constexpr int y_scale{ 20 };
//will draw a line that goes from r_min to r_max included (well, in this case the scaling is wrong 25!=20, so it will vary a bit), 
// with 0,0 at point orig
	//Function f1{ one,r_min,r_max,orig,n_points };
//using the scales now
	Function f1{ one,r_min,r_max,orig,n_points,x_scale,y_scale };
	Function f2{ slope,r_min,r_max,orig,n_points,x_scale,y_scale };
	Text tf2{ { 100,orig.y+y_length/5},"x/2" };
	Function f3{ square,r_min,r_max,orig,n_points,x_scale,y_scale };
	Function f4{ cos,r_min,r_max,orig,n_points,x_scale,y_scale };
	Function f5{ sloping_cos,r_min,r_max,orig,n_points,x_scale,y_scale };
	f4.set_color(Color::blue);
	win.attach(f1);
	win.attach(f2);
	win.attach(tf2);
	win.attach(f3);
	win.attach(f4);
	win.attach(f5);
	win.wait_for_button();
}