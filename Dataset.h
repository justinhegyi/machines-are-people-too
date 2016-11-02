#ifndef SPRING2016_MLProject2_Dataset_H
#define SPRING2016_MLProject2_Dataset_H

#include "Examples.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////DataSet//////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DataSet
{
	friend ostream &operator<<(ostream &out, const DataSet &ds);

protected:
	string name;
	Attributes attributes;
	Examples examples;
	long seed;
	//new for ID3
	bool homogeneous;
	int homogeneousClass;


public:
	DataSet();
	DataSet(const Attributes &attributes);
	void add(const DataSet &dataset);
	void add(const Example &example);
	Attributes getAttributes() const;
	Examples getExamples() const;
	void setExamples(const Examples &e);
	long getSeed() const;
	bool getHasNominalAttributes() const;
	bool getHasNumericAttributes() const;
	void load(string filename);
	void parse(istream &in);
	void setOptions(const vector<string> &options);
	void setSeed(long seed);
	void setName(const string &s);
	//for ID3
	int getBestSplittingAttribute() const;
	double gain(const int &attribute) const;
	double entropy() const;
	bool isHomogeneous() const;
	void setHomogeneous(bool isTrue);
	int getHomogeneousClass() const;
	vector<DataSet> split(const int & attribute) const;
	//for NN
	DataSet nominalToBinary();
	// for RDF
	int getBestRandAtr(int k) const;

};

#endif