#include "kpSolverHeurDP.hpp"
#include "kpSolverGreedy.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;


void printDPsolverResult(KpSolverHeurDP & kp, int sizeMax, int sizeNeighbor, string sep, ofstream & outfile){
	if (sizeMax<kp.getNbItems()){
    kp.setNeighborhood(sizeNeighbor,sizeNeighbor);
    if (sizeMax>0) kp.extractSubInstance(0,sizeMax);
    auto start = std::chrono::steady_clock::now();
    kp.solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
	outfile << kp.getSolutionCost() << sep << elapsed_seconds.count() << sep << sep;
	kp.clearInstance();
	}
}

void printGreedySolverResult(KpSolverGreedy & kp, int sizeMax, string sep, ofstream & outfile){
	if (sizeMax<kp.getNbItems()){
    if (sizeMax>0) kp.extractSubInstance(0,sizeMax);
    auto start = std::chrono::steady_clock::now();
    kp.solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    outfile << kp.getUpperBound() << sep << kp.getSolutionCost() << sep << elapsed_seconds.count() << sep << sep;
	kp.clearInstance();
	}
}


int main(int argc, char** argv) {

	vector<string> files {
	"../instances/kp_100_1.in",
	"../instances/kp_100_2.in",
	"../instances/kp_1000_1.in",
	"../instances/kp_1000_2.in",
	"../instances/kp_10000_1.in",
	"../instances/kp_10000_1_0.1.in",
	"../instances/kp_10000_1_0.01.in",
	"../instances/kp_10000_1_0.02.in",
	"../instances/kp_10000_1_0.03.in",
	"../instances/kp_10000_1_0.04.in",
	"../instances/kp_10000_1_0.05.in",
	"../instances/kp_10000_2.in",
	"../instances/kp_100000_1.in",
	"../instances/kp_100000_2.in"
	};

	vector<int> sizePb { -1,100,  1000, 10000, 100000};


    string sep = ",";
    const char* instanceFile;


    KpSolverGreedy kpGreedy;
    KpSolverHeurDP kpHeurDP;

    ofstream outfile("../csv/iterHeur.csv", ios::out | ios::trunc);

    if(outfile)
    {
        // instructions
    	for (std::vector<int>::iterator itNbItems = sizePb.begin() ; itNbItems != sizePb.end(); ++itNbItems){
    		for (std::vector<string>::iterator it = files.begin() ; it != files.end(); ++it){
    			instanceFile = (*it).c_str();
    			kpGreedy.importInstance(instanceFile);
    			if ((*itNbItems)<kpGreedy.getNbItems()){
    				outfile << *it << sep << (*itNbItems) << sep << sep;
    				printGreedySolverResult(kpGreedy, *itNbItems, sep, outfile);
    			}
    			kpGreedy.clearInstance();
    			kpHeurDP.importInstance(instanceFile);
    			if ((*itNbItems)<kpHeurDP.getNbItems()){
    				printDPsolverResult(kpHeurDP, *itNbItems, 100, sep,  outfile);
    				outfile << endl;
    				kpHeurDP.clearInstance();
    			}
    		}
    	}
    	outfile.close();
    }
    else  // sinon
            cerr << "Erreur à l'ouverture !" << endl;


    return 0;

}
