#include "Attribute.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Attribute implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Attribute::Attribute()
{
	name = "defaultName";
}

Attribute::Attribute(string name)
{
	this->name = name;
}

string Attribute::getName() const
{
	return name;
}

void Attribute::setName(string name)
{
	this->name = name;
}

int Attribute::getSize() const
{
	cout << "tried to get the size of a plain Attribute, couldn't" << endl;
	return 0;
}

ostream& operator<<(ostream & out, const Attribute &a)
{
	out << "@attribute " << a.getName() << " ";
	return out;
}