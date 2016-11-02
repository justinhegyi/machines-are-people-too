#ifndef SPRING2016_MLProject2_Performance_H
#define SPRING2016_MLProject2_Performance_H

#include <iostream>
using namespace std;


class Performance
{
	friend ostream& operator<<(ostream &out, const Performance &p);
private:
	double accuracy;
	double stdDev;
public:
	Performance();
	Performance(int correct, int wrong);
	void setAccuracy(double accuracy);
	double getAccuracy();
	void setStdDev(double stdDev);
	double getStdDev();

};

#endif