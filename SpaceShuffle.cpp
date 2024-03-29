#include <iostream>
#include "Node.h"
#include "SpaceShuffle.h"
using namespace std;

Node* SpaceShuffle::greedyRouteToNode(int targetHash) {
    Node* currentNode = findStartingNode();
    
    while (currentNode) {
        if (currentNode->getHashId() == targetHash) {
            return currentNode; // Destination reached
        }

        Node* nextNode = findClosestSuccessor(currentNode, targetHash);
        if (nextNode->getHashId() == currentNode->getHashId()) {
            // No closer node found, targetHash may not exist
            return nullptr;
        }
        currentNode = nextNode; // Move to the next node closer to the target
    }

    return nullptr; // If the loop exits without finding the node
}

//Node* SpaceShuffle::findStartingNode() {
//    if (!nodes.empty()) {
//        return nodes.front();
//    }
//    return nullptr;
//}

Node* SpaceShuffle::findStartingNode() {
    if (!nodes.empty()) {
        return nodes.front();
    }
    return nullptr;
}

Node* SpaceShuffle::findClosestSuccessor(Node* currentNode, int targetHash) {
    Node* closest = currentNode->getSuccessor();
    int closestDistance = calculateDistance(closest->getHashId(), targetHash);

    for (auto& finger : currentNode->getFingerTable()) {
        int fingerDistance = calculateDistance(finger.node->getHashId(), targetHash);
        if (fingerDistance < closestDistance) {
            closest = finger.node;
            closestDistance = fingerDistance;
        }
    }

    return closest;
}

int SpaceShuffle::calculateDistance(int nodeId, int targetHash) {
    int ringSize = pow(2, bitsForHash);
    if (nodeId <= targetHash) {
        return targetHash - nodeId;
    } else {
        return (ringSize - nodeId) + targetHash;
    }
}
