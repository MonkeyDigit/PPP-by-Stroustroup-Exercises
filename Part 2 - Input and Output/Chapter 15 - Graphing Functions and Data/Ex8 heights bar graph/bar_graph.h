#pragma once
#include "Graph.h"
using namespace Graph_lib;
struct Bar_graph : Shape {
	//constructors
	Bar_graph(Point origin, double xscale, double yscale);
	Bar_graph(Point origin, vector<double> data, double xscale, double yscale);	//with data vector included

	void add_value(double v);
	void set_bar_color(int i, Color col);
	void set_graph_label(string label);
	void set_bar_label(int i, string label);
	vector<double> get_values() const;
	void draw_lines() const;
private:
	vector<double> values;
	Vector_ref<Graph_lib::Rectangle> rects;
	Point orig;
	double xscale;
	double yscale;
	Text glab{ Point(orig.x,orig.y + 20),"" };
	Vector_ref<Text> blabs;	//bar labels
	void add_rect(double x, double v);	//the x coordinate and the height of the rectngle (the value)
};