//********* kpSolverGreedy.hpp *********

#ifndef KPSOLVERGREEDY_HPP
#define KPSOLVERGREEDY_HPP

#include "kpSolver.hpp"

class  KpSolverGreedy : public KpSolver {


public:
    //TODO: resolution de borne inferieure: algorithme glouton "discret", qui donne une borne inferieure a mettre a jour dans costSolution
    // et une composition du sac a dos a ecrire dans le vector<bool> solution heritee de la classe mere
    void solveLowerBound(); 

    //TODO: calcul de relaxation continue, c'est le glouton ou un objet peut etre fractionaire
    // seule la valeur du sac a dos continu est gardee, sauvegardee dans upperBoundOPT, pas la composition du sac a dos continu
    void solveUpperBound();

    //solve() appelle les deux calculs de bornes precedents, encadre l'optimum avec une complexité en temps O(n log n)
    void solve();


};


#endif
