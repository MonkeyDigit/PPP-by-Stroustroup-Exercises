int main()
{	//with this infinite loop we allocate memory on the free store until memory exhaustion
	//it shouldn't do any permanent damage, but it suddenly blocks the computer and it must be shut off by force to end it
	//to be sure, don't run this program
	while (true)
	{
		void* leaky = new double[9999999];
	}
}
