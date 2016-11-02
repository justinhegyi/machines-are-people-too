#ifndef SPRING2016MLPROJECT_ID3NODE_H
#define SPRING2016MLPROJECT_ID3NODE_H
#include <vector>

using namespace std;

class ID3Node {
private:
	unsigned label;
	unsigned attribute;

public:
	vector<ID3Node *> children;
	ID3Node();
	~ID3Node();
	void setLabel(const unsigned &label);
	unsigned getLabel();
	int size();
	void setAttribute(const unsigned &attribute);
	unsigned getAttribute();
};

#endif // !SPRING2016MLPROJECT_ID3NODE_H
