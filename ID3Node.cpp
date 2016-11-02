#include "ID3Node.h"

ID3Node::ID3Node()
{
	label = -1;
}

ID3Node::~ID3Node()
{
	for (int i = 0; i < children.size(); i++)
	{
		delete[] children[i];
	}
}

int ID3Node::size()
{
	return children.size();
}

void ID3Node::setLabel(const unsigned &label)
{
	this->label = label;
}

unsigned ID3Node::getLabel()
{
	return label;
}

void ID3Node::setAttribute(const unsigned &attribute)
{
	this->attribute = attribute;
}

unsigned ID3Node::getAttribute()
{
	return attribute;
}