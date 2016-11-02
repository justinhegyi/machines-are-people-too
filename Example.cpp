#include "Examples.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Example implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Example::Example(int n) : vector<double>(n)
{
}

Example::Example()
{
	//cout << "entered Example() default constructor" <<endl;
}

ostream& operator<<(ostream &out, const Example &e)
{
	int size = e.size();
	for (int i = 0; i < size; i++)
	{
		out << e[i] << " ";
	}
	out << endl;
	return out;
}