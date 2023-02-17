//********* nodeBB.hpp *********

#ifndef NODEBB_HPP
#define NODEBB_HPP


#include <vector>


using namespace std;

class  NodeBB {

private:
    vector<bool> isFixed; // indique les objets dont la variable a ete fixee à 1 avec un true
    vector<bool> isRemoved; // indique les objets dont la variable a ete fixee à 0 avec un true
    vector<bool> primalSolution; // vector retournant une solution entiere par algorithme glouton discret
    int criticalIndex; // indice de la variable fractionnaire, ou de la premiere variable non fixee (à 0 ou 1) qui n'a pas la valeur 1 dans la relaxation continue 
    float fractionalVariable; // valeur fractionnaire de la variable d'indice criticalIndex, peut etre nulle
    double localUpperBound; // borne supérieure locale au noeud: sa relaxation continue en considerant les valeurs fixees par isFixed et isRemoved
    long localLowerBound; // borne inferieure locale: le glouton discret appelé au noeud, donne une borne inf de l'optimum
    bool overCapacitated; // valeur a true si la somme des masses des objets imosés (fixés à 1) dépasse la amsse maximale du sac a dos, on enlevera alors le noeud par la suite

public:

    bool canBeRemoved();

    void primalHeuristic(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values);
    void solveUpperBound(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values);
    void init(int size);

    void clearSolution(){primalSolution.clear();};
    void fixVariable(int id, bool val){if (val) {isFixed[id]=true;} else {isRemoved[id]=true;}};
    double getNodeUpperBound(){return localUpperBound;};
    long getNodePrimalBound(){return localLowerBound;};
    void copyPrimalSolution(vector<bool> *sol) {sol->clear();*sol = primalSolution;}
    int getCriticalIndex() const {return criticalIndex;};
    float getFractionalVariable() const {return fractionalVariable;};

};

#endif
