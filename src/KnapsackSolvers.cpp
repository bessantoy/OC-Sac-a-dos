#include "kpSolverHeurDP.hpp"
#include "kpSolverDP.hpp"
#include "kpSolverGreedy.hpp"
#include <chrono>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        cerr << "A third parameter enables verbosity, useful for debugging" << endl;
        return 1;
    }

    bool verboseMode = true;
    bool HeuristicMode = false;
    if (argc < 3) HeuristicMode = true;
    if (argc < 4) verboseMode = false;
    const char* instanceFile = argv[1];


    KpSolverGreedy kpGreedy;
    kpGreedy.importInstance(instanceFile);

    //if (verboseMode) 
    kpGreedy.printKnapsackInstance();

    cout  << endl << "Greedy bounds :"  << endl << endl;

    auto start = std::chrono::steady_clock::now();
    kpGreedy.solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl<< endl;
    kpGreedy.printKnapsackSolution(verboseMode);

    kpGreedy.extractSubInstance(0,10);
    //if (verboseMode) 
    kpGreedy.printKnapsackInstance();



    KpSolverDP kp;
    KpSolverHeurDP kpHeurDP;

    if (HeuristicMode){
    	kpHeurDP.importInstance(instanceFile);

    	cout  << endl << "Dynamic Programming heuristic  with neighborhood 100,100 :"  << endl << endl;
    	kpHeurDP.setNeighborhood(100,100);

    	start = std::chrono::steady_clock::now();
    	kpHeurDP.solve();
    	end = std::chrono::steady_clock::now();
    	elapsed_seconds = end-start;
    	std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    	kpHeurDP.printKnapsackSolution(verboseMode);

    	cout  << endl << "Dynamic Programming heuristic  with neighborhood 200,200 :"  << endl << endl;
    	kpHeurDP.setNeighborhood(200,200);
    	start = std::chrono::steady_clock::now();
    	kpHeurDP.solve();
    	end = std::chrono::steady_clock::now();
    	elapsed_seconds = end-start;
    	std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    	kpHeurDP.printKnapsackSolution(verboseMode);

    }
    else
    {
    kp.importInstance(instanceFile);
	kp.setVerboseMode(verboseMode);
        kp.setMemoizedVersion(false);

	cout  << endl << "Dynamic Programming iterative version without parallelization  :"  << endl << endl;



	start = std::chrono::steady_clock::now();
	kp.solve();
	end = std::chrono::steady_clock::now();
	elapsed_seconds = end-start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

	kp.printKnapsackSolution(verboseMode);

	cout  << endl << "Dynamic Programming memoized version :"  << endl << endl;

	kp.setMemoizedVersion(true);
	 start = std::chrono::steady_clock::now();
	kp.solve();
	 end = std::chrono::steady_clock::now();
	elapsed_seconds = end-start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;

	kp.printKnapsackSolution(verboseMode);

    }
	
    return 0;

}
