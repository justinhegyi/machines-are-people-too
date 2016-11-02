#include "NominalAttribute.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											NominalAttribute implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NominalAttribute::NominalAttribute()
{
	//cout << "Entered default constructor" << endl;
}


NominalAttribute::NominalAttribute(string name)
{
	addValue(name);
}


int NominalAttribute::getSize() const
{
	return domain.size();
}

string NominalAttribute::getValue(int index)
{
	try {
		int size = getSize();
		if (index > size - 1)
			throw logic_error("index is out of bounds");
	}
	catch( std::out_of_range &oor)
	{
		throw logic_error(oor.what());
	}
	return domain[index];
}

int NominalAttribute::getIndex(string value)
{
	int size = domain.size();
	for (int i = 0; i < size; i++)
	{
		if (value == domain[i])
			return i;
	}
	throw logic_error("value could not be found in the domain");
}

void NominalAttribute::addValue(string 	value)
{
	domain.push_back(value);
}

void NominalAttribute::print(ostream & out) const
{
	out << "@attribute " << getName() << " ";
	for (int i = 0; i < getSize(); i++)
	{
		out << domain[i] << " ";
	}
	out << endl;
}