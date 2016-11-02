#include "Examples.h"
#include "NominalAttribute.h"
#include "NumericAttribute.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Examples implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Examples::Examples(const Attributes &attributes)
{
	this->attributes = attributes;
}

Examples::Examples()
{
	Attributes attr;
	this->attributes = attr;
}

void Examples::parse(istream &in)
{
	string temp;
	string word;
	double numToStore = 0;
	int pos = 0;
	Attribute * atr;
	Example e;

	while (in >> word)
	{
		//cout << word << " ";
		atr = this->attributes.get(pos);
		if (typeid(*atr) == typeid(NominalAttribute))
		{
			numToStore = dynamic_cast<NominalAttribute *>(atr)->getIndex(word);
		}
		else
		{
			numToStore = stod(word);
		}
		e.push_back(numToStore);
		pos++;

		while (in.peek() == ' ')
			in.get();
		if (in.peek() == '\n')
		{
			//cout << "about to push an example" << endl;
			if (e.size() != 0)
				push_back(e);
			e.clear();
			pos = 0;
		}
	}
	//cout << " about to push the last example, woo!" << endl;
	if (e.size() != 0)
		push_back(e);
}

void Examples::setAttributes(const Attributes &attributes)
{
	this->attributes = attributes;
}


ostream& operator<<(ostream &out, const Examples &e)
{
	out << "@examples" << endl << endl;
	int size = e.size();
	for (int i = 0; i < size; i++)
	{
		Example currentExample = e.at(i);
		int exSize = currentExample.size();

		for (int j = 0; j < exSize; j++)
		{
			Attribute * atr = e.attributes.get(j);
			if (typeid(*atr) == typeid(NumericAttribute))
			{
				out << currentExample[j] << " ";
			}
			else
			{
				out << dynamic_cast<NominalAttribute*>(atr)->getValue(currentExample[j]) << " ";
			}
		}
		out << endl;
	}
	return out;
}
