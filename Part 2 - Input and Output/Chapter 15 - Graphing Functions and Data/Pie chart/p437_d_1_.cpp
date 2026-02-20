#include "Simple_window.h"
#include "Graph.h"
# define PI 3.141592653589
int main()
{
	using namespace Graph_lib;

	Point tl(150, 150);
	Simple_window win(tl, 1000, 800, "My window");
	win.wait_for_button();

	Circle pie_chart{ {win.x_max() / 2,win.y_max() / 2},150 };
	Lines portion;
	double percent{ 10 };
	portion.add(pie_chart.center(), Point(pie_chart.center().x + pie_chart.radius(), pie_chart.center().y));
	portion.add(pie_chart.center(), Point(pie_chart.center().x + cos(2 * PI * percent / 100)*pie_chart.radius(), pie_chart.center().y - sin(2 * PI * percent / 100) * pie_chart.radius()));

	win.attach(pie_chart);
	win.attach(portion);
	win.wait_for_button();
}