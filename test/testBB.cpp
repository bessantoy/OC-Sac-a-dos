#include "kpSolverGreedy.hpp"
#include "kpSolverBB.hpp"
#include <chrono>
#include <string>

using namespace std;

BranchingStrategies& operator ++ (BranchingStrategies& e)
{
    if (e == BranchingStrategies::End) {
        throw std::out_of_range("for E& operator ++ (E&)");
    }
    e = BranchingStrategies(static_cast<std::underlying_type<BranchingStrategies>::type>(e) + 1);
    return e;
}

void printModeBranching(BranchingStrategies  b){
	switch (b) {
	        case BestBound: std::cout << "BestBound"; break;
	        case BFS: std::cout << "BFS";  break;
	        case DFS10: std::cout << "DFS10"; break;
	        case DFS01: std::cout << "DFS01"; break;
	        case Random: std::cout << "Random";
	                break;              //execution of subsequent statements is terminated
	        case End: return;
	}
}

void printResultmodeBranching(KpSolverBB & kpBB, BranchingStrategies  b){
	cout  << endl << "         BB mode Branchement ";
	printModeBranching(b);
	cout << endl << endl;

	kpBB.setBranchingStrategy(b);

	auto start = std::chrono::steady_clock::now();
	kpBB.solve();
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double>  elapsed_seconds = end-start;
	std::cout << endl  << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
	kpBB.printKnapsackSolution(false);

}


int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        return 1;
    }

    bool verboseMode = true;
    if (argc < 3) verboseMode = false;
    const char* instanceFile = argv[1];


    KpSolverGreedy kpGreedy;
    kpGreedy.importInstance(instanceFile);
    //kpGreedy.extractSubInstance(0,1000);

    if (verboseMode) kpGreedy.printKnapsackInstance();

    cout  << endl << "Greedy bounds :"  << endl << endl;

    auto start = std::chrono::steady_clock::now();
    kpGreedy.solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl<< endl;
    kpGreedy.printKnapsackSolution(false);


    KpSolverBB kpBB;
	kpBB.importInstance(instanceFile);
	kpBB.setVerboseMode(verboseMode);
	kpBB.setNbMaxNodeBb(10000);
	kpBB.setSizeDPheur(100);
	kpBB.setWithPrimalHeuristics(false);
	kpBB.setWithDPinitPrimalHeuristic(false);

/* */
    cout  << endl << "Resultats sans heuristique gloutonne:"  << endl << endl;

    for ( BranchingStrategies modeBranch = BranchingStrategies::BestBound; modeBranch != BranchingStrategies::End; ++modeBranch){
    	printResultmodeBranching(kpBB,modeBranch);

    }

    cout  << endl << "Resultats avec heuristique gloutonne:"  << endl << endl;

	kpBB.setWithPrimalHeuristics(true);

    for ( BranchingStrategies modeBranch = BranchingStrategies::BestBound; modeBranch != BranchingStrategies::End; ++modeBranch){
    	printResultmodeBranching(kpBB,modeBranch);

    }

    cout  << endl << "Resultats avec heuristique prog dyanmqiue:"  << endl << endl;

    kpBB.setWithDPinitPrimalHeuristic(true);

    for ( BranchingStrategies modeBranch = BranchingStrategies::BestBound; modeBranch != BranchingStrategies::End; ++modeBranch){
    	printResultmodeBranching(kpBB,modeBranch);

    }

    return 0;

}
