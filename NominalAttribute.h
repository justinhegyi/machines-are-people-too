#ifndef SPRING2016_MLProject2_NominalAttribute_H
#define SPRING2016_MLProject2_NominalAttribute_H

#include "Attribute.h"
#include <vector>
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////NominalAttribute///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NominalAttribute : public Attribute
{
public:
	NominalAttribute();
	NominalAttribute(string name);
	void addValue(string value);
	virtual int getSize() const;
	string getValue(int index);
	int getIndex(string value);
	virtual void print(ostream & out = cout) const;


private:
	vector<string> domain;
};


#endif