//********* knapsackGreedy.cpp *********

#include "kpSolverGreedy.hpp"


//TODO: calcul de relaxation continue, c'est le glouton ou un objet peut etre fractionaire
// seule la valeur du sac a dos continu est gardee, sauvegardee dans upperBoundOPT, pas la composition du sac a dos continu
void KpSolverGreedy::solveUpperBound() {

	//TODO
 }

//TODO: resolution de borne inferieure: algorithme glouton "discret", qui donne une borne inferieure a mettre a jour dans costSolution
// et une composition du sac a dos a ecrire dans le vector<bool> solution heritee de la classe mere

void KpSolverGreedy::solveLowerBound() {

	//TODO
 }

void KpSolverGreedy::solve() {
	solveUpperBound();
	solveLowerBound();
}
