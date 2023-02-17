//********* nodeBB.cpp *********

#include "nodeBB.hpp"
//#include <iostream>
//#include <fstream>

bool NodeBB::canBeRemoved() {
	return overCapacitated;
}

void NodeBB::init(int size){
	overCapacitated= false;

	isFixed.resize(size);
	isRemoved.resize(size);

	for(int i=0; i<size;i++){
		isFixed[i] = false;
		isRemoved[i] = false;
	}


    criticalIndex=-1;
    fractionalVariable=0;
    localLowerBound=0;
}

//TODO
void NodeBB::primalHeuristic(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {

	//TODO
 }


//TODO:
void NodeBB::solveUpperBound(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {

 }
