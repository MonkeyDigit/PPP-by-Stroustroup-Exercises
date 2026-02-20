#include "bar_graph.h"

Bar_graph::Bar_graph(Point origin, double xscale, double yscale)
	: orig(origin), xscale(xscale), yscale(yscale) {}

Bar_graph::Bar_graph(Point origin, vector<double> data, double xscale, double yscale)
	: orig(origin), values(data), xscale(xscale), yscale(yscale)
{
	for (int i = 0; i < values.size(); ++i)
		add_rect(i, values[i]);
}

vector<double> Bar_graph::get_values() const { return values; }
void Bar_graph::set_bar_color(int i, Color col) { rects[i].set_fill_color(col); }
void Bar_graph::set_graph_label(string label) { glab.set_label(label); }


void Bar_graph::add_value(double v)
{
	values.push_back(v);			//store the value and generate its corresponding rectangle
	add_rect(values.size() - 1, v);
}

void Bar_graph::add_rect(double x, double v)
{
	Point tl;
	int ww;
	int hh;
	double scaled_x = x * xscale;
	double scaled_y = v * yscale;
	if (v > 0)
	{
		//we add the scaled x value to orig. so orig.x  +  x*xscale; same thing for y
		tl = Point(orig.x + scaled_x, orig.y - scaled_y);
		//we add 1 pixel so that the rectangle fits perfectly
		ww = xscale + 1;
		hh = scaled_y + 1;
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
	blabs.push_back(new Text{ Point(orig.x + i * xscale,orig.y+20),label });
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