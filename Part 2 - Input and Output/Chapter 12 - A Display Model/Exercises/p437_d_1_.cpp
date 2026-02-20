#include "Simple_window.h"
#include "Graph.h"

int main()
try
{
	using namespace Graph_lib;
	Point tl(150, 150);
	Simple_window win(tl, 1000, 600, "My window");
	win.wait_for_button();
	/*
	Graph_lib::Rectangle r{ Point{ 300,300 }, 400, 200 };
	Graph_lib::Polygon p;

	p.add(Point{ 300,50 });
	p.add(Point{ 300,250 });
	p.add(Point{ 700,250});
	p.add(Point{ 700,50 });
	r.set_color(Color::blue);
	p.set_color(Color::red);
	//r.set_style(Line_style(Line_style::solid,4));
	win.attach(r);
	win.attach(p);

	Graph_lib::Rectangle rect{ Point{400,300},100,30 };
	Text t{ Point{420,314},"Howdy!" };
	win.attach(rect);
	win.attach(t);
	win.wait_for_button();

	Text initial_1{ Point{200,280},"M" };
	Text initial_2{ Point{320,280},"F" };
	initial_1.set_font_size(150);
	initial_2.set_font_size(150);
	initial_1.set_color(Color::dark_blue);
	initial_2.set_color(Color::dark_red);
	win.attach(initial_1);
	win.attach(initial_2);
	win.wait_for_button();

	Line x1{ Point{200,100},Point{350,100} };
	Line x2{ Point{200,150},Point{350,150} };

	Line y1{ Point{250,200},Point{250,50} };
	Line y2{ Point{300,200},Point{300,50} };

	win.attach(x1);
	win.attach(x2);
	win.attach(y1);
	win.attach(y2);
	Graph_lib::Rectangle in_rect{ Point{100,100},x_max() * 2 / 3,y_max() * 3 / 4 };
	Graph_lib::Rectangle frame_rect{ Point{50,50},x_max() * 2 / 3+100,y_max() * 3 / 4+100 };
	frame_rect.set_color(Color::red);
	win.attach(in_rect);
	win.attach(frame_rect);
	win.wait_for_button();

	Graph_lib::Polygon my_house;
	my_house.add(Point{ 100,550 });
	my_house.add(Point{ 100,250 });
	my_house.add(Point{ 400,200 });
	my_house.add(Point{ 700,250 });
	my_house.add(Point{ 700,550 });
	Graph_lib::Rectangle door{ Point{300,450},200,100 };
	Graph_lib::Rectangle window1{ Point{300,300},50,50 };
	Graph_lib::Rectangle window2{ Point{500,300},50,50 };

	my_house.set_fill_color(Color::yellow);
	door.set_fill_color(Color::dark_yellow);
	window1.set_fill_color(Color::cyan);
	window2.set_fill_color(Color::cyan);
	win.attach(my_house);
	win.attach(door);
	win.attach(window1);
	win.attach(window2);
	win.wait_for_button();

	Circle c1{ Point{400,280},50 };
	Circle c2{ Point{455,300},50 };
	Circle c3{ Point{510,280},50 };
	Circle c4{ Point{565,300},50 };
	Circle c5{ Point{620,280},50 };
	c1.set_style(Line_style(Line_style::solid, 5));
	c2.set_style(Line_style(Line_style::solid, 5));
	c3.set_style(Line_style(Line_style::solid, 5));
	c4.set_style(Line_style(Line_style::solid, 5));
	c5.set_style(Line_style(Line_style::solid, 5));
	c1.set_color(Color::blue);
	c2.set_color(Color::yellow);
	c3.set_color(Color::green);
	c4.set_color(Color::black);
	c5.set_color(Color::red);

	win.attach(c1);
	win.attach(c2);
	win.attach(c3);
	win.attach(c4);
	win.attach(c5);
	win.wait_for_button();

	//Image works on release mode, don't know why it doesn't in debug
	Image ii{ Point{300,400},"image.jpg" };
	win.attach(ii);
	win.wait_for_button();
	*/


	return 0;
}
catch (exception& e) {
	cerr << "error: " << e.what();
	return 1;
}
catch (...) {
	cerr << "error";
	return 2;
}