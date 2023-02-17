//********* kpSolver.cpp *********

#include "kpSolver.hpp"
#include <math.h>

void KpSolver::importInstance(const string& fileName) {

	clearInstance();

    ifstream infile;
    infile.exceptions(ifstream::failbit | ifstream::badbit);
    infile.open(fileName.c_str());

    infile >> nbItems;

    weights.resize(nbItems);
    for (int i = 0; i < nbItems; i++) infile >> weights[i];

    values.resize(nbItems);
    for (int i = 0; i < nbItems; i++) infile >> values[i];
    
    infile >> knapsackBound;

    sortKnapsack();


 }



void KpSolver::sortKnapsack() {

	vector<std::pair<std::pair<int,int>,float>> newStruct;

	std::pair <int,int> item;
	std::pair<std::pair<int,int>,float> itemCost;

	for (int i = 0; i < nbItems; i++){
		item = make_pair (weights[i],values[i]);
		itemCost = make_pair(item,(float) values[i] / ((float) weights[i]) );
	        newStruct.push_back(itemCost);
	}	

	std::sort(newStruct.begin(), newStruct.end(),
			[](std::pair<std::pair<int,int>,float> i, std::pair<std::pair<int,int>,float> j) {return i.second > j.second;}
	);

	for (int i = 0; i < nbItems; i++){
		weights[i] = newStruct[i].first.first;
		values[i] = newStruct[i].first.second;		
	}
	newStruct.clear();
}

void KpSolver::clearInstance() {
	values.clear();
	weights.clear();
	nbItems = -1;

	solution.clear();
	costSolution=0;
	upperBoundOPT=0;
}

void KpSolver::printKnapsackInstance() {

	cout << "Max capacity knapsack : " << knapsackBound  << endl;

	for (int i = 0; i < nbItems; i++){
	        cout << "Item: " << i << " Weight : " << weights[i]  << " Value : " << values[i] << " Marginal Cost : " << (float) values[i] / ((float) weights[i])  << endl;
	}
	 cout << endl;	
 }

void KpSolver::printKnapsackSolution(bool printSol) {

	cout << "solution cost : " << costSolution << endl;
	cout << "proven upper bound  : " << upperBoundOPT << endl;
	cout << "proven upper bound  after rounding: " << floor(upperBoundOPT) << endl;

	cout << "gap : " << (floor(upperBoundOPT)- (double)costSolution) /( (double)costSolution) * 100 << "%" << endl;

	if (printSol){
	cout << "knapsack composition  : ";
	for (std::vector<bool>::iterator it = solution.begin() ; it != solution.end(); ++it)
		    std::cout << ' ' << *it;
	cout  << endl;
	}

}


void KpSolver::extractSubInstance(int idMin, int idMax) {

    idMin= max(0,idMin);
    idMax= min(nbItems,idMax);

	float numerator = 0;
	for (int i = idMin; i< idMax; i++){
		numerator += weights[i];
	}
	float denominator = 0 ;
	for (int i = 0; i < nbItems ; i++){
		denominator += weights[i];
	}
	knapsackBound =  (int) (((float) knapsackBound) * numerator / denominator) ;

	nbItems = idMax - idMin;
	vector<int> oldweights = weights ;
	vector <int> oldvalues = values ;

    weights.resize(nbItems);
    values.resize(nbItems);

	for (int i = 0; i<nbItems; i++){
		weights[i] = oldweights[i+idMin];
		values[i] = oldvalues[i+idMin];
	}
}
