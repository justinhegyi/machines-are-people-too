#include "Attributes.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Attributes implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Attributes::Attributes()
{
	hasNominalAttributes = false;
	hasNumericAttributes = false;
	classIndex = -1;
}



void Attributes::add(Attribute *attribute)
{
	//if type or memory problems, throw logic_error. How to check that??
	//why are types incompatible?
	if (this->hasNominalAttributes == false && typeid(*attribute) == typeid(NominalAttribute))
		this->hasNominalAttributes = true;
	if (this->hasNumericAttributes == false && typeid(*attribute) == typeid(NominalAttribute))
		this->hasNumericAttributes = true;

	attributes.push_back(attribute);
	classIndex = getSize() - 1;
}


Attribute* Attributes::get(int i) const
{
	int size = attributes.size() - 1;
	if (i > size || i < 0)
		throw logic_error("index out of range inside Attributes::get()");
	return attributes[i];
}


Attribute* Attributes::getClassAttribute() const
{
	return attributes[classIndex];
}


int Attributes::getSize() const
{
	return attributes.size();
}


bool Attributes::getHasNominalAttributes()	const
{
	return hasNominalAttributes;
}


bool Attributes::getHasNumericAttributes()	const
{
	return hasNumericAttributes;
}

int Attributes::getIndex(string name) const
{
	int size = attributes.size();
	for (int i = 0; i < size; i++)
	{
		if ((*attributes[i]).getName() == name)
			return i;
	}
	return 0;

}

void Attributes::parse(istream  &in)
{
	string word;
	while (in.peek() != '\n')
	{
		AttributeFactory AtFac;
		Attribute *atr = new Attribute;
		atr = AtFac.make(in);
		add(atr);
	}
}

void Attributes::setClassIndex(int 	classIndex)
{
	this->classIndex = classIndex;
}

int Attributes::getClassIndex() const
{
	return classIndex;
}

ostream &operator<<(ostream &out, const Attributes &a)
{
	for (Attribute *atr : a.attributes)
	{	//convert from pointer back to attribute, then let it print itself
		if (typeid(*atr) == typeid(NominalAttribute))
		{
			dynamic_cast<NominalAttribute*>(atr)->print(out);
		}
		else
			out << *(dynamic_cast<NumericAttribute*>(atr)) << endl;
	}
	return out;
}
