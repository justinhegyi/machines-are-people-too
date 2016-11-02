#include "Evaluator.h"

Evaluator::Evaluator()
{
	holdOut = 10;
}

Evaluator::Evaluator(int holdOut)
{
	this->holdOut = holdOut;
}

Performance Evaluator::evaluate(const KNN &classifier)
{
	int folds = classifier.getFolds();
	DataSet allData = classifier.getTrain();
	DataSet tempTrain;
	KNN crossValidator;
	Performance totalPerformance;
	vector<int> randNum;
	int seed = allData.getSeed();
	int temp = 0;
	vector<DataSet> partitionedData;
	vector<Performance> performances;
	vector<double>stdDeviations;

	int allDataSize = allData.getExamples().size();
	srand(seed);
	for (int i = 0; i < allDataSize; i++)
	{
		temp = rand() % folds;
		randNum.push_back(temp);
	}

	for (int i = 0; i < folds; i++)
	{
		DataSet d;
		partitionedData.push_back(d);
	}

	int partitionNum;
	Example exToPush;
	for (int i = 0; i < allDataSize; i++)
	{
		partitionNum = randNum[i];
		exToPush = allData.getExamples()[i];
		partitionedData[partitionNum].add(exToPush);
	}

	int partitionedDataSize = partitionedData.size();
	for (int i = 0; i < partitionedDataSize; i++)	
	{
		crossValidator.setTest(partitionedData[i]);
		for (int j = 0; j < partitionedDataSize; j++)
		{
			if (j != i)
			{
				tempTrain = crossValidator.getTrain();
				tempTrain.add(partitionedData[j]);
				crossValidator.setTrain(tempTrain);
			}	
		}
		performances.push_back(crossValidator.classify(crossValidator.getTest()));
		cout << partitionedDataSize << " " << i << endl;
	}

	double sumAccuracy = 0.0;
	for (int i = 0; i < partitionedDataSize; i++)
	{
		sumAccuracy = (sumAccuracy + performances[i].getAccuracy());
	//	cout << " sum of accuracy = " << sumAccuracy << endl;
	}
	double meanAccuracy = sumAccuracy *1.0 / folds;
	
	for (int i = 0; i < partitionedDataSize; i++)
	{
		stdDeviations.push_back(pow(performances[i].getAccuracy() - meanAccuracy,2));
	}

	double sumStdDev = 0.0;
	for (int i = 0; i < partitionedDataSize; i++)
	{
		sumStdDev = sumStdDev + stdDeviations[i];
	}
	double meanStdDev = sumStdDev / folds;
	double finalStdDev = sqrt(meanStdDev);

	totalPerformance.setAccuracy(meanAccuracy);
	totalPerformance.setStdDev(finalStdDev);
	//cout << meanAccuracy << " +- " << finalStdDev << endl;
	return totalPerformance;
}

Performance Evaluator::evaluate(const NB &classifier)
{
	int folds = classifier.getFolds();
	DataSet allData = classifier.getTrain();
	DataSet tempTrain;
	KNN crossValidator;
	Performance totalPerformance;
	vector<int> randNum;
	int seed = allData.getSeed();
	int temp = 0;
	vector<DataSet> partitionedData;
	vector<Performance> performances;
	vector<double>stdDeviations;

	int allDataSize = allData.getExamples().size();
	srand(seed);
	for (int i = 0; i < allDataSize; i++)
	{
		temp = rand() % folds;
		randNum.push_back(temp);
	}

	for (int i = 0; i < folds; i++)
	{
		DataSet d;
		partitionedData.push_back(d);
	}

	int partitionNum;
	Example exToPush;
	for (int i = 0; i < allDataSize; i++)
	{
		partitionNum = randNum[i];
		exToPush = allData.getExamples()[i];
		partitionedData[partitionNum].add(exToPush);
	}

	int partitionedDataSize = partitionedData.size();
	for (int i = 0; i < partitionedDataSize; i++)
	{
		crossValidator.setTest(partitionedData[i]);
		for (int j = 0; j < partitionedDataSize; j++)
		{
			if (j != i)
			{
				tempTrain = crossValidator.getTrain();
				tempTrain.add(partitionedData[j]);
				crossValidator.setTrain(tempTrain);
			}
		}
		performances.push_back(crossValidator.classify(crossValidator.getTest()));
	//	cout << partitionedDataSize << " " << i << endl;
	}

	double sumAccuracy = 0.0;
	for (int i = 0; i < partitionedDataSize; i++)
	{
		sumAccuracy = (sumAccuracy + performances[i].getAccuracy());
		//	cout << " sum of accuracy = " << sumAccuracy << endl;
	}
	double meanAccuracy = sumAccuracy *1.0 / folds;

	for (int i = 0; i < partitionedDataSize; i++)
	{
		stdDeviations.push_back(pow(performances[i].getAccuracy() - meanAccuracy, 2));
	}

	double sumStdDev = 0.0;
	for (int i = 0; i < partitionedDataSize; i++)
	{
		sumStdDev = sumStdDev + stdDeviations[i];
	}
	double meanStdDev = sumStdDev / folds;
	double finalStdDev = sqrt(meanStdDev);

	totalPerformance.setAccuracy(meanAccuracy);
	totalPerformance.setStdDev(finalStdDev);
	//cout << meanAccuracy << " +- " << finalStdDev << endl;
	return totalPerformance;
}

Performance Evaluator::evaluate(const ID3 &classifier)
{
	int folds = holdOut;
	DataSet allData = classifier.getTrain();
	DataSet newTrain(allData.getAttributes());
	DataSet newTest(allData.getAttributes());
	int classIndex = allData.getAttributes().getClassIndex();
	Performance totalPerformance;
	vector<int> randNum;
	int seed = allData.getSeed();
	int temp = 0;
	int right = 0;
	int wrong = 0;

	int allDataSize = allData.getExamples().size();
	srand(seed);
	for (int i = 0; i < allDataSize; i++)
	{
		temp = rand() % folds;
		randNum.push_back(temp);
	}

	//if holdout
	for (int i = 0; i < allDataSize; i++)
	{
		if (randNum[i] == folds -1)
			newTest.add(allData.getExamples().at(i));
		else 
			newTrain.add(allData.getExamples().at(i));
	}

	ID3 tree(newTrain);
	for (Example e : newTest.getExamples())
	{
	//	cout << tree.classify(e) << " " << e[classIndex] << endl;
		if (tree.classify(e) == e[classIndex])
			right++;
		else
			wrong++;
	}
	
	return Performance(right, wrong);

}

Performance Evaluator::evaluate(const RDF &classifier)
{
	int folds = holdOut;
	DataSet allData = classifier.getTrain();
	DataSet newTrain(allData.getAttributes());
	DataSet newTest(allData.getAttributes());
	int classIndex = allData.getAttributes().getClassIndex();
	Performance totalPerformance;
	vector<int> randNum;
	int seed = allData.getSeed();
	int temp = 0;
	int right = 0;
	int wrong = 0;

	int allDataSize = allData.getExamples().size();
	srand(seed);
	for (int i = 0; i < allDataSize; i++)
	{
		temp = rand() % folds;
		randNum.push_back(temp);
	}

	//if holdout
	for (int i = 0; i < allDataSize; i++)
	{
		if (randNum[i] == folds - 1)
			newTest.add(allData.getExamples().at(i));
		else
			newTrain.add(allData.getExamples().at(i));
	}

	RDF trees;
	trees.setTreeNum(3);
	trees.train(newTrain);
	Performance p = trees.classify(newTest);
	

	return p;

}
/*
Performance Evaluator::evaluate(const NN &classifer)
{
	srand(time(NULL));
	DataSet train = classifer.getTrain();
	Attributes atts = train.getAttributes();
	DataSet d(atts);
	DataSet validation(atts);
	Examples examples = train.getExamples();
	int randNum = 0;

	for (int i = 0; i < examples.size(); i++)
	{
		randNum = rand() % holdOut;
		if (randNum == 0)
			validation.add(examples.at(i));
		else
			d.add(examples.at(i));
	}

	NN newClassifier;
	newClassifier.train(d);
	Performance p = newClassifier.classify(validation);
	return p;
}
*/