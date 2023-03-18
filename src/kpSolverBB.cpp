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

  upperBoundOPT = node0->getNodeUpperBound();
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

void KpSolverBB::solve() {
  init();
  while (!nodes.empty() && nbNodes < nbMaxNodeBB) {
    NodeBB* node = selectNode();
    nbNodes++;
    if (node->getFractionalVariable() != 0) {
      if (node->getNodeUpperBound() >= costSolution + 1) {
        // This node is not a leaf
        NodeBB* node1 = new NodeBB(*node);
        NodeBB* node2 = new NodeBB(*node);
        // Fix the variable to 1 and 0
        node1->fixVariable(node->getCriticalIndex(), 1);
        node2->fixVariable(node->getCriticalIndex(), 0);
        // Solve the upper bound
        node1->solveUpperBound(knapsackBound, nbItems, weights, values);
        node2->solveUpperBound(knapsackBound, nbItems, weights, values);
        // Apply the primal heuristics
        if (withPrimalHeuristics) {
          node1->primalHeuristic(knapsackBound, nbItems, weights, values);
          node2->primalHeuristic(knapsackBound, nbItems, weights, values);
        }
        // Insert the nodes in the queue
        insertNodes(node1, node2);
      }
      delete node;
    } else {
      node->primalHeuristic(knapsackBound, nbItems, weights, values);
      if (node->getNodePrimalBound() >= costSolution + 1) {
        costSolution = node->getNodePrimalBound();
        node->copyPrimalSolution(&solution);
      }
      delete node;
    }
  }
}