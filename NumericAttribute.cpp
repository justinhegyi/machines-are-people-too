#include "NumericAttribute.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											NumericAttribute implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NumericAttribute::NumericAttribute()
{
	setName("Blank NumericAttribute");
}

NumericAttribute::NumericAttribute(string name)
{
	setName(name);
}

ostream& operator<<	(ostream & 	out, const NumericAttribute & na)
{
	out << "@attribute " << na.getName() << " numeric ";
	return out;
}