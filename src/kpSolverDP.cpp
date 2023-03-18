//********* kpSolverDP.hpp *********

#include "kpSolverDP.hpp"

#include <omp.h>

void KpSolverDP::setMemoizedVersion(bool memoizedVersion) {
  this->memoizedVersion = memoizedVersion;
}

void KpSolverDP::setVerboseMode(bool verbosemode) {
  this->verboseMode = verbosemode;
}

void KpSolverDP::solve() {
  //	if (verboseMode) cout << "create  DP matrix " << endl;
  createMatrixDP();
  //	if (verboseMode) cout << " DP matrix created " << endl;
  //	if (verboseMode) cout << "fill first column DP matrix " << endl;
  fillFirstColumnDP();
  //	if (verboseMode) cout << "first column DP matrix filled" << endl;

  //	if (verboseMode) cout << "fill  DP matrix : " << endl;

  if (memoizedVersion)
    costSolution = solveMemoized(nbItems - 1, knapsackBound);
  else
    solveIter();

  //	if (verboseMode) cout << " DP matrix filled: " << endl;
  upperBoundOPT = costSolution;
  if (verboseMode) cout << "solution cost by DP: " << costSolution << endl;
  //	if (verboseMode) cout << "print DP matrix :" << endl;
  if (verboseMode) printMatrixDP();
  //	if (verboseMode) cout << "backtrack operations:" << endl;
  backtrack();
  //	if (verboseMode) cout << "backtrack operations achieved:" << endl;

  //	if (verboseMode) cout << "delete DP matrix : " << endl;
  deleteMatrixDP();
  //	if (verboseMode) cout << "DP matrix deleted: " << endl;
}

void KpSolverDP::createMatrixDP() {
  matrixDP = new int*[nbItems];
  for (int i = 0; i < nbItems; i++) {
    matrixDP[i] = new int[knapsackBound + 1];
    for (int j = 0; j <= knapsackBound; j++)
      if (memoizedVersion)
        matrixDP[i][j] = -1;
      else
        matrixDP[i][j] = 0;
  }
}

void KpSolverDP::deleteMatrixDP() {
  for (int i = 0; i < nbItems; i++) {
    delete[] matrixDP[i];
  }
  delete[] matrixDP;
}

void KpSolverDP::fillFirstColumnDP() {
  for (int m = 0; m <= knapsackBound; m++)
    if (m < weights[0])
      matrixDP[0][m] = 0;
    else
      matrixDP[0][m] = values[0];
}

void KpSolverDP::solveIter() {
  // Fill the matrix
  for (int i = 1; i < nbItems; i++) {
    for (int m = 1; m <= knapsackBound; m++) {
      if (m < weights[i])
        matrixDP[i][m] = matrixDP[i - 1][m];
      else
        matrixDP[i][m] = max(matrixDP[i - 1][m],
                             values[i] + matrixDP[i - 1][m - weights[i]]);
    }
  }

  // Find the cost of the solution
  costSolution = matrixDP[nbItems - 1][knapsackBound];
}

int KpSolverDP::solveMemoized(int i, int m) {
  if (matrixDP[i][m] > -1) return matrixDP[i][m];

  if (m < weights[i])
    matrixDP[i][m] = solveMemoized(i - 1, m);
  else
    matrixDP[i][m] = max(solveMemoized(i - 1, m),
                         values[i] + solveMemoized(i - 1, m - weights[i]));

  return matrixDP[i][m];
}

void KpSolverDP::backtrack() {
  solution.resize(nbItems, false);
  int m = knapsackBound;
  for (int i = nbItems - 1; i >= 0; i--) {
    if (i == 0) {
      if (matrixDP[i][m] > 0) solution[i] = true;
    } else {
      if (matrixDP[i][m] != matrixDP[i - 1][m]) {
        solution[i] = true; // if 1, then item i is in the solution
        m -= weights[i];
      }
    }
  }
}

void KpSolverDP::printMatrixDP() {
  cout << "print DP matrix : " << endl;

  for (int i = 0; i < nbItems; i++) {
    for (int j = 0; j <= knapsackBound; j++) cout << matrixDP[i][j] << " ";
    cout << endl;
  }
}
