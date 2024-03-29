#ifndef SPACESHUFFLE_H
#define SPACESHUFFLE_H

#include "Node.h"
#include <cmath>
#include <vector>

class SpaceShuffle {
public:
    SpaceShuffle(int bitsForHash);
    void insertNode(int nodeId, int referenceNodeId);
    void removeNode(int nodeId);
    void insertKeyValue(int key, int value);
    void deleteKey(int key);
    int findKeyValue(int key);
    void displayAllLocalKeys();
    void displayAllFingerTables();
    void displayKeyLookupResults(int nodeId);

private:
    std::vector<Node*> nodes;
    Node* findStartingNode();
    Node* greedyRouteToNode(int targetHash);
    Node* findClosestSuccessor(Node* currentNode, int targetHash);
    int calculateDistance(int nodeId, int targetHash);
    std::vector<Node*> nodesInChord;
    int bitsForHash;
    std::vector<int> keysInChord;
};

#endif // SPACESHUFFLE_H

