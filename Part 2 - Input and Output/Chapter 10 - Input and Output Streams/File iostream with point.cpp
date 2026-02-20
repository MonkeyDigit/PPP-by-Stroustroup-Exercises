#include "std_lib_facilities.h"
struct Point{
	int x;
	int y;
};

istream& operator>>(istream& is, Point& pp)
{
	int x,y;
	char ch;
	is >> x >> ch >> y;
	if(!is) return is;
	if(ch!=',')
	{
		is.clear(ios_base::failbit); // clear the state of input and set the fail bit
			return is;
	}
	pp.x=x;
	pp.y=y;
	return is;
}

bool operator==(Point& a, Point& b)
{
	return a.x == b.x
		&& a.y == b.y;
}

bool operator!=(Point& a, Point& b)
{
	return !(a == b);
}

int main()
{
	//Enter the name of the file from which to take the Point values
	/*
	cout << "Please enter input file name: ";
	string iname;
	cin >> iname;
	ifstream ist {iname}; // ist is an input stream for the file named name - NOTE: we must include the file extensione (PointsIn ->PointsIn.txt)
	if (!ist) error("can't open input file ",iname);
	*/
	//Entering the coordinates---------------------------------------------------------------------
	vector<Point> original_points;
	cout<<"Please enter 7 coordinates -> x,y"<<'\n';	//after opening the input file by initializing the ifstream ist, it can now read from the file
	for (int i=0;i<7;++i)
	{
		Point p;
		cin>>p;
		if(!cin) error("Incorrect input!");
		//ist>>p;	//this works like cin but it reads from the file instead of user input, so it's done automatically
		original_points.push_back(p);
	}
	
	//-----------------------------------------------------------------------------------------
 	/*
	//Just a loop that outputs the file values to ensure they are correct
	for (Point p : original_points)
 		cout << p.x << ',' << p.y << '\n';
 	
	cout << "Please enter name of output file: ";
	string oname;
	cin >> oname;
	ofstream ost {oname}; // ost is an output stream for a file named oname
	if (!ost) error("can't open output file ",oname);
	for (Point p : original_points)
 		ost << '(' << p.x << ',' << p.y << ")\n";	//we are now writing in the output file - Note: nothing appears in the console, but the output file is written
 	*/
 	
 	string oname {"mydata.txt"};
 	ofstream ost {oname};
 	if (!ost) error("can't open output file ",oname);
 	
	for (Point p : original_points)
 		ost << p.x << ',' << p.y << '\n';
 		
 	//Inform of the successful operation
 	cout<<"Writing to " << oname << " completed!"<<'\n';	
 	ost.close();
 	
 	/* These 2 lines can be used to pause the program and test what happens if values inside of mydata.txt are modified
 	int b;
 	cin>>b;
 	*/
 	
 	//Reading values from mydata.txt
 	string iname {"mydata.txt"};
 	ifstream ist {iname};
 	if (!ist) error("can't open output file ",oname);
 	
 	vector<Point> processed_points;
 	for(Point p : original_points)
 	{
 		ist>>p;
 		if(!ist) error("Couldn't read properly from ",iname);
 		processed_points.push_back(p);
	}
	
	//Output loops---------------------------------------------------------------
	cout<<"original_points: \n";
	for(int i=0; i<original_points.size();++i)
 	{
 		cout << original_points[i].x << ',' << original_points[i].y << '\n';
	}
	
	cout<<"processed_points: \n";
	for(int i=0; i<processed_points.size();++i)
 	{
 		cout << processed_points[i].x << ',' << processed_points[i].y << '\n';
	}
	
	//Vector comparison----------------------------------------------------------------
	if(original_points.size() != processed_points.size()) cout<< "Something's wrong!\n";
	for(int i=0; i<original_points.size();++i)
	{
		if(original_points[i] != processed_points[i])
		{
			cout << "Something's wrong!\n";
			break;
		}
	}
	
	
	return 0;
}
