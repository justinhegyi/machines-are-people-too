#include "KNN.h"

KNN::KNN()
{
	setK(7);
	setFolds(10);
}

KNN::KNN(int k)
{
	setK(k);
}


KNN::KNN(int k, const DataSet &train, const DataSet &test)
{
	setK(k);
	setTrain(train);
	setTest(test);
}

KNN::~KNN()
{
	delete[] minValues;
}

void KNN::setK(int k)
{
	this->k = k;
	minValues = new int[k];
}


void KNN::buildModel(const DataSet &train)
{
	setTrain(train);
}

Performance KNN::classify(const DataSet &d1)
{
	int correct = 0;
	int wrong = 0;
	for (Example e : d1.getExamples())
	{
		if (e[e.size()-1] == classify(e))
			correct++;
		else
			wrong++;
	}
	Performance p1(correct, wrong);
	return p1;
}

double KNN::classify(const Example &e)
{
	int distance = 0;
	int class1Count =  0;
	int class2Count = 0;
	int maxVal = 0;
	int maxIndex = -1;
	Example *closestKExamples = new Example[k];

	for (int i = 0; i < k; i++)
	{
		minValues[i] = INT_MAX;
	}


	for (Example ex : this->getTrain().getExamples())
	{
		int size = e.size();
		for (int i = 0; i < size; i++)
		{
			if (e[i] != ex[i])
				distance++;
		}

		maxVal = minValues[0];
		maxIndex = 0;
		for (int j = 1; j < k; j++)
		{
			if (minValues[j] > maxVal)
			{
				maxVal = minValues[j];
				maxIndex = j;
			}
		}
		if (distance < maxVal)
		{
			minValues[maxIndex] = distance;
			closestKExamples[maxIndex] = ex;
		}
	}
	
	int allValues;
	for (int i = 0; i < k; i++)
	{
		allValues = (closestKExamples[i])[e.size() -1];
	}
	if (allValues > k * 1.0 / 2)
		return 1;
	else
		return 0;
}

int KNN::getFolds() const
{
	return folds;
}
void KNN::setFolds(int folds)
{
	this->folds = folds;
}

int KNN::getK() const
{
	return k;
}