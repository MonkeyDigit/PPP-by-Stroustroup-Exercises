#include "Simple_window.h"
#include "Graph.h"
#include "bar_graph.h"
using namespace Graph_lib;

class Height_group {
public:
	Height_group() {}
	Height_group(int height, int quantity);
	int height() const { return h; }
	int quantity() const { return q; }
private:
	int h;//height
	int q;//quantity
};
Height_group::Height_group(int height, int quantity)
	 :h(height), q(quantity)
{
	if (h <= 0) error("Non-positive height");
	if (q < 0) error("Negative quantity");
}

istream& operator>>(istream& is, Height_group& hg)
{
	char ch1, ch2, ch3;
	int h, q;
	is >> ch1 >> h >> ch2 >> q >> ch3;
	if (!is) return is;

	if (ch1 != '(' || ch2 != ',' || ch3 != ')')
	{
		is.clear(ios_base::failbit);
		return is;
	}

	hg = Height_group(h, q);
	return is;
}

int main()
{
	std::cout << "Please enter input file name: ";
	string iname;
	std::cin >> iname;
	ifstream ifs{ iname };

	if (!ifs) error("Couldn't open input file ", iname);
	vector<int> heights;
	vector<double> groups;

	for (Height_group hg; ifs >> hg;)
	{
		heights.push_back(hg.height());
		groups.push_back(hg.quantity());
	}

	Point tl(150, 150);
	constexpr int xmax{ 800 };
	constexpr int ymax{ 800 };
	Simple_window win(tl, xmax, ymax, "My window");
	win.wait_for_button();

	constexpr int x_offset{ 30 };
	constexpr int y_offset{ 30 };
	const Point orig{ x_offset,ymax-y_offset };
	constexpr int x_length{ xmax - x_offset * 2 };
	constexpr int y_length{ ymax - y_offset * 2 };
	const int x_notches = heights.size();
	const int y_notches{ 45 };
	const double x_scale{ (double)x_length / x_notches };
	const double y_scale{ (double)y_length / y_notches };
	Axis xa{ Axis::x,orig,x_length,x_notches};
	Axis ya{ Axis::y,orig,y_length,y_notches};

	Bar_graph heights_graph{orig,groups,x_scale,y_scale };
	
	for (int i = 0; i < heights.size(); ++i)
	{
		ostringstream os;
		os<< heights[i];
		heights_graph.set_bar_label(i, os.str());
	}

	win.attach(heights_graph);
	win.attach(xa);
	win.attach(ya);
	win.wait_for_button();
}