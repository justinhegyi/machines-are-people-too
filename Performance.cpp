#include "Performance.h"

Performance::Performance()
{
	setAccuracy(-1);
	setStdDev(-1);
}

Performance::Performance(int correct, int wrong)
{
	int total = correct + wrong;
	setAccuracy(correct *1.0 / total);
}

void Performance::setAccuracy(double accuracy)
{
	this->accuracy = accuracy;
}

double Performance::getAccuracy()
{
	return accuracy;
}

void Performance::setStdDev(double stdDev)
{
	this->stdDev = stdDev;
}

double Performance::getStdDev()
{
	return stdDev;
}

ostream& operator<<(ostream &out, const Performance &p)
{
	if (p.stdDev == -1)
		out << p.accuracy << endl;
	else
		out << p.accuracy << " +- " << p.stdDev << endl;
	return out; 
}