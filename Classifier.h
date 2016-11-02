#ifndef SPRING2016_MLProject2_Classifier_H
#define SPRING2016_MLProject2_Classifier_H

#include "Dataset.h"
#include "Performance.h"

class Classifier
{

private: 
	DataSet train;
	DataSet test;
	int folds;

public:
	Classifier();
	Classifier(const DataSet &train, const DataSet &test);
	void setTrain(const DataSet &train);
	void setTest(const DataSet &test);
	DataSet getTrain() const;
	DataSet getTest() const;
	virtual void buildModel(const DataSet &train){}
	virtual Performance classify(const DataSet &d1){ Performance p1; return p1; }
	virtual double classify(const Example &e){ return -2; }
	int getFolds() const;
	void setFolds(int k);

};


#endif