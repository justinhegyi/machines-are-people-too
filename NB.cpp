#include "NB.h"

NB::NB()
{
	counts[0][0].assign(8.0, 100);
}

void NB::addOne() const
{
	int exSize = 0;
	exSize = getTrain().getExamples()[0].size();

}

void NB::buildModel()
{
	double classIndex = 0.0;
	

	for (Example e : this->getTrain().getExamples())
	{
		
		classIndex = e[e.size() - 1];
		/*if (counts[classIndex].empty())
		{
			vector < vector < double > > blank;
			for (int j = 0; j < classIndex; j++)
				counts.push_back(blank)
		} */
		int sizeOfClass = counts[classIndex].size();
		for (int i = 0; i < sizeOfClass; i++)
		{
			
			if (counts[classIndex][i].empty())
			{
				for (int j = 0; j < e[i]; j++)
				{
					counts[classIndex][i].push_back(1.0);
				}
			}
			counts[classIndex][i][e[i]] = counts[classIndex][i][e[i]] + 1;
		}
	}

	int countsSize = counts.size();
	double nvj = 0;
	int classSize = 0;
	int domainSize = 0;
	double totalFeatureCount = 0;
	double totalDomainCount = 0;
	double totalClassCount = 0;
	double probability = 0.0;

	for (int i = 0; i < countsSize; i++)
	{
		classSize = counts[i].size();
		for (int j = 0; j < classSize; j++)
		{
			domainSize = counts[i][j].size();
			for (int k = 0; k < domainSize; k++)
			{
				totalClassCount = totalClassCount + counts[i][j][k];
			}
		}
		for (int j = 0; j < classSize; j++)
		{
			domainSize = counts[i][j].size();
			for (int k = 0; k < domainSize; k++)
			{
				nvj =  counts[i][j][k];
			}
			probability = (nvj + 1) / (totalClassCount + domainSize);
			probabilities[i][j].push_back(probability);
		}
	}
}

Performance NB::classify(const DataSet &d1)
{
	int correct = 0;
	int wrong = 0;
	for (Example e : d1.getExamples())
	{
		if (classify(e) == e[e.size() - 1])
			correct++;
		else
			wrong++;
	}
	Performance p1(correct, wrong);
	return p1;
}

double NB::classify(const Example &e)
{
	double product = 1;
	double maxProduct = -1;
	int productIndex = -1;
	int exSize = e.size();
	int probabilitySize = probabilities.size();

	for (int i = 0; i < probabilitySize; i++)
	{
		for (int j = 0; j < exSize; j++)
		{
			product = product * probabilities[i][j][e[j]];

		}
		if (product > maxProduct)
		{
			maxProduct = product;
			productIndex = i;
		}
	}
	return productIndex;
}
