#include "Simple_window.h"
#include "Graph.h"
#include "Windows.h"
#include "GUI.h"


struct Lines_window : Window {
	Lines_window(Point xy, int w, int h, const string& title);
private:
	//data
	Open_polyline lines;
	Button next_button; // add (next_x,next_y) to lines
	Button quit_button; //quit
	In_box next_x;
	In_box next_y;
	Out_box xy_out;

	Menu color_menu;
	Button color_menu_button;

	Menu style_menu;
	Button style_menu_button;


	void change_color(Color c) { lines.set_color(c); }
	void hide_color_menu() { color_menu.hide(); color_menu_button.show(); }
	//style menu
	void hide_style_menu() { style_menu.hide(); style_menu_button.show(); }
	void change_style(Line_style sty) { lines.set_style(sty); }

	// actions invoked by the callbacks
	//window
	void next();
	void quit();

	//color menu
	void red_pressed() { change_color(Color::red); hide_color_menu(); }
	void blue_pressed() { change_color(Color::blue); hide_color_menu(); }
	void black_pressed() { change_color(Color::black); hide_color_menu(); }
	void color_menu_pressed() { color_menu_button.hide(); color_menu.show(); }

	//style menu
	void solid_pressed() { change_style(Line_style(Line_style::solid)); hide_style_menu(); }
	void dash_pressed() { change_style(Line_style(Line_style::dash)); hide_style_menu(); }
	void dot_pressed() { change_style(Line_style(Line_style::dot)); hide_style_menu(); }
	void style_menu_pressed() { style_menu_button.hide(); style_menu.show(); }

	//Callback functions
	//window
	static void cb_next(Address, Address);
	static void cb_quit(Address, Address);

	//color menu
	static void cb_red(Address, Address); // callback for red button
	static void cb_blue(Address, Address); // callback for blue button
	static void cb_black(Address, Address); // callback for black button
	static void cb_color_menu(Address, Address);

	//style menu
	static void cb_solid(Address, Address);
	static void cb_dash(Address, Address);
	static void cb_dot(Address, Address);
	static void cb_style_menu(Address, Address);
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	next_button{ Point{x_max()-150,0}, 70, 20, "Next point", cb_next },
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit", cb_quit },
	next_x{Point{x_max()-310,0}, 50, 20, "next x:"},
	next_y{Point{x_max()-210,0}, 50, 20, "next y:"},
	xy_out{Point{100,0}, 100, 20, "current (x,y):"},
	color_menu{ Point{x_max()-70,30},70,20,Menu::vertical,"color" },
	color_menu_button{ Point{x_max()-80,30}, 80, 20, "color menu", cb_color_menu },
	style_menu{ Point{x_max()-70,100},70,20,Menu::vertical, "style"},
	style_menu_button{ Point{x_max()-80,100}, 80, 20, "style menu", cb_style_menu }
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point"); //IMPORTANT: we can put something in the out_box only after attaching it to the window
	color_menu.attach(new Button{ Point(0,0),0,0,"red",cb_red});
	color_menu.attach(new Button{ Point(0,0),0,0,"blue",cb_blue });
	color_menu.attach(new Button{ Point(0,0),0,0,"black",cb_black });
	attach(color_menu);
	color_menu.hide();
	attach(color_menu_button);

	style_menu.attach(new Button{ Point(0,0),0,0,"solid",cb_solid });
	style_menu.attach(new Button{ Point(0,0),0,0,"dash",cb_dash });
	style_menu.attach(new Button{ Point(0,0),0,0,"dot",cb_dot });
	attach(style_menu);
	style_menu.hide();
	attach(style_menu_button);
	attach(lines);
}

void Lines_window::quit()
{
	hide(); // curious FLTK idiom to delete window
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{ x,y });
	// update current position readout:
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());
	redraw();
}

//Callback functions-----------------------------------------------------------------
//window
void Lines_window::cb_next(Address, Address pw)
// call Lines_window::next() for the window located at pw
{
	reference_to<Lines_window>(pw).next();
}

void Lines_window::cb_quit(Address, Address pw)
{
	reference_to<Lines_window>(pw).quit();
}

//Color menu--------------------------------------------
void Lines_window::cb_color_menu(Address, Address pw)
{
	reference_to<Lines_window>(pw).color_menu_pressed();
}
void Lines_window::cb_red(Address, Address pw)
{
	reference_to<Lines_window>(pw).red_pressed();
}
void Lines_window::cb_black(Address, Address pw)
{
	reference_to<Lines_window>(pw).black_pressed();
}
void Lines_window::cb_blue(Address, Address pw)
{
	reference_to<Lines_window>(pw).blue_pressed();
}

//Style menu---------------------------------------
void Lines_window::cb_solid(Address, Address pw)
{
	reference_to<Lines_window>(pw).solid_pressed();
}
void Lines_window::cb_dash(Address, Address pw)
{
	reference_to<Lines_window>(pw).dash_pressed();
}
void Lines_window::cb_dot(Address, Address pw)
{
	reference_to<Lines_window>(pw).dot_pressed();
}
void Lines_window::cb_style_menu(Address, Address pw)
{
	reference_to<Lines_window>(pw).style_menu_pressed();
}

int main()
try
{
	using namespace Graph_lib;
	Point tl{ 150,150 };
	Lines_window lwin{ tl,800,800,"Lines" };

	return gui_main();
}

catch (exception& e)
{
	cerr << "Error: " << e.what();
	return 1;
	keep_window_open();
}

catch (...)
{
	cerr << "Unknown error";
	return 2;
	keep_window_open();
}