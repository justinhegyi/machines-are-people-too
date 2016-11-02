#ifndef SPRING2016_MLProject2_KNN_H
#define SPRING2016_MLProject2_KNN_H

#include "Classifier.h"

class KNN : public Classifier
{
private:

	int k;
	int *minValues;
	int folds;

public:

	KNN();
	KNN(const int k);
	KNN(const int k, const DataSet &train, const DataSet &test);
	~KNN();
	int getFolds() const;
	void setFolds(int folds);
	int getK() const;
	void setK(const int k);
	void buildModel(const DataSet &train);
	Performance classify(const DataSet &d1);
	double classify(const Example &e);
};


#endif