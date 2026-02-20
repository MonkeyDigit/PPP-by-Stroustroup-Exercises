#include "Simple_window.h"
#include "Graph.h"
#include <iostream>
# define PI 3.14159265359

class Smiley : public Circle {
public:
	using Circle::Circle;	//we use the circle's constructor
	void draw_lines() const;	//we need to override draw_lines() to draw the eyes and mouth
	void set_style(Line_style sty);
	void set_color(Color col);
private:
	Circle eye1{ {Circle::center().x-Circle::radius()/2, Circle::center().y - Circle::radius() / 2}, Circle::radius()/8};
	Circle eye2{ {Circle::center().x+Circle::radius()/2, Circle::center().y - Circle::radius() / 2}, Circle::radius()/8};
	Circle mouth{ Circle::center(), int(Circle::radius() /2) }; //we just draw part of it
};

void Smiley::draw_lines() const
{
	Circle::draw_lines();	//first draw the main circle part
	eye1.draw_lines();		//then the eyes
	eye2.draw_lines();
	if (color().visibility())	//and the mouth
			fl_arc(mouth.point(0).x, mouth.point(0).y, mouth.radius() * 2, mouth.radius() * 2, 180, 360);
}

void Smiley::set_style(Line_style sty)
{
	Circle::set_style(sty);
	eye1.set_style(sty);
	eye2.set_style(sty);
	mouth.set_style(sty);
}

void Smiley::set_color(Color col)
{
	Circle::set_color(col);
	eye1.set_color(col);
	eye2.set_color(col);
	mouth.set_color(col);
}

//Frown-----------------------------------
class Frowny : public Circle {
public:
	using Circle::Circle;
	void draw_lines() const;
	void set_style(Line_style sty);
	void set_color(Color col);
private:
	Circle eye1{ {Circle::center().x - Circle::radius() / 2, Circle::center().y - Circle::radius() / 2}, Circle::radius() / 8 };
	Circle eye2{ {Circle::center().x + Circle::radius() / 2, Circle::center().y - Circle::radius() / 2}, Circle::radius() / 8 };
	Circle mouth{ {Circle::center().x,Circle::center().y+ int(Circle::radius() / 2)}, int(Circle::radius() / 2) }; //we just draw part of it
};

void Frowny::draw_lines() const
{
	Circle::draw_lines();	//first draw the main circle part
	eye1.draw_lines();		//then the eyes
	eye2.draw_lines();
	if (color().visibility())
		fl_arc(mouth.point(0).x, mouth.point(0).y, mouth.radius() * 2, mouth.radius() * 2, 0, 180);
}

void Frowny::set_style(Line_style sty)
{
	Circle::set_style(sty);
	eye1.set_style(sty);
	eye2.set_style(sty);
	mouth.set_style(sty);
}

void Frowny::set_color(Color col)
{
	Circle::set_color(col);
	eye1.set_color(col);
	eye2.set_color(col);
	mouth.set_color(col);
}
/*	For some reason the initializer list doesn't work
class Smiley_hat : public Smiley {
public:
	using Smiley::Smiley;
	void draw_lines() const;
private:
	Graph_lib::Polygon hat={ Point{Smiley::center().x+int(cos(120)*Smiley::radius()),Smiley::center().y + int(sin(120) * Smiley::radius())},
							 Point{Smiley::center().x,Smiley::center().y-Smiley::radius()*2},
							 Point{Smiley::center().x + int(cos(60) * Smiley::radius()),Smiley::center().y + int(sin(60) * Smiley::radius())}
	};
};
*/

class Immobile_circle : public Circle {
public:
	using Circle::Circle;
	void move() { };
};

//striped rectangle-----------------------------------
struct Striped_rectangle : Rectangle {
	using Rectangle::Rectangle;
	void set_stripe_color(Color col);
	void draw_lines() const;
private:
	int spacing{4};
	int line_width{2};
	Lines stripes;
};
void Striped_rectangle::set_stripe_color(Color col)
{
	for (int i = spacing; i < Rectangle::height(); i += spacing)
	{
		stripes.add({ Rectangle::point(0).x,Rectangle::point(0).y + i },
			{ Rectangle::point(0).x + Rectangle::width() - 1,Rectangle::point(0).y + i });
	}
	stripes.set_style(Line_style(Line_style::solid, line_width));
	stripes.set_color(col);
}

void Striped_rectangle::draw_lines() const
{
	Rectangle::draw_lines();
	stripes.draw();
}

//striped circle-----------------------------------------
struct Striped_circle : Circle {	//by declaring a struct instead of a class, all public members from Circle are already inherited
	using Circle::Circle;
	void set_stripe_color(Color col);
	void draw_lines() const;
private:
	int spacing{ 10 };
	int line_width{ 2 };
	Lines stripes;
};

void Striped_circle::set_stripe_color(Color col)
{
	for (int i = spacing; i < Circle::radius()*2; i += spacing)
	{
		int x_dist = sqrt(pow(Circle::radius(), 2) - pow(Circle::radius()-i, 2));
		stripes.add({ Circle::center().x-x_dist+1,Circle::center().y-Circle::radius()+i},
			{ Circle::center().x + x_dist-1,Circle::center().y - Circle::radius() + i });
	}
	stripes.set_style(Line_style(Line_style::solid, line_width));
	stripes.set_color(col);
}

void Striped_circle::draw_lines() const
{
	Circle::draw_lines();
	stripes.draw();
}

struct Regular_octagon : Polygon {
	Regular_octagon(Point p, int rr);
	Point center() const { return c; }
	int radius() const { return r; }
	void add() {}
private:
	Point c;
	int r;
};
Regular_octagon::Regular_octagon(Point p, int rr) : c(p), r(rr)
{
	if (r <= 0) error("Invalid radius");
	int n = 8;
	for (int i = 0; i < n; ++i)
	{
		Polygon::add(Point(c.x + cos(2*PI/n*i)*r, c.y - sin(2 * PI / n * i)*r));
	}
}

//group--------------------------------------------------------------------
struct Group : Shape{
	Group(int square_size);
	void add_piece_shape(Shape& s) { p.push_back(s); }
	Vector_ref<Shape> board() const { return b; }
	Vector_ref<Shape> pieces() const { return p; }
	void draw_lines() const;
	void move_piece(int index, int row, int column);

private:
	Vector_ref<Shape> b;
	Vector_ref<Shape> p;
	int sq_size;
};

Group::Group(int square_size) : sq_size(square_size)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			b.push_back(new Graph_lib::Rectangle{ {j * sq_size,i * sq_size},sq_size,sq_size });
			b[b.size() - 1].set_color(Color::invisible);

			if ((i + j) % 2 == 0)
				b[b.size() - 1].set_fill_color(Color::white);
			else
				b[b.size() - 1].set_fill_color(Color::black);
		}
	}
}

void Group::move_piece(int index, int row, int column)
{
	int dx{row*sq_size-p[index].point(0).x-100};
	int dy{column*sq_size-p[index].point(0).y-100};
	bool to_move{ true };
	for (int i = 0; i < p.size(); ++i)
	{
		if (index != i && p[index].point(0).x+dx == p[i].point(0).x && p[index].point(0).y + dy == p[i].point(0).y)
		{
			to_move = false;
			break;
		}
	}
	if(to_move)
		p[index].move(dx, dy);
}

void Group::draw_lines() const {
	if (color().visibility())
	{
		for (int i = 0; i < b.size(); ++i)
		{
			b[i].draw();
		}

		for (int i = 0; i < p.size(); ++i)
		{
			p[i].draw();
		}
	}
}

struct Pseudo_window : Shape {
	Pseudo_window(Point p, int ww, int hh, string label);
	int width() const { return w; }
	int height() const { return h; }
	string label() const { return lab; }
	void draw_lines() const;
private:
	int w;
	int h;
	string lab;
	int r;
	Smiley smile;
};

Pseudo_window::Pseudo_window(Point p, int ww, int hh, string label)
	:w(ww),h(hh),lab(label), smile{ {p.x+w/2,p.y + h/2},w / 8}
{
	add(p);
	r = 14;
	if (w <= 0) error("Invalid width");
	if (h <= 0) error("Invalid height");

	w = (w < lab.length()*8) ? lab.length()*8 + r * 2 : w;
	w = (w < r * 2) ? r * 2 : w;
	h = (h < r * 2) ? r * 2 : h;
	smile.set_style(Line_style(Line_style::solid, 3));
	smile.set_fill_color(Color::yellow);
}

void Pseudo_window::draw_lines() const
{
	if (color().visibility())
		//corners
	{	//topleft topright
		fl_arc(point(0).x, point(0).y, r+r,r+r, 90, 180);
		fl_arc(point(0).x+w-r*2, point(0).y, r + r,r + r,0,90);
		//bottomleft bottomright
		fl_arc(point(0).x, point(0).y+h-r*2, r + r, r + r, 180, 270);
		fl_arc(point(0).x + w - r*2, point(0).y+h-r*2, r + r, r + r, 270, 360);

		//window sides
		//left right
		fl_line(point(0).x, point(0).y + r, point(0).x, point(0).y + h - r);
		fl_line(point(0).x+w, point(0).y + r, point(0).x+w, point(0).y + h - r);
		//up down
		fl_line(point(0).x+r, point(0).y, point(0).x+w-r, point(0).y);
		fl_line(point(0).x+r, point(0).y+h, point(0).x+w-r, point(0).y + h);

		//label
		fl_line(point(0).x+1, point(0).y+20, point(0).x + w-1, point(0).y + 20);
		fl_draw(lab.c_str(), point(0).x+r, point(0).y+16);

		//smile
		smile.draw();
	}
}

struct Binary_tree : Shape {
	Binary_tree(Point root,int levels);
	void draw_lines() const;
private:
	Point r;
	int l;
	Vector_ref<Circle> circles;
	int nr{ 6 };	//node circle radius
	int step{ 50 };	//y spacing
};
/*
Binary_tree::Binary_tree(Point root, int levels)
	:l(levels), r(root)
{
	int tot_width = pow(2, l) * nr*2;
	//int nodes;
	for (int i = 0; i < l; ++i)
	{
		int nodes = pow(2, i);
		for (int j = 0; j < nodes; ++j)
		{
			//find node position
			circles.push_back(new Circle{ {r.x-tot_width/2+tot_width/2*(j+1)-tot_width/(j+1)*i,r.y + step * i + nr},nr});
		}
	}
}

void Binary_tree::draw_lines() const
{
	if (color().visibility())
		for (int i = 0; i < circles.size(); ++i)
			circles[i].draw();
}
*/

//Main---------------------------------------------------------------------------------------------------------------------------------
int main()
{
	srand(time(NULL));
	using namespace Graph_lib;

	Point tl(150, 150);
	Simple_window win(tl, 1000, 800, "My window");
	win.wait_for_button();
	/*
	Smiley my_smile{ {300,400},100 };
	win.attach(my_smile);
	Frowny my_frown{ {550,400},100 };
	win.attach(my_frown);
	Striped_rectangle strip_rect{ {100,100},{300,200} };
	strip_rect.set_stripe_color(Color::blue);
	strip_rect.set_fill_color(Color::white);
	strip_rect.set_color(Color::red);
	win.attach(strip_rect);

	Striped_circle strip_circ{ {300,500},50 };
	strip_circ.set_stripe_color(Color::blue);
	strip_circ.set_fill_color(Color::white);
	strip_circ.set_color(Color::red);
	win.attach(strip_circ);
	win.wait_for_button();

	Regular_octagon oct{ {750,300},100 };
	win.attach(oct);
	win.wait_for_button();
	oct.add();
	oct.move(20, 20);
	oct.set_color(Color::green);
	oct.set_fill_color(Color(173));
	oct.set_style(Line_style(Line_style::dash, 4));
	win.wait_for_button();

	Group checkers_board{ 100 };
	Circle chess_pawn{ {0,0},50 };
	Circle chess_pawn2{ {100,0},50 };
	chess_pawn.set_fill_color(Color::red);
	chess_pawn2.set_fill_color(Color::green);
	checkers_board.add_piece_shape(chess_pawn);
	checkers_board.add_piece_shape(chess_pawn2);
	win.attach(checkers_board);
	while (true)
	{
		for (int i = 0; i < checkers_board.pieces().size(); ++i)
		{
			checkers_board.move_piece(i, rand() % 8 + 1, rand() % 8 + 1);
		}
		win.wait_for_button();
	}
	*/
	Pseudo_window ps_win{ {100,100},170,200,"Pseudo window" };
	win.attach(ps_win);
	win.wait_for_button();
	return 0;
}