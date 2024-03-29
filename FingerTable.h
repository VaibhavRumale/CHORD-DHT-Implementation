#ifndef FINGERTABLE_H
#define FINGERTABLE_H
#include <vector>
#include <utility>
#include <stdint.h>
#include <map>
#include <set>

using namespace std;

class Node;

class Finger{
	public:
		int interval_start;
		int interval_end;
		Node* next_node;
};

class FingerTable{
public:

	FingerTable();
	FingerTable(Node* node);
	FingerTable(Node* node, int bitsForHash);

	void setFinger(int index, Finger finger);
	Finger getFinger(int index);

	void setIntervalStart(int index, int interval_start);
	int getIntervalStart(int index);

	void setIntervalEnd(int index, int interval_end);
	int getIntervalEnd(int index);

	void setNextNode(int index, Node* next_node);
	Node* getNextNode(int index);
	
	void prettyPrint();

public:
    int M;
	vector<Finger> fingerTable_;
	
};

#endif
