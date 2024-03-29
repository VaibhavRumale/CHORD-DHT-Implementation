#ifndef NODE_H
#define NODE_H
#include <stdint.h>
#include "FingerTable.h"
#include <vector>
#include <map>
#include <set>
using namespace std;

bool keyInNodeRangeInclusive(int key, int startNode, int endNode);

bool keyInNodeRangeExclusive(int key, int startNode, int endNode);

bool keyInNodeRangeStartInclusive(int key, int startNode, int endNode);

bool keyInNodeRangeEndInclusive(int key, int startNode, int endNode);


class Node {
public:

	
    
    Node* findSuccessor(int key, vector<Node*>& path);
    Node* findPredecessor(int key, vector<Node*>& path);
    Node* closestPrecedingFinger(int key);
    Node(int nodeId);
    Node(int nodeId, int bitsForHash);
    void printLocalKeys();
    void printNodeFingerTable();
    void print_path(vector<Node*>& path);
	void join(Node* node);
    void updateOwnFingerTable(Node* node);
    void updateOthersFingerTableJoinOP();
    void updateFingerTableJoinOP(Node* node, int index);
    void migrateKeysOnJoin();
    void leave();
    void updateOthersFingerTableLeaveOP();
    void updateFingerTableLeaveOP(Node* node);
    void migrateKeysOnLeave();
    int find(int key);
    void insert(int key, int value);
    void remove(int key);

    int getId();
    void setId(int key);

    int getHashId();
    void setHashId(int key);
    
    Node* getPredecessor();
    void setPredecessor(Node* node);
    Node* getSuccessor();
    
    FingerTable getFingerTable();
    void setFingerTable(FingerTable fingerTable );
    std::map<int, int> getLocalKeys();
    void setLocalKeys(std::map<int, int> localKeys);

public:
    int M;
    FingerTable fingerTable_;
    std::map<int, int> localKeys_;

private:
	int id_;
    int hash_id;
    Node* predecessor;
};

#endif
