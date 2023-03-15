//********* nodeBB.cpp *********

#include "nodeBB.hpp"

#include <algorithm>
// #include <iostream>
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

  auto ratios = std::vector<std::pair<int, double>>();
  for (int i = 0; i < nbItems; ++i) {
    if (!isFixed[i] && !isRemoved[i]) {
      ratios.push_back(i, (double)values[i] / weights[i]);
    } else {
      if (isFixed[i]) {
        localLowerBound += values[i];
        totalWeight += weights[i];
        primalSolution[i] = true;
      }
    }
  }
  std::sort(ratios.begin(), ratios.end(),
            [](auto& a, auto& b) { return a.second > b.second; });

  for (auto item : ratios) {
    int i = item.first;
    if (weights[i] + totalWeight <= kpBound) {
      totalWeight += weights[i];
      localUpperBound += values[i];
      primalSolution[i] = true;
    } else {
      break;
    }
  }
}

void NodeBB::solveUpperBound(int kpBound, int nbItems, vector<int>& weights,
                             vector<int>& values) {
  localUpperBound = 0;
  int totalWeight = 0;

  auto ratios = std::vector<std::pair<int, double>>();
  for (int i = 0; i < nbItems; ++i) {
    if (!isFixed[i] && !isRemoved[i]) {
      ratios.push_back(i, (double)values[i] / weights[i]);
    } else {
      if (isFixed[i]) {
        localUpperBound += values[i];
        totalWeight += weights[i];
      }
    }
  }
  std::sort(ratios.begin(), ratios.end(),
            [](auto& a, auto& b) { return a.second > b.second; });

  for (auto item : ratios) {
    int i = item.first;
    if (weights[i] + totalWeight <= kpBound) {
      totalWeight += weights[i];
      localUpperBound += values[i];
    } else {
      overCapacitated = true;
      criticalIndex = i;
      fractionalVariable =
          (double)(kpBound - totalWeight) / weights[i] * values[i];
      break;
    }
  }
}
