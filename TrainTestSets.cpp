#include "TrainTestSet.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											TrainTestSets implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TrainTestSets::TrainTestSets()
{

}

TrainTestSets::TrainTestSets(const vector<string> &options)
{
	this->setOptions(options);
}


DataSet TrainTestSets::getTrainingSet() const
{
	return train;
}

DataSet TrainTestSets::getTestingSet() const
{
	return test;
}

void TrainTestSets::setTrainingData(const DataSet &train)
{
	this->train = train;
}

void TrainTestSets::setTestingSet(const DataSet &test)
{
	this->test = test;
}

ostream& operator<<(ostream & out, const TrainTestSets &tts)
{
	return out;
}

void TrainTestSets::setOptions(const vector<string> &options)
{
	//this->options = options;
}