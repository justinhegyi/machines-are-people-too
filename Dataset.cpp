#include "Dataset.h"
#include<sstream>
#include<fstream>



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											DataSet implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DataSet::DataSet()
{
	this->name = "Empty Dataset";
	//this->homogeneous = true;
	homogeneousClass = -1;
	this->seed = 202687034;
}

DataSet::DataSet(const Attributes &attributes)
{
	this->attributes = attributes;
	//this->homogeneous = true;
	homogeneousClass = -1;
	this->seed = 202687034;
}

void DataSet::add(const DataSet &dataset)
{
	for (Example ex : dataset.getExamples())
	{
		add(ex);
	}
}

void DataSet::add(const Example &example)
{
	if (example.size() != 0)
	{
		examples.push_back(example);
		double exampleClass = example[attributes.getClassIndex()];
		if (homogeneousClass == -1)
		{
			homogeneousClass = exampleClass;
			homogeneous = true;
		}
		else if (homogeneous)
		{
			if (homogeneousClass != exampleClass)
				homogeneous = false;
		}
	}
}

void DataSet::parse(istream &in)
{
	string word;
	in >> word;
	attributes.parse(in);
	examples.setAttributes(attributes);
	examples.parse(in);
}

void DataSet::load(string filename)
{
	std::ifstream file;
	file.open(filename);
	if (!file.is_open())
		throw logic_error("file open error");

	string temp;
	while (getline(file, temp))
	{
		//cout << "got a line" << endl;
		istringstream line(temp);
		string word;
		while (line >> word) {
			//cout << word << endl;
			if (word == "@dataset")
			{
				line >> word;
				this->name = word;
				this->parse(file);
			}
		}
	}
}

ostream& operator<<(ostream &out, const DataSet &ds)
{
	out << "@dataset " << ds.name << endl << endl;
	out << ds.attributes << endl;
	out << ds.examples << endl;
	return out;
}

Attributes DataSet::getAttributes() const
{
	return this->attributes;
}

Examples DataSet::getExamples() const
{
	return this->examples;
}

long DataSet::getSeed() const
{
	return this->seed;
}

bool DataSet::getHasNominalAttributes() const
{
	return getAttributes().getHasNominalAttributes();
}

bool DataSet::getHasNumericAttributes() const
{
	return getAttributes().getHasNumericAttributes();
}

bool DataSet::isHomogeneous() const
{
	return homogeneous;
}

int DataSet::getHomogeneousClass() const
{
	return homogeneousClass;
}

void DataSet::setName(const string &s)
{
	name= s;
}

void DataSet::setExamples(const Examples &e)
{
	examples = e;
}

void DataSet::setHomogeneous(bool isTrue)
{
	homogeneous = isTrue;
}


void DataSet::setOptions(const vector<string> &options)
{

}

void DataSet::setSeed(long seed)
{
	this->seed = seed;
}

int DataSet::getBestSplittingAttribute() const
{
	double tempGain = 0;
	double maxGain = 0;
	int pos = -1;
	Attribute maxAttr;
	for (int i = 0; i < attributes.getSize(); i++)
	{
		if (i != attributes.getClassIndex())
		{
			tempGain = gain(i);
			if (tempGain > maxGain)
			{
				maxGain = tempGain;
				//maxAttr = *(attributes.get(i));
				pos = i;
			}
		}
	}
	//std::cout << "best splitting attribute is: " << pos << " with the value: " << maxGain << endl;
	return pos;
}

double DataSet::gain(const int & attribute) const
{

	double currentEntropy = this->entropy();
	double tempEntropy = 0.0;
	double size = 0;
	double totalSize = examples.size();

		vector<DataSet> splits  = split(attribute);
		for (DataSet ds : splits)
		{
			size = ds.getExamples().size();
			if (size != 0)
			{
				tempEntropy = tempEntropy + (size / totalSize) * ds.entropy();
			}	
		}
		//cout << "gain from splitting on " << attribute << " is: " << currentEntropy - tempEntropy << endl;
		return currentEntropy - tempEntropy;
}



double DataSet::entropy() const
{
	int classIndex = attributes.getClassIndex();
	int classSize = attributes.getClassAttribute()->getSize();
	vector<double> counts(classSize, 0.0);
	double entropy = 0.0;
	double total = examples.size();
	double ratio = 0.0;


	for (Example e : examples)
	{
		if (e.size() != 0)
			counts[e[classIndex]] = counts[e[classIndex]] + 1;
	}
	
	for (int i = 0; i < classSize; i++)
	{
		if (counts[i] != 0)
		{
			ratio = counts[i] / total;
			entropy = entropy - (ratio * log2(ratio));
		}
	}

	return entropy;
}

vector<DataSet> DataSet::split(const int & attribute) const
{
	int domain = attributes.get(attribute)->getSize();
	vector<DataSet> splits;
	for (int i = 0; i < domain; i++)
	{
		DataSet temp(attributes);
		splits.push_back(temp);
	}

	for (Example e : examples)
	{
		splits[e[attribute]].add(e);
	}

	return splits;
}


void convertToBinary(vector<int> &v, int numToConvert)
{
	v.clear();
	if (numToConvert / 2 != 0)
		convertToBinary(v, numToConvert / 2);
	v.push_back(numToConvert % 2);
}


DataSet DataSet::nominalToBinary()
{
	Attributes newAttributes;
	Attribute *atr;
	vector<int> binDigits;
	vector<int> domainDigits;
	int classIndex = attributes.getClassIndex();

	for (int i = 0; i < attributes.getSize() -1; i++)
	{
		atr = attributes.get(i);
		NominalAttribute *nAtr = NULL;
		
		//ensures that the attribute is nominal before proceeding
		if (typeid(*atr) == typeid(NominalAttribute))
		{
			nAtr = (dynamic_cast<NominalAttribute*>(atr));
			int domain = nAtr->getSize();
			if (domain > 2)
			{
				int current = domain;
				for (int atrNum = 0; current != 0; atrNum++)
				{
					NominalAttribute * tempAtr = new NominalAttribute();
					tempAtr->setName(nAtr->getName() + to_string(atrNum));
					tempAtr->addValue(to_string(0));
					tempAtr->addValue(to_string(1));
					newAttributes.add(tempAtr);

					current = current / 2;
				}
			}
			else
			{
				newAttributes.add(atr);
			}
		}
	}
		NumericAttribute * tempAtr = new NumericAttribute;
		tempAtr->setName("bias");
		newAttributes.add(tempAtr);
		newAttributes.add(attributes.get(classIndex));

	std::cout << newAttributes << endl;

	Examples newExamples(newAttributes);
	//changing the examples into binary format, an unfortunate amount of repeat code, but trying to covert them
	//at the same time was giving me trouble
	for (Example e : examples)
	{
		Example newExample;
		for (int i = 0; i < attributes.getSize() - 1; i++)
		{
		atr = attributes.get(i);
		NominalAttribute nAtr;

		//ensures that the attribute is nominal before proceeding
		if (typeid(*atr) == typeid(NominalAttribute))
		{
			nAtr = *(dynamic_cast<NominalAttribute*>(atr));
			int domain = nAtr.getSize();
			if (domain > 2)
			{
				convertToBinary(binDigits, e[i]);
				convertToBinary(domainDigits, domain);
				while (binDigits.size() < domainDigits.size())
					binDigits.push_back(0.0);
				for (unsigned int j = 0; j < binDigits.size(); j++)
				{
					newExample.push_back(binDigits[j]);
				}
			}
			else
			{
				newExample.push_back(e[i]);
			}
		}
		}
		newExample.push_back(-1.0);
		newExample.push_back(e[attributes.getClassIndex()]);
		//cout << newExample << endl;
		newExamples.push_back(newExample);
		//cout << newExamples.size() << endl;
	}

	DataSet newDataSet = DataSet(newAttributes);
	newDataSet.setExamples(newExamples);
	newDataSet.setName(name + "Bin");
	newDataSet.setSeed(this->getSeed());
	return newDataSet;
}

int DataSet::getBestRandAtr(int k) const
{
	vector<int> used(attributes.getSize(), 0);
	int classIndex = attributes.getClassIndex();
	int usedCounter = 0;
	vector<double> gains;
	vector<int> attr;
	srand(time_t(seed));
	
	while (gains.size() < k && used.size() - usedCounter > k)
	{
		int randInt = rand() % used.size();
		if (randInt != classIndex && used[randInt] == 0)
		{
				double tempGain = gain(randInt);
				if (tempGain > 0.0)
				{
					gains.push_back(tempGain);
					attr.push_back(randInt);
				}
				used[randInt] = used[randInt] + 1;
				usedCounter++;
		}
	}

	double max = 0;
	int maxPos = -1;
	if (gains.size() > 0)
	{
		for (int i = 0; i < gains.size(); i++)
		{
			if (gains[i] > max)
			{
				max = gains[i];
				maxPos = i;
			}
		}
	}
	if (maxPos == -1)
		return -1;

	//cout << "best random attribute is " << attr[maxPos] << " with the value " << max << endl;
	return attr[maxPos];
}