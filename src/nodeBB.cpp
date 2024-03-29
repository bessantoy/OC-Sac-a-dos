//********* nodeBB.cpp *********

#include "nodeBB.hpp"

#include <algorithm>
#include <iostream>
// #include <fstream>

bool NodeBB::canBeRemoved() { return overCapacitated; }

void NodeBB::init(int size) {
  overCapacitated = false;

  isFixed.resize(size);
  isRemoved.resize(size);

  for (int i = 0; i < size; i++) {
    isFixed[i] = false;
    isRemoved[i] = false;
  }

  criticalIndex = -1;
  fractionalVariable = 0;
  localLowerBound = 0;
}

// TODO
void NodeBB::primalHeuristic(int kpBound, int nbItems, vector<int>& weights,
                             vector<int>& values) {
  primalSolution.resize(nbItems, false);
  localLowerBound = 0;
  int totalWeight = 0;

  for (int i = 0; i < nbItems; ++i) {
    if (isFixed[i]) {
      if (weights[i] + totalWeight <= kpBound) {
        localLowerBound += values[i];
        totalWeight += weights[i];
        primalSolution[i] = true;
      } else {
        overCapacitated = true;
        break;
      }
    }
    if (!isFixed[i] && !isRemoved[i]) {
      if (weights[i] + totalWeight <= kpBound) {
        totalWeight += weights[i];
        localLowerBound += values[i];
        primalSolution[i] = true;
      }
    }
  }
}

void NodeBB::solveUpperBound(int kpBound, int nbItems, vector<int>& weights,
                             vector<int>& values) {
  localUpperBound = 0;
  int totalWeight = 0;
  fractionalVariable = 0;
  overCapacitated = false;

  for (int i = 0; i < nbItems; ++i) {
    if (isFixed[i]) {
      if (totalWeight + weights[i] > kpBound) {
        overCapacitated = true;
        break;
      }
      localUpperBound += values[i];
      totalWeight += weights[i];
    }
  }
  for (int i = 0; i < nbItems; ++i) {
    if (!isFixed[i] && !isRemoved[i]) {
      if (weights[i] + totalWeight <= kpBound) {
        totalWeight += weights[i];
        localUpperBound += values[i];
      } else {
        criticalIndex = i;
        fractionalVariable =
            (double)(kpBound - totalWeight) / weights[i] * values[i];
        localUpperBound += fractionalVariable;
        break;
      }
    }
  }
}
