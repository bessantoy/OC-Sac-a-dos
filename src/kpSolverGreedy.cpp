//********* knapsackGreedy.cpp *********

#include "kpSolverGreedy.hpp"

// TODO: calcul de relaxation continue, c'est le glouton ou un objet peut etre
// fractionaire
//  seule la valeur du sac a dos continu est gardee, sauvegardee dans
//  upperBoundOPT, pas la composition du sac a dos continu
void KpSolverGreedy::solveUpperBound() {
  int totalWeight = 0;
  for (int i = 0; i < nbItems; i++) {
    if (weights[i] + totalWeight <= knapsackBound) {
      totalWeight += weights[i];
      upperBoundOPT += values[i];
    } else {
      upperBoundOPT +=
          (double)(knapsackBound - totalWeight) / weights[i] * values[i];
      break;
    }
  }
}

// TODO: resolution de borne inferieure: algorithme glouton "discret", qui donne
// une borne inferieure a mettre a jour dans costSolution
//  et une composition du sac a dos a ecrire dans le vector<bool> solution
//  heritee de la classe mere

void KpSolverGreedy::solveLowerBound() {
  int totalWeight = 0;
  for (int i = 0; i < nbItems; i++) {
    if (weights[i] + totalWeight <= knapsackBound) {
      totalWeight += weights[i];
      costSolution += values[i];
    }
  }
}

void KpSolverGreedy::solve() {
  solveUpperBound();
  solveLowerBound();
}
