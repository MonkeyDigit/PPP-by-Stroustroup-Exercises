#include "std_lib_facilities.h"
//to indent the output table
int max_length(vector<string>& sv, string w)
{
	int length{};
	for(string& s : sv)
	{
		if(length < s.length()) length=s.length();
	}
	if(length < w.length()) length=w.length();
	return length;
}

//enum Types will be used to choose the type of number
enum Types{UND,BAD,DEC,HEX,OCT}; //UND for Undefined

//Main-------------------------------------------------------------------
int main()
{
	vector<string> base_tbl {"undefined", "unknown", "decimal", "hexadecimal", "octal"};	//printed types table
	vector<string> string_nums;	//where we will store the numbers entered from the user

	//filling the vector
	//press CTRL+Z to stop insertion
	for(string sn;cin>>sn;)
		string_nums.push_back(sn);
	
	//printing names of the table fields
	cout << left << setw(max_length(string_nums,"Number")) << "Number" << '|' 
	<< left << setw(max_length(base_tbl,"Base")) << "Base" 
	<< "|Decimal conversion\n";
	
	//determine the number type and print the table
	for(string& sn : string_nums)
	{
		Types type {UND};	//initialize type to undefined
		//look for the base - first check for hex, else it must be either oct or dec	
		if(sn[0] == '0' && sn[1] == 'x')
			type=HEX;
		else
		{
			bool is_oct {true};
			for(int i=0;i<sn.length();++i)
			{
				if(sn[0] != '0' || sn[i] >= '8')
				{
					is_oct=false;
					break;
				}
			}
			if(is_oct) type=OCT;
			else
			{
				for(int i=0;i<sn.length();++i)
				{
					if(!isdigit(sn[i]))
					{
						type=BAD;
						break;
					}
				}
				if(type!=BAD) type=DEC;
			}
		}
		//with this stringstream we can automatically convert the input into integers by simply reading from it into converted_num, just like cin but from ss
		stringstream ss{sn};
		//will work with just this
		ss.unsetf(ios::dec); // don’t assume decimal (so that 0x can mean hex)
		//ss.unsetf(ios::hex); // don’t assume hexadecimal (so that 12 can mean twelve)
		//ss.unsetf(ios::oct); // don’t assume octal (so that 12 can mean twelve)
		int converted_num;
		ss >> converted_num; 	//read from ss into converted_num
		
		//print the table elements
		cout << left << setw(max_length(string_nums,"Number")) << sn << '|' 
		<< left << setw(max_length(base_tbl,"Base")) << base_tbl[int(type)] << '|' 
		<< converted_num << '\n';
	}
	return 0;
}
