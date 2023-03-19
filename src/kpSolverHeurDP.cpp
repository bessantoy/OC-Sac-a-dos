//********* knapsackheurDP.cpp *********

#include "kpSolverHeurDP.hpp"
#include "kpSolverDP.hpp"

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
  
  
  // Calcul des bornes inférieure et supérieure initialisation de la taille du sac à dos à reoptimiser 
  int lowerBoundReopt = lastIndex - nbSelectedReopt;
  int upperBoundReopt = lastIndex + nbUnselectedReopt;
  int nbItemsReopt = upperBoundReopt - lowerBoundReopt;
  int knapsackBoundReopt = knapsackBound;
  
  //On selectionne dans la solution finale les objets inferieurs à lowerboundReopt 

  solution.resize(nbItems);


  for(int i = 0; i < lowerBoundReopt; i++){
    knapsackBoundReopt -= weights[i];
    solution[i] = true;
    costSolution += values[i];
  }


/*std::cout<<"knapBoundReopt"<<knapsackBoundReopt<<std::endl;
std::cout<<"knapBound"<<knapsackBound<<std::endl;
std::cout<<"nbItems"<<nbItems<<std::endl;
std::cout <<"nbItemsReopt : " << nbItemsReopt << std::endl;*/

  
 
  //On initialise la matrice
  int** matrixDP = new int*[nbItemsReopt];
  for (int i = 0; i < nbItemsReopt; i++) {
    matrixDP[i] = new int[knapsackBoundReopt + 1];
    for (int j = 0; j <= knapsackBoundReopt; j++){
       matrixDP[i][j] = 0;

    }
  }
  //on remplit la premiere colonne de la matrice
  for (int m = 0; m <= knapsackBoundReopt; m++)
    if (m < weights[0])
      matrixDP[0][m] = 0;
    else
      matrixDP[0][m] = values[0];

  
  
  // solve_iter
  
  for (int i = 1; i < nbItemsReopt; i++) {
    for (int m = 0; m <= knapsackBoundReopt; m++) {
      if (m < weights[i])
        matrixDP[i][m] = matrixDP[i - 1][m];
      else
        matrixDP[i][m] = std::max(matrixDP[i - 1][m],
                                  matrixDP[i - 1][m - weights[i]] + values[i]);
    }
  }

std::cout << "Matrice DP: " << std::endl;
  for (int i = 0; i < nbItemsReopt; i++) {
    for (int j = 0; j <= knapsackBoundReopt; j++) {
      std::cout << matrixDP[i][j] << " ";
    }
    std::cout << std::endl;
  }
  

  // Find the cost of the sub_solution
  costSolution += matrixDP[nbItemsReopt - 1][knapsackBoundReopt];
  //std::cout << "Cost of the sub_solution: " << costSolution << std::endl;

 
  	vector<bool> solutionReopt; // composition du sous sac a dos de meilleur cout trouvé


  solutionReopt.resize(nbItemsReopt);
  int m = knapsackBoundReopt;
  for (int i = nbItemsReopt - 1; i >= 0; i--) {
    if (i == 0) {
      if (matrixDP[i][m] > 0) solutionReopt[i] = true;
    } else {
      if (matrixDP[i][m] != matrixDP[i - 1][m]) {
        solutionReopt[i] = true; // if 1, then item i is in the solution
        m -= weights[i];
      }
    }
  }
  std::cout << "Solution reoptimisee: " <<  std::endl;
  for (int i = 0; i < nbItemsReopt; i++) {
    std::cout << solutionReopt[i] << " ";
  }

  // for(size_t i = 0; i< solutionReopt.size(); i++){
  //   solution[i+lowerBoundReopt] = solutionReopt[i];
  //   costSolution += values[i+lowerBoundReopt];
  // }

  

}
  



void KpSolverHeurDP::setNeighborhood(int nbSelectedOpt, int nbUnselectedOpt) {
	nbUnselectedReopt = nbUnselectedOpt;
	nbSelectedReopt = nbSelectedOpt;
}
