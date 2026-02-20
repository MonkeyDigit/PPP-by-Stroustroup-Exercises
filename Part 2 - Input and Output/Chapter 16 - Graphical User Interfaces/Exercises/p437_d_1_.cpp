#include "Simple_window.h"
#include "Graph.h"
#include "GUI.h"
#define PI 3.141592653589

//My window - has next and quit button------------------------------------------------------
struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);
	void wait_for_button();
private:
	Button next_button;
	Button quit_button;
	bool next_button_pushed;
	
	//the keyword static is there to make sure that cb_next() can be called as an ordinary 
	//function, that is, not as a C++ member function invoked for a specific object
	//static void cb_next(Address, Address);
	//static void cb_quit(Address, Address);

	void next();
	void quit();

};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	quit_button{ Point{x_max() - 70,0},70,20,"Quit",[](Address, Address pw) {reference_to<My_window>(pw).quit(); } },
	next_button{ Point{x_max() - 150,0},70,20,"Next",[](Address, Address pw) {reference_to<My_window>(pw).next(); } },
	next_button_pushed{false}
{
	attach(quit_button);
	attach(next_button);
}

/* We used lambda expressions instead
void My_window::cb_quit(Address, Address pw)
{
	reference_to<My_window>(pw).quit();
}

void My_window::cb_next(Address, Address pw)
{
	reference_to<My_window>(pw).next();
}
*/

void My_window::wait_for_button()
// modified event loop
// handle all events (as per default), but quit when button_pushed becomes true
// this allows graphics without control inversion
{
	while (!next_button_pushed) Fl::wait();	//when someone clicks our “Next” button, wait() calls cb_next() and returns(to our “wait loop”).
										//To proceed in wait_for_button(), next() just has to set the Boolean variable next_button_pushed to true
	next_button_pushed = false;
	Fl::redraw();
}

void My_window::quit()
{
	hide();
}

void My_window::next()
{
	next_button_pushed = true;
}

//Checker board window - has a 4 by 4 grid of buttons ----------------------------------------------------------
struct Checker_board : My_window {
	Checker_board(Point xy, int w, int h, const string& title);
private:
	Vector_ref<Button> buttons;
	void change0() { cout << "b0 x: " << buttons[0].loc.x << " y: " << buttons[0].loc.y << '\n'; }
	void change1() { cout << "b1 x: " << buttons[1].loc.x << " y: " << buttons[1].loc.y << '\n'; }
	void change2() { cout << "b2 x: " << buttons[2].loc.x << " y: " << buttons[2].loc.y << '\n'; }
	void change3() { cout << "b3 x: " << buttons[3].loc.x << " y: " << buttons[3].loc.y << '\n'; }
	void change4() { cout << "b4 x: " << buttons[4].loc.x << " y: " << buttons[4].loc.y << '\n'; }
	void change5() { cout << "b5 x: " << buttons[5].loc.x << " y: " << buttons[5].loc.y << '\n'; }
	void change6() { cout << "b6 x: " << buttons[6].loc.x << " y: " << buttons[6].loc.y << '\n'; }
	void change7() { cout << "b7 x: " << buttons[7].loc.x << " y: " << buttons[7].loc.y << '\n'; }
	void change8() { cout << "b8 x: " << buttons[8].loc.x << " y: " << buttons[8].loc.y << '\n'; }
	void change9() { cout << "b9 x: " << buttons[9].loc.x << " y: " << buttons[9].loc.y << '\n'; }
	void change10() { cout << "b10 x: " << buttons[10].loc.x << " y: " << buttons[10].loc.y << '\n'; }
	void change11() { cout << "b11 x: " << buttons[11].loc.x << " y: " << buttons[11].loc.y << '\n'; }
	void change12() { cout << "b12 x: " << buttons[12].loc.x << " y: " << buttons[12].loc.y << '\n'; }
	void change13() { cout << "b13 x: " << buttons[13].loc.x << " y: " << buttons[13].loc.y << '\n'; }
	void change14() { cout << "b14 x: " << buttons[14].loc.x << " y: " << buttons[14].loc.y << '\n'; }
	void change15() { cout << "b15 x: " << buttons[15].loc.x << " y: " << buttons[15].loc.y << '\n'; }
};

Checker_board::Checker_board(Point xy, int w, int h, const string& title)
	:My_window{xy,w,h,title}
{
	int side_y = (y_max() - 20) / 4;
	int side_x = x_max()/ 4;
	buttons.push_back(new Button{ Point{0,20}, side_x, side_y, "b0", [](Address, Address pw) {reference_to<Checker_board>(pw).change0(); } });
	buttons.push_back(new Button{ Point{side_x,20}, side_x, side_y, "b1", [](Address, Address pw) {reference_to<Checker_board>(pw).change1(); } });
	buttons.push_back(new Button{ Point{side_x *2,20}, side_x, side_y, "b2", [](Address, Address pw) {reference_to<Checker_board>(pw).change2(); } });
	buttons.push_back(new Button{ Point{side_x * 3,20}, side_x, side_y, "b3", [](Address, Address pw) {reference_to<Checker_board>(pw).change3(); } });

	buttons.push_back(new Button{ Point{0,20+side_y}, side_x, side_y, "b4", [](Address, Address pw) {reference_to<Checker_board>(pw).change4(); } });
	buttons.push_back(new Button{ Point{side_x,20 + side_y}, side_x, side_y, "b5", [](Address, Address pw) {reference_to<Checker_board>(pw).change5(); } });
	buttons.push_back(new Button{ Point{side_x *2,20 + side_y}, side_x, side_y, "b6", [](Address, Address pw) {reference_to<Checker_board>(pw).change6(); } });
	buttons.push_back(new Button{ Point{side_x * 3,20 + side_y}, side_x, side_y, "b7", [](Address, Address pw) {reference_to<Checker_board>(pw).change7(); } });

	buttons.push_back(new Button{ Point{0,20+side_y *2}, side_x, side_y, "b8", [](Address, Address pw) {reference_to<Checker_board>(pw).change8(); }});
	buttons.push_back(new Button{ Point{side_x,20 + side_y * 2}, side_x, side_y, "b9", [](Address, Address pw) {reference_to<Checker_board>(pw).change9(); } });
	buttons.push_back(new Button{ Point{side_x * 2,20 + side_y * 2}, side_x, side_y, "b10", [](Address, Address pw) {reference_to<Checker_board>(pw).change10(); } });
	buttons.push_back(new Button{ Point{side_x * 3,20 + side_y * 2}, side_x, side_y, "b11", [](Address, Address pw) {reference_to<Checker_board>(pw).change11(); } });

	buttons.push_back(new Button{ Point{0,20 + side_y *3}, side_x, side_y, "b12", [](Address, Address pw) {reference_to<Checker_board>(pw).change12(); } });
	buttons.push_back(new Button{ Point{side_x,20 + side_y *3}, side_x, side_y, "b13", [](Address, Address pw) {reference_to<Checker_board>(pw).change13(); } });
	buttons.push_back(new Button{ Point{side_x * 2,20 + side_y *3}, side_x, side_y, "b14", [](Address, Address pw) {reference_to<Checker_board>(pw).change14(); } });
	buttons.push_back(new Button{ Point{side_x * 3,20 + side_y *3}, side_x, side_y, "b15", [](Address, Address pw) {reference_to<Checker_board>(pw).change15(); } });

	for (int i = 0; i < buttons.size(); ++i)
	{
		attach(buttons[i]);
	}
}

//Moving image window - has an image covering a button that moves randomly------------------------------------------------------------------
#include<random>
inline int rand_int(int min, int max)
{
	static default_random_engine ran;
	return uniform_int_distribution<>{min, max}(ran);
}

struct Moving_image : My_window {
	Moving_image(Point xy, int w, int h, const string& title, const string& url);
private:
	Button image_button;
	int side_y;
	int side_x;
	Image image{ Point{0,0},""};
	void move_image_button();
};

Moving_image::Moving_image(Point xy, int w, int h, const string& title, const string& url)
	: My_window{ xy,w,h,title },
	image_button{ Point{0,20},x_max() / 4,(y_max() - 20) / 4,"im_b",[](Address, Address pw) {reference_to<Moving_image>(pw).move_image_button(); } },
	image(Point{0,20},url)
{
	side_y = (y_max() - 20) / 4;
	side_x = x_max() / 4;
	attach(image_button);
	image.set_mask(Point{ 0,0 }, side_x, side_y);
	attach(image);
}

void Moving_image::move_image_button()
{
	int rnd_x = rand_int(0, 3)*side_x;
	int rnd_y = rand_int(0, 3)*side_y+20;
	image_button.move(-(image_button.loc.x - rnd_x), -(image_button.loc.y - rnd_y));
	image.move(-(image.point(0).x - rnd_x), -(image.point(0).y - rnd_y));
	redraw();
}

//Shapes window - can be used to create specific shapes ---------------------------------------------------------------

//shapes for Shapes_window

struct Hexagon : Closed_polyline {
	Hexagon(Point center, int radius);
	Point center() const { return c; };
	int radius() const { return r; };
private:
	Point c;
	int r;
};
Hexagon::Hexagon(Point center, int radius)
	: c(center),r(radius)
{
	if (r <= 0) error("Non positive length");
	for (int i = 0; i < 360; i += 60)
	{
		double x = c.x + cos(i * PI / 180.0) * r;
		double y = c.y - sin(i * PI / 180.0) * r;
		add(Point(x, y));
	}
}

struct Square : Closed_polyline {
	Square(Point xy, int length);
	int get_length() const { return length; }
private:
	int length;
};

Square::Square(Point xy, int length)
	: length(length)
{
	if (length <= 0) error("Non positive length");
	add(xy);
	add(Point{xy.x,xy.y+length});
	add(Point{xy.x+length,xy.y+length});
	add(Point{xy.x+length,xy.y});
}

struct Triangle : Closed_polyline{
	Triangle(Point center, int edge_length);
	Point center() const { return c; };
	int edge_length() const { return el; };
private:
	Point c;
	int el;
};
Triangle::Triangle(Point center, int edge_length)
	:c{ center }, el{edge_length}
{
	int h = sin(PI / 3) * el;
	add(Point{ c.x - el / 2,c.y + h /2  });
	add(Point{ c.x ,c.y - h/2});
	add(Point{ c.x + el / 2,c.y + h /2 });
}

struct Shapes_window : Window {
	Shapes_window(Point xy, int w, int h, const string& title);
private:
	Button quit_button; //end program
	Button shape_menu_button;
	Menu shape_menu;
	In_box x_in;
	In_box y_in;
	Out_box xy_out;

	int radius;
	Vector_ref<Shape> shapes;
	void quit_pressed() { hide(); }
	void shape_menu_pressed() { shape_menu_button.hide(); shape_menu.show(); };
	void circle_pressed();
	void hexagon_pressed();
	void square_pressed();
	void triangle_pressed();
};

Shapes_window::Shapes_window(Point xy, int w, int h, const string& title)
	: Window{xy,w,h,title},
	radius{50},
	quit_button{ Point{x_max() - 70,0},70,20,"Quit", [](Address, Address pw) {reference_to<Shapes_window>(pw).quit_pressed(); } },
	shape_menu_button{ Point{x_max() - 80,40},80,20,"shape menu", [](Address, Address pw) {reference_to<Shapes_window>(pw).shape_menu_pressed(); } },
	shape_menu{Point{x_max()-80,40},80,20,Menu::vertical,"shape menu"},
	x_in{Point{230,0},50,20,"x: "},
	y_in{Point{350,0},50,20,"y: "},
	xy_out{Point{90,0},100,20,"drawn at (x,y)"}
{
	shape_menu.attach(new Button{ Point{0,0},0,0,"circle", [](Address, Address pw) {reference_to<Shapes_window>(pw).circle_pressed(); } });
	shape_menu.attach(new Button{ Point{0,0},0,0,"hexagon", [](Address, Address pw) {reference_to<Shapes_window>(pw).hexagon_pressed(); } });
	shape_menu.attach(new Button{ Point{0,0},0,0,"square", [](Address, Address pw) {reference_to<Shapes_window>(pw).square_pressed(); } });
	shape_menu.attach(new Button{ Point{0,0},0,0,"triangle", [](Address, Address pw) {reference_to<Shapes_window>(pw).triangle_pressed(); } });
	attach(x_in);
	attach(y_in);
	attach(shape_menu);
	attach(xy_out);
	xy_out.put("no point");
	shape_menu.hide();
	attach(shape_menu_button);
	attach(quit_button);
}

void Shapes_window::circle_pressed()
{
	int x = x_in.get_int();
	int y = y_in.get_int();
	shapes.push_back(new Circle{ Point{x,y},radius });
	attach(shapes[shapes.size() - 1]);
	shape_menu.hide();
	shape_menu_button.show();
	// update current position readout:
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());
}
void Shapes_window::hexagon_pressed()
{
	int x = x_in.get_int();
	int y = y_in.get_int();
	/*
	Closed_polyline hex;
	for (int i = 0; i < 360; i += 60)
	{
		hex.add(Point( x + cos(i * PI / 180.0) * radius,y - sin(i * PI / 180.0)*radius ));
	}
	shapes.push_back(new Closed_polyline{ hex.point(0), hex.point(1), hex.point(2),hex.point(3), hex.point(4),hex.point(5) });
	*/
	shapes.push_back(new Hexagon{ Point{x,y},50 });
	attach(shapes[shapes.size() - 1]);
	shape_menu.hide();
	shape_menu_button.show();
	// update current position readout:
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());
}

void Shapes_window::square_pressed()
{
	int x = x_in.get_int();
	int y = y_in.get_int();
	//shapes.push_back(new Graph_lib::Rectangle{ Point{x,y},100,100 });
	shapes.push_back(new Square{Point{x,y},radius*2});
	attach(shapes[shapes.size() - 1]);
	shape_menu.hide();
	shape_menu_button.show();
	// update current position readout:
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

}
void Shapes_window::triangle_pressed()
{
	int x = x_in.get_int();
	int y = y_in.get_int();
	/*
	Closed_polyline triangle;
	for (int i = 0; i <360 ; i += 120)
	{
		triangle.add(Point(x + cos(i * PI / 180.0) * radius, y - sin(i * PI / 180.0) * radius));
	}

	shapes.push_back(new Closed_polyline{ triangle.point(0), triangle.point(1), triangle.point(2)});
	*/
	shapes.push_back(new Triangle(Point{x,y},sin(PI/3)*radius*2));
	attach(shapes[shapes.size() - 1]);
	shape_menu.hide();
	shape_menu_button.show();
	// update current position readout:
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());
}

//Moving shape window-------------------------------------------------------------------------------

struct Moving_shape : Window {
	Moving_shape(Point xy, int w, int h, const string& title);
private:
	Circle circle;
	Button next_button;
	Button quit_button;
	void next();
	void quit();
};

Moving_shape::Moving_shape(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	quit_button{ Point{x_max() - 70,0},70,20,"Quit",[](Address, Address pw) {reference_to<Moving_shape>(pw).quit(); } },
	next_button{ Point{x_max() - 150,0},70,20,"Next",[](Address, Address pw) {reference_to<Moving_shape>(pw).next(); } },
	circle{ {x_max() / 2,y_max() / 2},40 }
{
	attach(circle);
	attach(quit_button);
	attach(next_button);
}

void Moving_shape::next()
{
	int rnd_x = rand_int(0, x_max()-circle.radius()*2);
	int rnd_y = rand_int(0, y_max()- circle.radius() * 2);
	circle.move(-(circle.point(0).x - rnd_x), -(circle.point(0).y - rnd_y));
	redraw();
}

void Moving_shape::quit()
{
	hide();
}


int main()
try
{
	using namespace Graph_lib;
	Point tl{ 150,150 };
	constexpr int xmax = 600;
	constexpr int ymax = 600;
	/*
	My_window my_win{ tl,xmax,ymax,"My window" };

	Circle some_circle{ Point{300,300},75 };
	my_win.attach(some_circle);
	my_win.wait_for_button();

	Graph_lib::Rectangle some_rect{ Point{400,400},150,100 };
	my_win.attach(some_rect);
	my_win.wait_for_button();

	Checker_board check_board{ tl,xmax,ymax,"Checker board" };

	Moving_image my_image{ tl,600,600,"The moving image","image.jpg" };

	Shapes_window my_shapes{ tl,xmax,ymax,"Shapes window" };
	*/
	Moving_shape move_shape{ tl,xmax,ymax,"Moving shape" };
	return gui_main();	//by putting gui_main() the window won't close unless we press the quit button
}

catch (exception& e)
{
	cerr << "Error: " << e.what()<<'\n';
	return 1;
}

catch (...)
{
	cerr << "Unknown error"<<'\n';
	return 2;
}