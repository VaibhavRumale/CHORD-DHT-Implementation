#include <iostream>
#include <iomanip>
#include "FingerTable.h"
#include "Node.h"
#include <math.h>


FingerTable::FingerTable(){
	fingerTable_.resize(M + 1);
}

FingerTable::FingerTable(Node* node) : FingerTable(node, 8) {}

FingerTable::FingerTable(Node* node, int bitsForHash) : M(bitsForHash) {
    fingerTable_.resize(M + 1);
    if (!node) return;

    for(int i = 1; i <= M; i++){
        int pow2_i_1 = int(pow(2, i - 1));
        int pow2_i = int(pow(2, i));
        int interval_start = (node->getHashId() + pow2_i_1) % int(pow(2, M));
        int interval_end = (node->getHashId() + pow2_i) % int(pow(2, M));

        setIntervalStart(i, interval_start);
        setNextNode(i, node);
        setIntervalEnd(i, interval_end);
    }
}

void FingerTable::setFinger(int index, Finger finger){
	fingerTable_[index] = finger;
}
Finger FingerTable::getFinger(int index) {
	return fingerTable_[index];
}

void FingerTable::setIntervalStart(int index, int interval_start){
	fingerTable_[index].interval_start = interval_start;
}
int FingerTable::getIntervalStart(int index) {
	return fingerTable_[index].interval_start;
}

void FingerTable::setIntervalEnd(int index, int interval_end){
	fingerTable_[index].interval_end = interval_end;
}
int FingerTable::getIntervalEnd(int index) {
	return fingerTable_[index].interval_end;
}

void FingerTable::setNextNode(int index, Node* next_node){
	fingerTable_[index].next_node = next_node;
}
Node* FingerTable::getNextNode(int index) {
	return fingerTable_[index].next_node;
}


void FingerTable::prettyPrint() {
    cout << std::setfill('-') << std::setw(50) << "\n";  // Top border
    cout << std::setfill(' ');  // Reset fill character for other output

    for (int i = 1; i <= M; i++) {
        cout << "| k = " << std::setw(2) << i << " |";
        cout << std::setw(8) <<"{"<< getIntervalStart(i) << " , ";
        cout << getIntervalEnd(i) << "} |";
        cout << " succ. = " << std::setw(2) << getNextNode(i)->getId() << " |\n";
    }

    cout << std::setfill('-') << std::setw(50) << "-" << endl;  // Bottom border
    cout << std::setfill(' ');  // Reset fill character for other output
}
