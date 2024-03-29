
#include "Node.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdint.h>
#include <map>
#include <set>
#include <vector>
using namespace std;



struct NodeCmp {
    bool operator()(Node* node1, Node* node2) const {
        return node1->getId() < node2->getId();
    }
};

class ChordDHT{
public:
    
    ChordDHT();
    ChordDHT(int bitsForHash);

    void insertNode(int nodeId, int refNodeId);

    void removeNode(int nodeId);

    void insertKeyValue(int key, int value);

    void deleteKey(int key);

    int findKeyValue(int key);

    void displayAllLocalKeys();

    void displayAllFingerTables();

    void displayKeyLookupResults(int nodeId);

    set<Node*, NodeCmp> nodesInChord;
    int bitsForHash;

private:
    Node* getNodeById(int nodeId);

    
    set<int> keysInChord;
};

ChordDHT::ChordDHT(){
    bitsForHash= 8;

}

ChordDHT::ChordDHT(int bitsForHash){
    this->bitsForHash= bitsForHash;
}


Node* ChordDHT::getNodeById(int nodeId) {
    for (Node* node : nodesInChord) {
        if (node->getId() == nodeId) {
            return node;
        }
    }
    return nullptr;
}
void ChordDHT::insertNode(int nodeId, int refNodeId){
    Node* newNode = getNodeById(nodeId);
    if(newNode != nullptr){
        cout << "Error: A node with ID " << nodeId << " already exists. No action taken." << endl;
        return;
    }

    newNode = new Node(nodeId, bitsForHash);
    if(!nodesInChord.empty()) {
        Node* referenceNode = getNodeById(refNodeId);
        if(referenceNode == nullptr){
            cout << "Error: Reference node ID " << refNodeId << " not found. Cannot add new node." << endl;
            return;
        }
        newNode->join(referenceNode);
    } else {
        newNode->join(nullptr);
    }
    
    nodesInChord.insert(newNode);
    cout << "Success: Node " << nodeId << " added to the Chord network." << endl;
}

void ChordDHT::removeNode(int nodeId){
    Node* targetNode = getNodeById(nodeId);
    if(targetNode == nullptr) {
        cout << "Error: Node ID " << nodeId << " not found in the Chord." << endl;
        return;
    }

    targetNode->leave();
    nodesInChord.erase(targetNode);
    cout << "Success: Node " << nodeId << " removed from the Chord network." << endl;
}

void ChordDHT::insertKeyValue(int key, int value){
    if(keysInChord.find(key) != keysInChord.end()) {
        cout << "Alert: Key " << key << " already present. No new key added." << endl;
        return;
    }
    
    if(nodesInChord.empty()) {
        cout << "Error: The Chord is empty. Add nodes before inserting keys." << endl;
        return;
    }

    keysInChord.insert(key);
    Node* startingNode = *(nodesInChord.begin());
    startingNode->insert(key, value);
    cout << "Success: Key " << key << " added to the Chord." << endl;
}

void ChordDHT::deleteKey(int key){
    if(keysInChord.find(key) == keysInChord.end()) {
        cout << "Error: Key " << key << " not found in the Chord." << endl;
        return;
    }
    
    if(nodesInChord.empty()) {
        cout << "Error: The Chord is empty. No keys to remove." << endl;
        return;
    }

    keysInChord.erase(key);
    Node* startingNode = *(nodesInChord.begin());
    startingNode->remove(key);
    cout << "Success: Key " << key << " removed from the Chord." << endl;
}

int ChordDHT::findKeyValue(int key){
    if(keysInChord.find(key) == keysInChord.end()) {
        cout << "Error: Key " << key << " not found in the Chord." << endl;
        return -1;
    }
    
    if(nodesInChord.empty()) {
        cout << "Error: The Chord is empty. Cannot perform lookup." << endl;
        return -1;
    }

    Node* startingNode = *(nodesInChord.begin());
    int value = startingNode->find(key);
    cout << "Lookup Result: Key " << key << " has value " << value << "." << endl;
    return value;
}

void ChordDHT::displayAllLocalKeys(){
    for (Node* currentNode : nodesInChord) {
        currentNode->printLocalKeys();
    }
}

void ChordDHT::displayAllFingerTables(){
    if(nodesInChord.empty()) {
        cout << "The Chord does not contain any nodes." << endl;
        return;
    }

    for (Node* currentNode : nodesInChord) {
        currentNode->printNodeFingerTable();
    }
}

void ChordDHT::displayKeyLookupResults(int nodeId){
    Node* targetNode = getNodeById(nodeId);
    if(targetNode == nullptr) {
        cout << "[Error] No node found with the ID: " << nodeId << ".\n";
        return;
    }

    cout << "\n[Key Lookup Results for Node " << nodeId << "]\n";
    cout << string(40, '=') << endl;

    if (keysInChord.empty()) {
        cout << "No keys present in the Chord to look up.\n";
    } else {
        for (int key : keysInChord) {
            int value = targetNode->find(key);
            cout << "Key: " << key << " | Value: " << value << endl;
        }
    }

    cout << string(40, '=') << "\n\n";
}

int getInputNumber() {
    int input;
    while (true) {
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error. Please enter a valid integer.\n";
        } else {
            return input;
        }
    }
}

int main() {
    int hashSpaceSize;
    bool terminateProgram = false;

   cout << "\n";
   cout << "             CHORD DISTRIBUTED HASH TABLE            \n";
   cout << "=====================================================\n";
   cout << "   Enter the size of the hash space for the network   \n";
   cout << "   (Example: 8 for a hash space size of 8):           \n";
   cout << "=====================================================\n";
   cout << "\n>>> ";


    while(true) {
        hashSpaceSize = getInputNumber();

        if (hashSpaceSize > 0) {
            break; // Valid size entered, exit the loop
        } else {
           cout << "The size of the hash table must be greater than 0. Please enter a valid size: ";
        }
    }

    ChordDHT chordNetwork(hashSpaceSize);
 

    int userChoice;
    
    while (!terminateProgram) {
        cout << "=====================================================\n";
        cout << "=====================================================\n";
        cout << "\nChord Network Operations:\n";
        cout << "\n1. Add Node\n";
        cout << "2. Remove Node\n";
        cout << "3. Insert Key/Value Pair\n";
        cout << "4. Delete Key\n";
        cout << "5. Search Key/Value Pair\n";
        cout << "6. Show Stored Keys\n";
        cout << "7. Show Finger Tables\n";
        cout << "8. Node Key Lookup\n";
        cout << "0. Exit Simulator\n";
        cout << "\n\nSelect an option:\n \n";
        cout << "=====================================================\n";
        cout << "=====================================================\n";

        cin >> userChoice;
        
        switch(userChoice) {
            case 1: {
                int nodeId, referenceNodeId;
                cout << "Node ID for insertion: ";
                nodeId = getInputNumber();

                if (!chordNetwork.nodesInChord.empty()) {
                    cout << "Reference Node ID: ";
                    referenceNodeId = getInputNumber();
                    chordNetwork.insertNode(nodeId, referenceNodeId);
                } else {
                    chordNetwork.insertNode(nodeId, 0);
                }
                break;
            }
            case 2: {
                int nodeId;
                cout << "Node ID for removal: ";
                nodeId = getInputNumber();

                chordNetwork.removeNode(nodeId);
                break;
            }
            case 3: {
                int key;
                int value;
                int option;

                cout << "[Key Insertion]\nEnter the key to add: ";
                key = getInputNumber();

                cout << "Do you want to assign a value to this key?\n";
                cout << "1. Yes, assign a value\n";
                cout << "2. No, use a default value\n";
                cout << "Select an option: ";
                option = getInputNumber();

                if (option == 1) {
                    cout << "Enter the value for key " << key << ": ";
                    value = getInputNumber();
                    chordNetwork.insertKeyValue(key, value);
                    cout << "Key " << key << " with value " << value << " added.\n";
                } else {
                    chordNetwork.insertKeyValue(key, -1);
                    cout << "Key " << key << " added with a default value.\n";
                }
                break;
            }

            case 4: { // Remove Key
                                int key;
                
                                cout << "Enter key to be removed from the chord:" << endl;
                                key = getInputNumber();
                
                                chordNetwork.deleteKey(key);
                                break;
                            }
            case 5: { // Find Key/Value
                                int key;
                
                                cout << "Enter key you want to search for in the chord:" << endl;
                                key = getInputNumber();
                
                                chordNetwork.findKeyValue(key);
                                break;
                            }
            case 6: // Display Stored Keys
                                chordNetwork.displayAllLocalKeys();
                                break;
            case 7: // Display Finger Tables
                                chordNetwork.displayAllFingerTables();
                                break;
            case 8: { // Key Lookup for Node
                                int vertexIdentifier;
                
                                cout << "Enter vertex id of the vertex to print all key lookup for:" << endl;
                                vertexIdentifier = getInputNumber();
                
                                chordNetwork.displayKeyLookupResults(vertexIdentifier);
                                break;
                            }
            case 0:
                terminateProgram = true;
                break;
            default:
                cout << "Please choose a valid option.\n";
        }
    }
}
