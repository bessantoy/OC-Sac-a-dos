//********* kpSolver.hpp *********

#ifndef KPSOLVERDP_HPP
#define KPSOLVERDP_HPP

#include "kpSolver.hpp"

class  KpSolverDP : public KpSolver {

private:

    //matrice de programmation dynamique
    int** matrixDP;

    //option pour appeler la memoisation
    bool memoizedVersion;
    //option pour appeler le mode verbeux du solveur, et afficher la matrice de programmation dynamique
    bool verboseMode;

    //TODO: construction itérative de la matrice de prog dynamique
    void solveIter();

    // construction itérative de la matrice de prog dynamique
    int solveMemoized(int i , int m);

    //TODO: backtrack dans la matrice de prog dynamique pour récupérer une composition optimale du sac a dos, a ecrire dans le vector<bool> solution heritee de la classe mere
    void backtrack();

    // construction et destruction de la matrice de prog dynamique
    void createMatrixDP();
    void deleteMatrixDP();

    //affichage de la matrice de prog dynamique
    void printMatrixDP();

    // construction de la première ligne de la matrice de prog dynamique (relative au premier objet)
    void fillFirstColumnDP();

public:

    void solve();

    void setMemoizedVersion(bool memoizedVersion);
    void setVerboseMode(bool verbosemode);

};

#endif

