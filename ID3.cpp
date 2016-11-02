#include "ID3.h"

ID3::ID3()
{
	this->root = new ID3Node();
}

ID3::ID3(DataSet &train)
{
	this->root = new ID3Node();
		train.setHomogeneous(false);
	this->train(train);
}

ID3::~ID3()
{
}

void ID3::train(const DataSet &train)
{
	this->train(root, train);
}

void ID3::train(ID3Node * node, const DataSet &train)
{
	if (train.isHomogeneous())
	{
		node->setLabel(train.getHomogeneousClass());
		//cout << train.getHomogeneousClass() << endl;
	}
	else
	{
		node->setAttribute(train.getBestSplittingAttribute());
		if (node->getAttribute() != -1)
		{
			vector<DataSet> splits = train.split(node->getAttribute());

			for (int i = 0; i < splits.size(); i++)
			{
				ID3Node * temp = new ID3Node();
				node->children.push_back(temp);
				if (splits[i].getExamples().size() == 0)
				{
					int classIndex = train.getAttributes().getClassIndex();
					int classSize = train.getAttributes().get(classIndex)->getSize();
					vector<int> classCounts(classSize, 0);
					int totalCount = train.getExamples().size();
					for (int j = 0; j < totalCount; j++)
					{
						Example e = train.getExamples().at(j);
						classCounts[e[classIndex]] = classCounts[e[classIndex]] + 1;
					}

					int max = 0;
					int pos = -1;
					for (int j = 0; j < classCounts.size(); j++)
					{
						if (classCounts[j] > max)
						{
							max = classCounts[j];
							pos = j;
						}
					}
					node->setLabel(pos);
				}
				else
				{
					this->train(node->children[i], splits[i]);
				}

			}
		
		}
		else {
			if (train.getExamples().size() != 0)
				node->setLabel(train.getHomogeneousClass());
		}
	}
}


double ID3::classify(const Example &e)
{
	//returns -1 for 19 - 2
	return classify(root, e);
}

int ID3::classify(ID3Node * node, const Example &e)
{
	try
	{
		if (node->size() == 0)
			return node->getLabel();
		else
		{
			int atr = node->getAttribute();
			return classify(node->children[e[atr]], e);
		}
	}
	catch (std::out_of_range &oor)
	{
		cout << oor.what() << endl;
	}
}

//for RDF
void ID3::buildRand(const DataSet & ds, const int &k)
{
	buildRand(root, ds, k);
}

void ID3::buildRand(ID3Node * node, const DataSet &ds, const int &k)
{
	try{
		if (ds.isHomogeneous())
		{
			node->setLabel(ds.getHomogeneousClass());
			//cout << ds.getHomogeneousClass() << endl;;
		}
		else
		{
			//change to parameter
			int atr = ds.getBestRandAtr(13);
			if (atr == -1)
				train(node, ds);
			else
			{
				node->setAttribute(atr);
				if (node->getAttribute() != -1)
				{
					vector<DataSet> splits = ds.split(node->getAttribute());

					for (int i = 0; i < splits.size(); i++)
					{
						ID3Node * temp = new ID3Node();
						node->children.push_back(temp);
						if (splits[i].getExamples().size() == 0)
						{
							int classIndex = ds.getAttributes().getClassIndex();
							int classSize = ds.getAttributes().get(classIndex)->getSize();
							vector<int> classCounts(classSize, 0);
							int totalCount = ds.getExamples().size();
							for (int j = 0; j < totalCount; j++)
							{
								Example e = ds.getExamples().at(j);
								classCounts[e[classIndex]] = classCounts[e[classIndex]] + 1;
							}

							int max = 0;
							int pos = -1;
							for (int j = 0; j < classCounts.size(); j++)
							{
								if (classCounts[j] > max)
								{
									max = classCounts[j];
									pos = j;
								}
							}
							node->setLabel(pos);
						}
						else
						{
							this->buildRand(node->children[i], splits[i], k);
						}

					}

				}
				else {
					if (ds.getExamples().size() != 0)
						node->setLabel(ds.getHomogeneousClass());
				}
			}
		}
		//cout << "random tree trained!" << endl;
	}
	catch (std::out_of_range &oor)
	{
		cout << oor.what() << endl;
	}
}