#ifndef SPRING2016_MLProject5_RDF_H
#define SPRING2016_MLProject5_RDF_H

#include "ID3.h"

class RDF : public Classifier
{
public:
	RDF();
	RDF(const int num, const int k);
	~RDF();
	void insertTree(const ID3 &tree, const int pos);
	double classify(const Example &e);
	Performance classify(const DataSet &ds);
	void train(const DataSet &ds);
	void setTreeNum(const int num);

private:
	vector<ID3> trees;
	int classSize;
	int treeNum;
	int k;
};

#endif