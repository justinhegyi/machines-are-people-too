#include "Attribute.h"
#include "NominalAttribute.h"
#include "NumericAttribute.h"
#include "AttributeFactory.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//										AttributeFactory implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Attribute* AttributeFactory::make(istream &in)
{
	//next word is the name
	string name;
	string word;
	in >> name;
	in >> word;

	//creates a NumericAttribute if the next word is numeric 
	if (word == "numeric")
	{	//move to the next word
		in >> word;
		NumericAttribute *Atr2Return = new NumericAttribute(name);
		return dynamic_cast<Attribute *>(Atr2Return);
	}

	//creates a NominalAttribute if the next word isn't numeric
	else
	{
		NominalAttribute *Atr2Return = new NominalAttribute();
		(*Atr2Return).setName(name);
		(*Atr2Return).addValue(word);

		//as long as the line continues, the words are stored as possible values
		while (in >> word)
		{
			if (word == "@attribute")
				return Atr2Return;
			else if (word == "@examples")
			{
				return Atr2Return;
			}
			else
				(*Atr2Return).addValue(word);
		}
		return Atr2Return;
	}

}