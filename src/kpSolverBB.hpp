//********* kpSolverBB.hpp *********

#ifndef KPSOLVERBB_HPP
#define KPSOLVERBB_HPP

#include "kpSolver.hpp"
#include "nodeBB.hpp"
#include <deque>


enum BranchingStrategies { BestBound,  DFS10, DFS01, BFS, Random, End}; // type enumere, les differents types de parcours d'arbre

class  KpSolverBB : public KpSolver {

private:
    deque<NodeBB*> nodes; // liste des noeuds actifs de l'arbre de B&B
    int nbNodes; // nombre de noeuds visites, compte le nombre d'appeles a la relaxation continue
    int nbMaxNodeBB; // nombre maximal de noeuds a explorer, un critere d arret pour uen resolution approchee
    bool withPrimalHeuristics; // active les heuristiques gloutonnes discretes a chaque noeud
    bool verboseMode; // mode verbux pour deboguer le B&B
    bool withDPinitPrimalHeuristic; // pour initialiser avec une solution obtenue par Kernel Search
    int sizeDPheur; // parametre pour la Kernel Search: nombre maximale d'objets a considere dans l'optimisation locale

    BranchingStrategies branchingStrategy; // un type de parcours d'arbre, grace au type enumere BranchingStrategies


    void printStatus();
    void removeNodes();

    double getUpperBound();

    NodeBB* selectNode();
    NodeBB* selectNodeRandom();

    void insertNode(NodeBB* nod);
    void insertNodes(NodeBB* nod1, NodeBB* nod2);

    void insertNodesBestBound(NodeBB* nod1, NodeBB* nod2);
    void insertNodesBFS(NodeBB* nod1, NodeBB* nod2);
    void insertNodesDFS(NodeBB* nod1, NodeBB* nod2);

    void init();

public:

    void solve();


	void setNbMaxNodeBb(int nbMaxNodeBb) {	nbMaxNodeBB = nbMaxNodeBb;};
	void setVerboseMode(bool vMode){verboseMode = vMode;};
	void setWithPrimalHeuristics(bool withHeuristics) {withPrimalHeuristics = withHeuristics;};
	void setWithDPinitPrimalHeuristic(bool withHeuristic) {withDPinitPrimalHeuristic = withHeuristic;};
	void setSizeDPheur(int siz) {sizeDPheur = siz;};
	void setBranchingStrategy(BranchingStrategies bStrategy) {branchingStrategy = bStrategy;};
	int getNbNodes() const {return nbNodes;};


};



#endif
