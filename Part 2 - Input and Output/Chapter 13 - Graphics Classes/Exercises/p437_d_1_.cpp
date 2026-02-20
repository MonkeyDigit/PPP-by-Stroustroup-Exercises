#include "Simple_window.h"
#include "Graph.h"
#include <iostream>
# define PI 3.14159265359
using namespace Graph_lib;

class Arch : public Shape {
public:
	Arch(Point center, int width, int height, double start, double end) : c(center),w(width), h(height), s(start), e(end)
	{
		add(center);	//topleft angle of square bounding the arch
	}
	Point center() const { return c; };
	void draw_lines() const;
private:
	Point c;
	int w;
	int h;
	double s;	//start angle (0 from the right)
	double e;	//end angle (360)
};

void Arch::draw_lines() const
{
	if (color().visibility())
		fl_arc(point(0).x, point(0).y, w, h, s, e);
}

//Box
class Box : public Shape {
public:
	Box(Point pp,string label) : p(pp),h(24), sm(8), l(label)
	{
		add(pp);
		int box_width{};
		for (char& ch : l)
		{
			if (isupper(ch) || isspace(ch)) box_width += 9;
			else box_width += 8;
		}
		w = box_width+10;

	}
	Box(Point pp, int width,int height, int smoothness) : p(pp), w(width), h(height), sm(smoothness)
	{
		add(pp);	//topleft angle
		if (sm > min(width,height)) sm = min(width,height);		//the most rounding a square can get, will make it look like a circle
	}
	void draw_lines() const;
private:
	Point p;	//topleft angle
	string l{""}; //label
	int w;		//width
	int h;		//height
	int sm;		//smoothness of corners [0:sz]
};

void Box::draw_lines() const
{
	if (color().visibility())
	{
		//smooth corners //fl_arc(x,y,w,h,s,e)   x,y:centre ; w:width; h:height; s:start; e:end
		fl_arc(p.x,p.y, sm, sm , 90, 180);	//topleft
		fl_arc(p.x+w-sm, p.y, sm , sm , 0, 90);	//topright
		fl_arc(p.x,p.y+h-sm, sm , sm , 180, 270);	//bottomleft
		fl_arc(p.x+w-sm,p.y+h-sm, sm , sm , 270, 360); //bottomright

		//sides from p1 to p2
		fl_line(p.x, p.y +sm/2,  p.x, p.y + h-sm/2);				//left side
		fl_line(p.x+w,  p.y + sm / 2, p.x+w, p.y + h- sm / 2);	//right side
		fl_line(p.x + sm / 2, p.y,  p.x+w - sm / 2, p.y);			//top side
		fl_line(p.x + sm / 2, p.y+h,  p.x+w - sm / 2, p.y + h);	//bottom side
		if (l.length() > 0)
		{
			fl_draw(l.c_str(), p.x+5, p.y+h-7);
		}
	}
}

Point rotate_point(Point pivot, double angle, Point p) //rotate point p around the pivot, by angle degrees
{
	//NOTE: cos and sin expect the angle to be expressed in radians
	double angleRad = angle * PI / 180.0;
	return Point(cos(angleRad) * (p.x - pivot.x) - sin(angleRad) * (p.y - pivot.y) + pivot.x,	//x	
		sin(angleRad) * (p.x - pivot.x) + cos(angleRad) * (p.y - pivot.y) + pivot.y);			//y
}

//Arrow
class Arrow : public Shape {
public:
	Arrow(Point p1, Point p2, int arrow_size);
private:
	int sz;		//size of arrow head
};

Arrow::Arrow(Point p1, Point p2, int arrow_size) : sz(arrow_size)
{	//by adding the points to the shape we don't need to define draw_lines
	add(p1);	//start point
	add(p2);	//end point
	//magnitude - the great size or extent of something
	// vector - magnitude + direction
	//
	//get difference of  x and y:  end.x - start.x   and    end.y - start.y		catets of right triangle
	//calculate lenght of arrow - hypotenuse  magnitude
	//make a unit vector (vector where magnitude=1 but direction is the same)
	//multiply magnitude by the size of the arrow before doing the division to get the unit vector
	//to know where the arrow heads need to go, we need to rotate a point, which corresponds to end of the arrow head
	//that is,starting from the end of the line, to the end of the line. to know that point we need to subtract the components
	//(x,y) of unit vector, from components of the end of the line
	//then we can rotate it by an angle
	double side_x = abs(p2.x - p1.x);
	double side_y = abs(p2.y - p1.y);
	double lmag = sqrt(side_x * side_x + side_y * side_y);
	Point unit_vect(double(side_x * arrow_size / lmag), double(side_y * arrow_size / lmag));

	Point arrow1;	//left arrow segment
	Point arrow2;	//right arrow segment
	//handle all possible slopes
	if (p2.y - p1.y < 0 && p2.x - p1.x >= 0)
	{
		arrow1 = rotate_point(p2, 30, Point(p2.x - unit_vect.x, p2.y + unit_vect.y));
		arrow2 = rotate_point(p2, -30, Point(p2.x - unit_vect.x, p2.y + unit_vect.y));
	}
	else if (p2.y - p1.y < 0 && p2.x - p1.x < 0)
	{
		arrow1 = rotate_point(p2, 30, Point(p2.x + unit_vect.x, p2.y + unit_vect.y));
		arrow2 = rotate_point(p2, -30, Point(p2.x + unit_vect.x, p2.y + unit_vect.y));
	}
	else if (p2.y - p1.y >= 0 && p2.x - p1.x < 0)
	{
		arrow1 = rotate_point(p2, 30, Point(p2.x + unit_vect.x, p2.y - unit_vect.y));
		arrow2 = rotate_point(p2, -30, Point(p2.x + unit_vect.x, p2.y - unit_vect.y));
	}
	else if (p2.y - p1.y >= 0 && p2.x - p1.x >= 0)
	{
		arrow1 = rotate_point(p2, 30, Point(p2.x - unit_vect.x, p2.y - unit_vect.y));
		arrow2 = rotate_point(p2, -30, Point(p2.x - unit_vect.x, p2.y - unit_vect.y));
	}
	add(p2);	//add a point with the coordinates of p2, and connect arrow1's point to it
	add(arrow1);
	add(p2);
	add(arrow2);
}

//cardinal points n,s,e,w - center,ne,se,nw,sw
Point n(Graph_lib::Rectangle& rect)
{
	return Point(rect.point(0).x + rect.width() / 2, rect.point(0).y);
}
Point s(Graph_lib::Rectangle& rect)
{
	return Point(rect.point(0).x + rect.width() / 2, rect.point(0).y+rect.height());
}
Point e(Graph_lib::Rectangle& rect)
{
	return Point(rect.point(0).x + rect.width(), rect.point(0).y + rect.height()/2);
}
Point w(Graph_lib::Rectangle& rect)
{
	return Point(rect.point(0).x, rect.point(0).y + rect.height()/2);
}
Point center(Graph_lib::Rectangle& rect)
{
	return Point(rect.point(0).x + rect.width() / 2, rect.point(0).y + rect.height()/2);
}
Point ne(Graph_lib::Rectangle& rect)
{
	return Point(rect.point(0).x + rect.width(), rect.point(0).y);
}
Point se(Graph_lib::Rectangle& rect)
{
	return Point(rect.point(0).x + rect.width(), rect.point(0).y + rect.height());
}
Point sw(Graph_lib::Rectangle& rect)
{
	return Point(rect.point(0).x, rect.point(0).y + rect.height());
}
Point nw(Graph_lib::Rectangle& rect)
{
	return Point(rect.point(0).x, rect.point(0).y);
}

Point n(Circle& circ)
{
	return Point(circ.point(0).x + circ.radius(), circ.point(0).y);
}
Point s(Circle& circ)
{
	return Point(circ.point(0).x + circ.radius(), circ.point(0).y + circ.radius()*2);
}
Point e(Circle& circ)
{
	return Point(circ.point(0).x + circ.radius()*2, circ.point(0).y + circ.radius());
}
Point w(Circle& circ)
{
	return Point(circ.point(0).x, circ.point(0).y + circ.radius());
}
Point center(Circle& circ)
{
	return circ.center();
}
Point ne(Circle& circ)
{
	double angleRad = 45 * PI / 180.0;
	double dist = cos(angleRad) * circ.radius();
	int x{ static_cast<int>(circ.center().x + dist) };
	int y{ static_cast<int>(circ.center().y-dist)};
	return Point(x,y);
}
Point se(Circle& circ)
{
	double angleRad = 45 * PI / 180.0;
	double dist = cos(angleRad) * circ.radius();
	int x{ static_cast<int>(circ.center().x + dist) };
	int y{ static_cast<int>(circ.center().y + dist) };
	return Point(x, y);
}
Point sw(Circle& circ)
{
	double angleRad = 45 * PI / 180.0;
	double dist = cos(angleRad) * circ.radius();
	int x{ static_cast<int>(circ.center().x - dist) };
	int y{ static_cast<int>(circ.center().y + dist) };
	return Point(x, y);
}
Point nw(Circle& circ)
{
	double angleRad = 45 * PI / 180.0;
	double dist = cos(angleRad) * circ.radius();
	int x{ static_cast<int>(circ.center().x - dist) };
	int y{ static_cast<int>(circ.center().y - dist) };
	return Point(x, y);
}

class Regular_hexagon : public Closed_polyline {
public:
	Regular_hexagon(Point center,int radius);
	Point center() const { return c;};
	int radius() const {return r;};
private:
	Point c;
	int r;
};

Regular_hexagon::Regular_hexagon(Point center, int radius) : c(center), r(radius)
{
	if (r <= 0) error("Negative radius");
	for (int i = 0; i < 360; i += 60)
	{
		double rad = i * PI / 180.0;
		double x = c.x + cos(rad) * r;
		double y = c.y - sin(rad) * r;
		add(Point(x,y));
	}

}

class Regular_polygon : public Closed_polyline {
public:
	Regular_polygon(Point center, int sides, int radius);
	Point center() const { return c; };
	int radius() const { return r; };
private:
	Point c;
	int s;
	int r;

};

Regular_polygon::Regular_polygon(Point center, int segments, int radius)
	: c(center), s(segments), r(radius)
{
	s=(segments < 3)? 3 : segments;
	if (r <= 0) error("Negative radius");

	double angle = 360 / s;
	for (int i = 0; i < 360; i += angle)
	{
		double rad = i * PI / 180.0;
		add(Point(c.x + cos(rad) * r, c.y - sin(rad) * r));
	}

}

class Star : public Closed_polyline{
public:
	Star(Point center, int outer_radius, int inner_radius, int points);
	Point center() const { return c; };
	int outer_radius() const { return out_r; };
	int inner_radius() const { return in_r; };
private:
	Point c;
	int out_r ;
	int in_r;
};
Star::Star(Point center, int outer_radius, int inner_radius, int points)
	:c(center), out_r(outer_radius), in_r(inner_radius)
{
	if (in_r <= 0 || out_r<=0) error("Negative radius");
	points = (points < 2) ? 2 : points;
	int angle = 360 / points;
	for (int i =0; i < 360; i += angle)
	{
		double rad = i * PI / 180.0;
		add(Point(c.x + cos(rad) * out_r, c.y - sin(rad) * out_r));
		rad= (i+(double)angle/2) * PI / 180.0;
		add(Point(c.x + cos(rad) * in_r, c.y - sin(rad) * in_r));
	}
}

//Main------------------------------------------------------------------------------------------------------------------
int main()
{

	Point tl(150, 150);
	Simple_window win(tl, 1000, 600, "My window");
	win.wait_for_button();

	/*
	Arch my_arch{ {200,300},300,200,0,180 };
	my_arch.set_color(Color::dark_green);
	my_arch.set_style(Line_style(Line_style::solid,4));
	win.attach(my_arch);

	Vector_ref<Arch> arches;
	int thickness{4};
	for (int i = 0; i < 6; ++i)
	{
		arches.push_back(new Arch{ {600,300 + i * thickness},500,333,0,180 });
		arches[i].set_color(Color(i + 1));
		arches[i].set_style(Line_style(Line_style::solid,4));
		win.attach(arches[i]);
	}
	win.wait_for_button();
	Box my_box{{400,200},200,100,50};
	my_box.set_style(Line_style(Line_style::solid, 3));
	//my_box.set_fill_color(Color::blue);				 not implemented
	win.attach(my_box);
	win.wait_for_button();

	//circle of arrows
	Vector_ref<Arrow> arrows;
	int length = 200;
	Point origin{ 500,250 };
	int color{166};
	for (int i = 0; i < 360; i += 8)
	{
		double angleRads = i * PI / 180.0;
		double x{origin.x + cos(angleRads) * length };
		double y{origin.y - sin(angleRads) * length };
		arrows.push_back(new Arrow( origin, Point(x,y), 15 ));
		arrows[arrows.size() - 1].set_color(Color(color));
		arrows[arrows.size() - 1].set_style(Line_style(Line_style::solid,3));
		win.attach(arrows[arrows.size() - 1]);
		++color;
	}
	win.wait_for_button();
	Graph_lib::Rectangle rect{ {300,150},{450,250} };
	win.attach(rect);

	Vector_ref<Circle> red_circles;
	red_circles.push_back(new Circle(Point(n(rect).x,n(rect).y),8));

	red_circles.push_back(new Circle(Point(s(rect).x, s(rect).y), 8));

	red_circles.push_back(new Circle(Point(e(rect).x, e(rect).y), 8));

	red_circles.push_back(new Circle(Point(w(rect).x, w(rect).y), 8));

	red_circles.push_back(new Circle(Point(center(rect).x, center(rect).y), 8));

	red_circles.push_back(new Circle(Point(ne(rect).x, ne(rect).y), 8));

	red_circles.push_back(new Circle(Point(se(rect).x, se(rect).y), 8));

	red_circles.push_back(new Circle(Point(nw(rect).x, nw(rect).y), 8));

	red_circles.push_back(new Circle(Point(sw(rect).x, sw(rect).y), 8));

	for (int i = 0; i < red_circles.size(); ++i)
	{
		red_circles[i].set_color(Color::invisible);
		red_circles[i].set_fill_color(Color::red);
		win.attach(red_circles[i]);
	}
	win.wait_for_button();
	Circle circ{ {800,150},75 };
	win.attach(circ);
	Vector_ref<Circle> red_circles2;
	red_circles2.push_back(new Circle(Point(n(circ).x, n(circ).y), 8));
	red_circles2.push_back(new Circle(Point(s(circ).x, s(circ).y), 8));

	red_circles2.push_back(new Circle(Point(e(circ).x, e(circ).y), 8));

	red_circles2.push_back(new Circle(Point(w(circ).x, w(circ).y), 8));

	red_circles2.push_back(new Circle(Point(center(circ).x, center(circ).y), 8));

	red_circles2.push_back(new Circle(Point(ne(circ).x, ne(circ).y), 8));

	red_circles2.push_back(new Circle(Point(se(circ).x, se(circ).y), 8));

	red_circles2.push_back(new Circle(Point(nw(circ).x, nw(circ).y), 8));

	red_circles2.push_back(new Circle(Point(sw(circ).x, sw(circ).y), 8));

	for (int i = 0; i < red_circles2.size(); ++i)
	{
		red_circles2[i].set_color(Color::invisible);
		red_circles2[i].set_fill_color(Color::red);
		win.attach(red_circles2[i]);
	}
	win.wait_for_button();

	Box tbox{ {200,200},"Window" };
	win.attach(tbox);
	win.wait_for_button();

	Vector_ref<Graph_lib::Rectangle> rgb;
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			rgb.push_back(new Graph_lib::Rectangle(Point(i * 35, j * 35), 35, 35));
			rgb[rgb.size() - 1].set_color(Color::invisible);
			rgb[rgb.size() - 1].set_fill_color(Color(i*16+j));
			win.attach(rgb[rgb.size() - 1]);
		}
	}
	win.wait_for_button();
	Regular_hexagon hexag{ {600,500},50 };
	win.attach(hexag);
	win.wait_for_button();
	Vector_ref<Regular_hexagon> tiles;
	int hex_rad{20};
	int hex_h = sqrt(pow(hex_rad, 2) -pow(hex_rad/2,2));
	for (int i = 0; i < 10; ++i)
	{
		Point np{ 20,20 + i * hex_h* 2};
		for (int j = 0; j <28; ++j)
		{
			tiles.push_back(new Regular_hexagon{np,hex_rad});
			tiles[tiles.size() - 1].set_color(Color::invisible);
			tiles[tiles.size() - 1].set_fill_color(Color(i*28+j));
			win.attach(tiles[tiles.size() - 1]);
			//win.wait_for_button();
			if (j% 2 == 0)
			{
				np.x = tiles[tiles.size() - 1].point(5).x + hex_rad;
				np.y = tiles[tiles.size() - 1].point(5).y;
			}
			else
			{
				np.x = tiles[tiles.size() - 1].point(1).x + hex_rad;
				np.y = tiles[tiles.size() - 1].point(1).y;
			}
			np.x+=1;
		}
	}
	win.wait_for_button();
	Regular_polygon reg_pol{ {500,450},8,100 };
	win.attach(reg_pol);
	win.wait_for_button();
	Graph_lib::Ellipse ell{ {400,300},150,100 };
	Axis xa{ Axis::x,Point(ell.center().x - 200,ell.center().y),400,20};
	Axis ya{ Axis::y,Point(ell.center().x,ell.center().y+200),400,20};
	Mark foci1{ell.focus1(),'1'};
	Mark foci2{ell.focus2(),'2'};
	int ang{ 220 };
	double rad = ang * PI / 180.0;
	Mark ell_mark{ Point(ell.center().x + cos(rad) * ell.major(),ell.center().y -sin(rad) * ell.minor()),'x'};
	Lines foci_h;
	foci_h.add(ell.focus1(),ell_mark.point(0));
	foci_h.add( ell.focus2(),ell_mark.point(0) );
	foci_h.set_color(Color::red);
	win.attach(ell);
	win.attach(xa);
	win.attach(ya);
	win.attach(foci1);
	win.attach(foci2);
	win.attach(ell_mark);
	win.attach(foci_h);
	win.wait_for_button();

	Circle clock_circle{ {400,300},200 };
	int clock_ang{};
	Mark cmark{ {clock_circle.center().x + clock_circle.radius(),clock_circle.center().y},'x'};
	win.attach(clock_circle);
	while(true)
	{
		win.attach(cmark);
		win.wait_for_button();
		clock_ang += 20;
		double angrad = clock_ang * PI / 180.0;
		double nx = clock_circle.center().x + cos(angrad) * clock_circle.radius();
		double ny = clock_circle.center().y - sin(angrad) * clock_circle.radius();
		cmark.move(-(cmark.point(0).x - nx), -(cmark.point(0).y - ny));
	}
	win.wait_for_button();
	*/
	Star my_star{ {400,400},200,60,12};
	my_star.set_fill_color(Color(170));
	win.attach(my_star);
	win.wait_for_button();
	return 0;
}