#ifndef SPRING2016MLPROJECT_NN_H
#define SPRING2016MLPROJECT_NN_H

#include "Classifier.h"
#include <time.h>

class NN : public Classifier
{
private:
	vector <double >  V;
	vector < vector < double> > I;
	vector<double> W;
	vector < vector <double > > J;
	int hNodes;
	double learningRate;
	double Emin;


public:
	NN();
	NN::NN(int hNodes, double learningRate, double Emin);
	void train(DataSet &ds);
	double classify(const Example &e);
	Performance classify(const DataSet &ds);
	void sethNodes(int num);
	void setLearningRate(double lr);
	void setEmin(double num);
	int gethNodes();
	double getLearningRate();
	double getEmin();

};


#endif