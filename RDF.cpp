#include "RDF.h"

RDF::RDF()
{
	treeNum = 5;
	k = 13;
}

RDF::RDF(const int num, const int k)
{
	treeNum = num;
	this->k = k;
}

RDF::~RDF()
{

}

void RDF::insertTree(const ID3 &tree, const int pos)
{
	trees[pos] = tree;
}

double RDF::classify(const Example &e)
{
	try {
		vector<double> votes(classSize, 0.0);
		double maxVal = 0;
		double maxPos = 0;

		for (ID3 tree : trees)
		{
//			cout << votes[tree.classify(e)] << endl;
			if (tree.classify(e) != -1)
				votes[tree.classify(e)] = votes[tree.classify(e)] + 1;
		}

		for (int i = 0; i < votes.size(); i++)
		{
			if (votes[i] > maxVal)
			{
				maxVal = votes[i];
				maxPos = i;
			}
		}
		return maxPos;

	}
	catch (std::out_of_range &oor)
	{
		cout << oor.what() << endl;
	}
}

Performance RDF::classify(const DataSet &ds)
{
	int correct = 0;
	int classIndex = ds.getAttributes().getClassIndex();
	Examples ex = ds.getExamples();

	for (int i = 0; i < ex.size(); i++)
	{
		Example e = ex.at(i);
		if (classify(e) == e[classIndex])
			correct++;
	}
	Performance p(correct, ds.getExamples().size() - correct);
	//cout << "# correct: " << correct << endl;
	return p;
}

void RDF::train(const DataSet &ds)
{
	vector<DataSet> sets;
	Examples exs = ds.getExamples();
	int exSize = exs.size();
	srand(time_t(ds.getSeed()));
	Attributes oldAtts = ds.getAttributes();
	int classDomain = oldAtts.getClassAttribute()->getSize();
	this->classSize = classDomain;

	for (int i = 0; i < treeNum; i++)
	{
		DataSet newDs(oldAtts);
		for (int j = 0; j < exSize; j++)
		{
			int randInt = rand() % exSize;
			newDs.add(exs[randInt]);
		}
		ID3 randTree;
		randTree.buildRand(newDs, k);
		randTree.setTrain(newDs);
		trees.push_back(randTree);
	}
}

void RDF::setTreeNum(const int num)
{
	treeNum = num;
}

