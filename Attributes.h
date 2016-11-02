#ifndef SPRING2016_MLProject2_Attributes_H
#define SPRING2016_MLProject2_Attributes_H

#include "Attribute.h"
#include "NominalAttribute.h"
#include "NumericAttribute.h"
#include "AttributeFactory.h"
#include <vector>
#include <typeinfo>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////Attributes/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Attributes
{

	friend ostream &operator<<(ostream &out, const Attributes &a);

private:
	vector<Attribute*> attributes;
	bool hasNumericAttributes;
	bool hasNominalAttributes;
	int classIndex;

public:
	Attributes();

	void add(Attribute *attribute);
	bool getHasNominalAttributes() const;
	bool getHasNumericAttributes() const;
	Attribute* get(int i) const;
	Attribute* getClassAttribute() const;
	int getIndex(string name) const;
	int getSize() const;
	void parse(istream &in);
	void setClassIndex(int classIndex);
	int getClassIndex() const;
};

#endif