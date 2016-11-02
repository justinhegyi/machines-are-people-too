#include "NN.h"
//#include <math.h>


NN::NN()
{
	hNodes = 3;
	learningRate = .9;
	Emin = .1;
}

NN::NN(int hNodes, double learningRate, double Emin)
{
	sethNodes(hNodes);
	setLearningRate(learningRate);
	setEmin(Emin);

}

double sig(double num)
{
	double exponent = -1 * num;
	return 1.0 / (1 + exp(exponent));
}

void NN::train(DataSet &ds)
{
	setTrain(ds);
	DataSet d = ds.nominalToBinary();
	Attributes atts = d.getAttributes();
	int classIndex = atts.getClassIndex();
	int classSize = atts.get(classIndex)->getSize();
	Examples exs = ds.getExamples();
	Example ex = exs.at(0);
	vector <double> y;
	vector<double> output;
	vector <double > oESig;
	vector <double > yESig;
	srand(time(NULL));
	double randNum;
	double E = 1.0;
	int q = 0;
	int epoch = 0;

	for (int i = 0; i < classSize; i++)
		output.push_back(0.0);

	//ex.size() -1 to skip classLabel
	for (int j = 0; j < ex.size() - 1; j++)
	{
		V.clear();
		//hNodes + 1 to get a weight for biased neuron
		for (int i = 0; i < hNodes +1; i++)
		{
			randNum = rand() % 30 + 10;
			randNum = randNum * .01;
			V.push_back(randNum);
		}
		I.push_back(V);
	}

	for (int j = 0; j < hNodes + 1; j++)
	{
		W.clear();
		//hNodes + 1 to get a weight for biased neuron
		for (int i = 0; i < output.size(); i++)
		{
			randNum = rand() % 30 + 10;
			randNum = randNum * .01;
			W.push_back(randNum);
		}
		J.push_back(W);
	}

	Example e;
	while (E > Emin && epoch <= 3000)
	{
		epoch++;
		E = 0;
		double yVal = 0.0;
		double oVal = 0.0;
		double ySig = 0.0;
		for (int i = 0; i < exs.size(); i++)
		{
			yESig.clear();
			oESig.clear();
			y.clear();
			e = exs.at(i);
			for (int k = 0; k < V.size(); k++)
			{
				yVal = 0.0;
				for (int j = 0; j < I.size(); j++)
				{

					yVal = yVal + e[j] * I[j][k];
				}
				if (k != V.size() - 1)
					y.push_back(sig(yVal));
				else
					y.push_back(-1.0);
			} //  END load y loop

			for (int j = 0; j < output.size(); j++)
			{
				for (int k = 0; k < y.size(); k++)
				{
					oVal = oVal + J[k][j] * y[k];
				}
				output[j] = (sig(oVal));
			} // end load output loop

			//calculate error
			for (int j = 0; j < output.size(); j++)
			{
				E = E + .5 * pow(e[classIndex] - output[j], 2);
				//cout << "expected: " << e[classIndex] << " actual: " << output[j] << endl;
			}

			//compute error signals
			for (int j = 0; j < output.size(); j++)
			{
				oESig.push_back((e[classIndex] - output[j]) * (1 - output[j]) * output[j]);
			}

			for (int j = 0; j < J.size(); j++)
			{
				ySig = 0.0;
				for (int k = 0; k < output.size(); k++)
				{
					ySig = ySig + oESig[k] * J[j][k];
				}
				yESig.push_back(y[j] * (1 - y[j]) * ySig);
			}

			//adjust output layer weights 
			for (int j = 0; j < J.size(); j++)
			{
				for (int k = 0; k < output.size(); k++)
				{
					J[j][k] = J[j][k] + learningRate * oESig[k] * y[j];
				}
			}

			//adjust hidden layer weights
			for (int j = 0; j < I.size(); j++)
			{
				for (int k = 0; k < J.size(); k++)
				{
					I[j][k] = I[j][k] + learningRate * yESig[k] * e[j];
				}
			}
			q++;
		} // END Examples for loop
		if (epoch % 1000 == 0)
		{
			cout << "epoch " << epoch << " error: " << E << endl;
		/*	for (int t = 0; t < I.size(); t++)
			{
				for (int r = 0; r < J.size(); r++)
					cout << I[t][r] << " ";
				cout << endl;
			}
			for (int t = 0; t < J.size(); t++)
			{
				for (int r = 0; r < output.size(); r++)
					cout << J[t][r] << " ";
				cout << endl;
			}*/
		}
	}

} // END train

Performance NN::classify(const DataSet &ds)
{
	int correct = 0;
	int classIndex = ds.getAttributes().getClassIndex();
	Examples ex = ds.getExamples();

	for (int i = 0; i < ex.size();i++)
	{
		Example e = ex.at(i);
		//cout << classify(e) << e[classIndex];
		if (classify(e) == e[classIndex])
			correct++;
	}
	Performance p(correct, ds.getExamples().size() - correct);
	//cout << "# correct: " << correct << endl;
	return p;
}

double NN::classify(const Example &e)
{
	vector <double> y;
	vector <double> output;
	double yVal = 0.0;
	double oVal = 0.0;
	double ySig = 0.0;
	int classSize = W.size();
	
	for (int i = 0; i < classSize; i++)
		output.push_back(0.0);

		for (int k = 0; k < V.size(); k++)
		{
			yVal = 0.0;
			for (int j = 0; j < I.size(); j++)
			{

				yVal = yVal + e[j] * I[j][k];
			}
			if (k != V.size() - 1)
				y.push_back(sig(yVal));
			else
				y.push_back(-1.0);
		} //  END load y loop

		for (int j = 0; j < output.size(); j++)
		{
			for (int k = 0; k < y.size(); k++)
			{
				oVal = oVal + J[k][j] * y[k];
			}
			output[j] = (sig(oVal));
		} // end load output loop
	
		double pos = 0.0;
		double current = 0.0;
		for (int i = 0; i < classSize; i++)
		{
			if (output[i] > current)
			{
				current = output[i];
				pos = i;
			}
		}
		return pos;
}

void NN::sethNodes(int num)
{
	hNodes = num;
}

void NN::setLearningRate(double lr)
{
	learningRate = lr;
}

void NN::setEmin(double num)
{
	Emin = num;
}

int NN::gethNodes()
{
	return hNodes;
}

double NN::getLearningRate()
{
	return learningRate;
}

double NN::getEmin()
{
	return Emin;
}