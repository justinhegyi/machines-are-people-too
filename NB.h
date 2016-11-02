#ifndef SPRING2016_MLProject2_NB_H
#define SPRING2016_MLProject2_NB_H

#include "Classifier.h"
#include "Performance.h"

class NB : public Classifier
{
private:
	vector < vector < vector < double > > > counts;
	vector < vector < vector < double > > > probabilities;

public:
	NB();
	void buildModel();
	Performance classify(const DataSet &d1);
	double classify(const Example &e);
	void addOne() const;
};

class Probability
{
private:
	Attribute atr;
	double count;
	int classIndex;
public:
	Probability();
};

#endif