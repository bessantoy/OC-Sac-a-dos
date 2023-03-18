//********* knapsackheurDP.cpp *********

#include "kpSolverHeurDP.hpp"


void KpSolverHeurDP::solveUpperBound() {
  int totalWeight = 0;
  lastIndex = -1; // initialisation de lastIndex
  for (int i = 0; i < nbItems; i++) {
    if (weights[i] + totalWeight <= knapsackBound) {
      totalWeight += weights[i];
      upperBoundOPT += values[i];
    } else {
		if(lastIndex == -1){
			lastIndex = i; // mise à jour de lastIndex
		}
      upperBoundOPT +=
          (double)(knapsackBound - totalWeight) / weights[i] * values[i];
      break;
    }
  }
}

void KpSolverHeurDP::solve() {
  // Calcul de la borne supérieure et de l'indice critique
  solveUpperBound();

  

  // Détermination des indices à réoptimiser
  int nbSelectedReopt = 0;
  int nbUnselectedReopt = 0;
  for (int i = 0; i <= lastIndex; i++) {
    if (solution[i]) {
      nbSelectedReopt++;
    } else {
      nbUnselectedReopt++;
    }
  }

  // Définition de l'ensemble des indices à réoptimiser
  int startIndex = lastIndex - nbSelectedReopt + 1;
  int endIndex = lastIndex + nbUnselectedReopt;
  int subKpSize = endIndex - startIndex + 1;
  vector<int> subWeights(subKpSize);
  vector<int> subValues(subKpSize);
  for (int i = 0; i < subKpSize; i++) {
    subWeights[i] = weights[startIndex + i];
    subValues[i] = values[startIndex + i];
  }

  // Détermination de la masse actuelle du sac à dos
  int totalWeight = 0;
  for (int i = 0; i <= lastIndex; i++) {
    if (solution[i]) {
      totalWeight += weights[i];
    }
  }

  // Calcul de la borne inférieure en considérant les objets déjà sélectionnés
	int LowerBound = 0;
	for (int i = 0; i <= lastIndex; i++) {
		if (solution[i]) {
			LowerBound += values[i];
		}
	}

	


  

  // Réoptimisation locale des objets à réoptimiser
	
}

void KpSolverHeurDP::setNeighborhood(int nbSelectedOpt, int nbUnselectedOpt) {
	nbUnselectedReopt = nbUnselectedOpt;
	nbSelectedReopt = nbSelectedOpt;
}
