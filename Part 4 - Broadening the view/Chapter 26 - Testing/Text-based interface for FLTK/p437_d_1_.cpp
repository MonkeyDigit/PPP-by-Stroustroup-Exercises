#include "Simple_window.h"
#include "Graph.h"
#include <regex>

int main()
{
	using namespace Graph_lib;

	Point tl(150, 150);
	Simple_window win(tl, 600, 400, "My window");

	const string circle_str = "Circle";
	const string rect_str = "Rectangle";
	const string line_str = "Line";
	regex cmd_pat{R"(([a-zA-Z]+)(\(Point\(\d+,\d+\),[\w ]+\)))"};

	regex circle_pat{ R"((\(Point\()(\d+),(\d+)\),(\d+)\))" };

	vector<Shape*> shapes;

	string cmd;
	while (true)
	{
		cin >> cmd;
		//circle
		smatch matches;

		if (cmd.length() > 0 && regex_match(cmd, matches, cmd_pat))
		{	//test cout
			//cout << matches[0] << ' ' << matches[1] << ' ' << matches[2] << '\n';

			string arg_str = matches[2].str();

			//matches[1] is the shape
			if (matches[1].str() == circle_str)
			{
				cout << "is circle " << arg_str << '\n';
				if (regex_match(arg_str, matches, circle_pat))
				{
					/*
					cout << matches[0] << ' '
						<< matches[1] << ' '
						<< matches[2] << ' '
						<< matches[3] << ' '
						<< matches[4] << '\n';
					*/

					Point circle_point{ stoi(matches[2].str()),stoi(matches[3].str()) };
					int circle_radius{ stoi(matches[4].str()) };

					shapes.push_back(new Circle{ circle_point,circle_radius });
				}
			}
			else
				cout << "Bad circle input\n";
		}
		else
			cout << "Bad input\n";

		for (int i = 0; i < shapes.size(); ++i)
		{
			shapes[i]->set_color(Color::black);
			win.attach(*shapes[i]);
			shapes[i]->draw();
		}
		win.wait_for_button();
	}
}