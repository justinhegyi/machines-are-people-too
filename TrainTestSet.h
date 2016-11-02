#ifndef SPRING2016_MLProject2_TrainTestSets_H
#define SPRING2016_MLProject2_TrainTestSets_H

#include "Dataset.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////TrainTestSets////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TrainTestSets
{
	friend ostream &operator<<(ostream &out, const TrainTestSets &tts);

protected:
	DataSet train;
	DataSet test;

public:
	TrainTestSets();
	TrainTestSets(const vector<string> &options);
	DataSet getTrainingSet() const;
	DataSet getTestingSet() const;
	void setTrainingData(const DataSet &train);
	void setTestingSet(const DataSet &test);
	void setOptions(const vector<string> &options);
};

#endif