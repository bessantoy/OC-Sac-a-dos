//********* kpSolver.hpp *********

#ifndef KPSOLVER_HPP
#define KPSOLVER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


// Tous nos solveurs vont hériter de KpSolver, qui contient des fonctions générales d'import et d'affichage
// tous les solveurs modifient les bornes supérieures et inférieures de la classe mère, et remplissent dans le vecteur de booléens l'affectation du sac a dos
// qui donne la meilleure valeur (borne inférieure car pb de maximisation)

// Remarque: pas de constructeur et de destructeurs implémentés, les cosntructeur/destructeurs par défaut sont alors utilisés 
class KpSolver {

private:
	//trie le sac a dos selon el rapport cout/masse de l'algorithme glouton
	// fonction appelee dans en fin d'import d'instance, l'import trie deja les objets
	void sortKnapsack();


protected: // les classes filles pourront accéder à ces champs directement, pas besoin de getter/setter

	// Données définissant l'instance de  sac a dos 
	int nbItems; // nombre d'objets.
	vector<int> weights; //masses de chaque objet 
	vector<int> values; // valeur de chaque objet
	int knapsackBound;     // masse maximale du sac a dos

	// Elements de solutions, a modifier par la resolution dans chaque fonction solve() des classes filles
	vector<bool> solution; // composition du sac a dos de meilleur cout trouvé
	long costSolution;     // cout de la solution definie dans el vector precedent, borne inferieure de l'optimum
	double upperBoundOPT;  // borne superieure de l'optimum, par calcul de relaxation continue par exemple

public:

	void importInstance(const string& fileName); // importe une instance definie dans un fichier
	void printKnapsackInstance();
	void printKnapsackSolution(bool printSol);

	int getUpperBound(){return upperBoundOPT;};
	int getSolutionCost(){return costSolution;};
	bool isSelected(int item){return solution[item];};

	void extractSubInstance(int idMin, int idMax);

	void clearInstance();

	int getNbItems() const {return nbItems;	};
};

#endif

