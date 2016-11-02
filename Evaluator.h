#ifndef SPRING2016_MLProject2_Evaluator_H
#define SPRING2016_MLProject2_Evaluator_H

#include "KNN.h"
#include "NB.h"
#include "ID3.h"
//#include "NN.h"
#include "RDF.h"

class Evaluator
{
private:
	int holdOut;
public:
	Evaluator();
	Evaluator(int holdOut);
	Performance evaluate(const KNN &classifier);
	Performance evaluate(const NB &classifier);
	Performance evaluate(const ID3 &classifier);
	//Performance evaluate(const NN &classifier);
	Performance evaluate(const RDF &classifier);
};

#endif
