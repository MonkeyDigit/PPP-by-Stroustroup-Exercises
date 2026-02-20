#include "Simple_window.h"
#include "Graph.h"

int main()
{
	using namespace Graph_lib;
	Point tl{ 150,150 };
	Simple_window win{tl,800,1000,"My window"};
	Lines grid;
	int cell_size = 100;

	for (int x = cell_size; x < win.x_max(); x += cell_size)
	{
		grid.add({ x,0 }, { x,win.x_max() });	//it needs to be an 8 by 8 grid, so we put win.x_max() because it is 800
	}

	for (int y = cell_size; y < win.x_max(); y += cell_size)
	{
		grid.add({ 0,y }, { win.x_max(),y});
	}
	win.attach(grid);
	win.wait_for_button();

	Vector_ref<Graph_lib::Rectangle> rect;
	for (int i = 0; i < 8; ++i)
	{
		rect.push_back(new Graph_lib::Rectangle{ { i * cell_size,i * cell_size }, cell_size, cell_size });
		rect[i].set_fill_color(Color::red);
		win.attach(rect[i]);
	}

	/*This would make a colored grid
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			//we can omit Point when setting the rectangle coordinates
			rect.push_back(new Graph_lib::Rectangle{ {i*cell_size,j*cell_size},cell_size,cell_size });	
			rect[rect.size() - 1].set_fill_color(Color{ i * 16 + j });
			win.attach(rect[rect.size() - 1]);
		}
	}
	*/
	win.wait_for_button();

	Image i1{ Point{cell_size*2,0},"200by200.jpg" };	//wrote point to be explicit: in this case it means the position of the topleft pixel
	Image i2{ {cell_size*4,0},"200by200.jpg" };			//of the image
	Image i3{ {cell_size*6,0},"200by200.jpg" };
	i1.set_mask( Point{0,0},200,200 );	//In this case, the point is the topleft pixel of the image, which determines the portion cut and shown		
	i2.set_mask({ 0,0},200,200 );
	i3.set_mask({ 0,0},200,200 );
	win.attach(i1);
	win.attach(i2);
	//win.attach(i3);
	win.wait_for_button();

	int im_x{};
	int im_y{};
	Image moving_image{ {im_x,im_y},"chess pawn.jpg" };
	win.attach(moving_image);
	win.wait_for_button();

	while (true)
	{
		int rand_x{};
		int rand_y{};
		rand_x = (rand() % 8)*cell_size;
		rand_y = (rand() % 8) * cell_size;
		moving_image.move(rand_x-im_x, rand_y-im_y);
		im_x = rand_x;
		im_y = rand_y;
		win.wait_for_button();
	}
	/*
	enum eDirection{LEFT,RIGHT,UP,DOWN};
	while (true)
	{
		int rand_dir{};
		int move_x{};
		int move_y{};
		do 
		{
			rand_dir = rand() % 4;
			switch(rand_dir)
			{
			case LEFT:
				move_x = -100;
				break;
			case RIGHT:
				move_x = 100;
				break;
			case UP:
				move_y = -100;
				break;
			case DOWN:
				move_y = 100;
				break;
			}
		} while (im_x + move_x < 0 || im_x + move_x>700 || im_y + move_y < 0 || im_y + move_y>700);
		im_x += move_x;
		im_y += move_y;
		moving_image.move(move_x, move_y);
		win.wait_for_button();
	}
	*/
	return 0;
}