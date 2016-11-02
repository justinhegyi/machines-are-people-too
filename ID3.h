#ifndef SPRING2016MLPROJECT_ID3_H
#define SPRING2016MLPROJECT_ID3_H

#include "Classifier.h"
#include "ID3Node.h"


class ID3 : public Classifier
{
private:
	ID3Node * root;
	Attributes attributes;
public:
	ID3();
	ID3(DataSet &train);
	~ID3();

	void train(const DataSet &train);
	void train(ID3Node * node, const DataSet &train);
	double classify(const Example &e);
	int classify(ID3Node * node, const Example &e);

	//for RDF
	void buildRand(const DataSet & ds, const int &k);
	void buildRand(ID3Node * node, const DataSet &ds, const int &k);

};

#endif