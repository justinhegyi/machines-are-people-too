#include "Classifier.h"

Classifier::Classifier()
{
	DataSet train;
	DataSet test;
}

Classifier::Classifier(const DataSet &train, const DataSet &test)
{
	setTrain(train);
	setTest(test);
}

void Classifier::setTrain(const DataSet &train)
{
	this->train = train;
}

void Classifier::setTest(const DataSet &test)
{
	this->test = test;
}

DataSet Classifier::getTest() const
{
	return test;
}

DataSet Classifier::getTrain() const
{
	return train;
}

int Classifier::getFolds() const
{
	return folds;
}

void Classifier::setFolds(int folds)
{
	this->folds = folds;
}