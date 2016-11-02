//
// Justin Hegyi
// jmh361@georgetown.edu
// Platform: Windows
// Language/Environment: c++11
//
// In accordance with the class policies and Georgetown's Honor Code,
// I certify that, with the exceptions of the class resources and those
// items noted below, I have neither given nor received any assistance
// on this project.
//

#include<iostream>
#include "Dataset.h"
#include "NominalAttribute.h"
#include "NumericAttribute.h"
#include <fstream>
#include "KNN.h"
#include "NB.h"
#include "Evaluator.h"
#include "ID3.h"

using namespace std;

int main(int argc, const char * argv[])
{
	try 
	{

		std::ifstream file;
		string filename = "monks3.te.mff";
		DataSet d1;
		d1.load(filename);
		
		ID3 rTree;
		rTree.train(d1);
		rTree.setTrain(d1);
		Evaluator eval(10);
		Performance p1;
		p1 = eval.evaluate(rTree);
		cout << p1;
		
		RDF trees(5,13);
		trees.setTrain(d1);
		Evaluator eval1(10);
		Performance p;
		p = eval1.evaluate(trees);
		cout << p << endl;


		//
		std::ifstream file1;
		string filename1 = "monks3.tr.mff";
		DataSet d2;
		d2.load(filename1);

		ID3 rTree1;
		rTree1.train(d2);
		rTree1.setTrain(d2);
		Evaluator eval2(10);
		Performance p2;
		p2 = eval1.evaluate(rTree1);
		cout << p2;

		RDF trees1(5,13);
		trees1.setTrain(d2);
		Evaluator eval3(10);
		Performance p3;
		p3 = eval3.evaluate(trees1);
		cout << p3 << endl;

		
		std::ifstream file2;
		string filename2 = "breast-cancer-wisconsin.mff";
		DataSet d3;
		d3.load(filename2);

		ID3 rTree2;
		rTree2.train(d3);
		rTree2.setTrain(d3);
		Evaluator eval4(10);
		Performance p4;
		p4 = eval4.evaluate(rTree2);
		cout << p4;

		RDF trees2(5,13);
		trees2.setTrain(d3);
		Evaluator eval5(10);
		Performance p5;
		p5 = eval5.evaluate(trees2);
		cout << p5 << endl;

	}
	catch (logic_error le) 
	{
		cout << le.what() << endl;
	}
	catch (std::bad_alloc ba)
	{
		ba.what();
	}
	catch (string str)
	{
		cout << str << endl;
	}
	catch (std::out_of_range &oor)
	{
		cout << oor.what() << endl;
	}
	std::cin.get();
	return 0;
}
