#include "kpSolverDP.hpp"

#include <chrono>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: knapsack inputFile  [verbosity]" << endl;
        cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        return 1;
    }

    bool verboseMode = true;
    if (argc < 3) verboseMode = false;
    const char* instanceFile = argv[1];


    
    KpSolverDP kp;


    	kp.setMemoizedVersion(false);

        kp.importInstance(instanceFile);
	kp.setVerboseMode(verboseMode);

    	cout  << endl << "Dynamic Programming iterative version  :"  << endl << endl;

    	auto start1 = std::chrono::steady_clock::now();
    	kp.solve();
    	auto end1 = std::chrono::steady_clock::now();
    	std::chrono::duration<double> elapsed_seconds = end1-start1;
    	std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    	kp.printKnapsackSolution(verboseMode);
        kp.clearInstance();

    	kp.importInstance(instanceFile);
    	kp.setVerboseMode(verboseMode);

    	cout  << endl << "Dynamic Programming memoized version :"  << endl << endl;

    	kp.setMemoizedVersion(true);
    	auto start = std::chrono::steady_clock::now();
    	kp.solve();
    	auto end = std::chrono::steady_clock::now();
    	elapsed_seconds = end-start;
    	std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

    	kp.printKnapsackSolution(verboseMode);

    return 0;

}
