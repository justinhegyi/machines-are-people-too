#ifndef SPRING2016_MLProject2_AttributeFactory_H
#define SPRING2016_MLProject2_AttributeFactory_H

#include "Attribute.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////AttributeFactory//////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AttributeFactory
{
public:
	Attribute* make(istream &in);

};

#endif