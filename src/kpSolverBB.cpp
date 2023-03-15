//********* kpSolverBB.cpp *********

#include "kpSolverBB.hpp"

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "kpSolverDP.hpp"

double KpSolverBB::getUpperBound() {
  upperBoundOPT = costSolution;
  for (std::deque<NodeBB*>::iterator it = nodes.begin(); it != nodes.end();
       ++it)
    upperBoundOPT = max(upperBoundOPT, (*it)->getNodeUpperBound());
  return upperBoundOPT;
}

void KpSolverBB::printStatus() {
  getUpperBound();
  cout << "nbNodes: " << nbNodes;
  cout << " remaining Nodes: " << nodes.size();
  cout << " LB: " << costSolution;
  cout << " UB: " << (long)floor(upperBoundOPT);
  cout << " gap : "
       << (floor(upperBoundOPT) - (double)costSolution) /
              ((double)costSolution) * 100
       << "%" << endl;
}

// TODO: rajouter heuristique de programmation dynamique
void KpSolverBB::init() {
  nbNodes = 0;
  nodes.clear();
  NodeBB* node0 = new NodeBB();
  node0->init(nbItems);
  node0->solveUpperBound(knapsackBound, nbItems, weights, values);
  if (withPrimalHeuristics) {
    node0->primalHeuristic(knapsackBound, nbItems, weights, values);
    costSolution = node0->getNodePrimalBound();
    node0->copyPrimalSolution(&solution);
  } else {
    costSolution = 0;
    solution.resize(nbItems);
    for (int i = 0; i < nbItems; i++) solution[i] = false;
  }

  nodes.push_back(node0);

  if (!withDPinitPrimalHeuristic) return;

  // TODO: rajouter heuristique de programmation dynamique
}

NodeBB* KpSolverBB::selectNodeRandom() {
  srand(time(NULL));

  int n = nodes.size();
  int id = rand() % n;

  swap(nodes[0], nodes[id]);

  NodeBB* node = nodes.front();
  nodes.pop_front();
  return node;
}

NodeBB* KpSolverBB::selectNode() {
  if (branchingStrategy == Random) return selectNodeRandom();

  if (branchingStrategy == BestBound) {
    std::sort(nodes.begin(), nodes.end(), [](NodeBB* i, NodeBB* j) {
      return i->getNodeUpperBound() < j->getNodeUpperBound();
    });
  }

  if (branchingStrategy == BFS) {
    NodeBB* node = nodes.front();
    nodes.pop_front();
    return node;
  }

  NodeBB* nod = nodes.back();
  nodes.pop_back();
  return nod;
}

void KpSolverBB::insertNode(NodeBB* nod) {
  if ((nod->canBeRemoved()) || nod->getNodeUpperBound() < costSolution + 1) {
    delete nod;
  } else
    nodes.push_back(nod);
}

void KpSolverBB::insertNodes(NodeBB* nod1, NodeBB* nod2) {
  if (branchingStrategy == DFS01) {
    insertNode(nod1);
    insertNode(nod2);
  } else {
    insertNode(nod2);
    insertNode(nod1);
  }
}

// TODO
void KpSolverBB::solve() {
  init();

  while (!nodes.empty()) {        // while there are nodes to explore
    NodeBB* node = selectNode();  // we select a node to explore
    nbNodes++;                    // we increase the number of nodes explored

    // TODO

    NodeBB* nod1 = new NodeBB();
    nod1->init(nbItems);
    nod1->copySolution(node);
    nod1->fixFractionalVariable(node->getFractionalVariable(), 1);

    NodeBB* nod2 = new NodeBB();
    nod2->init(nbItems);
    nod2->copySolution(node);
    nod2->fixFractionalVariable(node->getFractionalVariable(), 0);

    nod1->solveUpperBound(knapsackBound, nbItems, weights, values);
    nod2->solveUpperBound(knapsackBound, nbItems, weights, values);

    if (withPrimalHeuristics) {
      nod1->primalHeuristic(knapsackBound, nbItems, weights, values);
      nod2->primalHeuristic(knapsackBound, nbItems, weights, values);
    }

    insertNodes(nod1, nod2);

    delete node;
  }
}
