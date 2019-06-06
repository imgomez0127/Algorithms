/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Ian Gomez
 * Date        : 10/3/2018
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : "I pledge my honor that I have abided by the Stevens honor system"-igomez1
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;
map<int, vector<vector<int>>> m;


vector<vector<int>> get_ways(int num_stairs) {
    // returns a vector of the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    if(m.find(num_stairs) != m.end()){
    	return m[num_stairs];
    }
    else{
		vector<vector<int>> ways;
		if(num_stairs == 0){
		   	vector<int> empt(0);	
		   	ways.push_back(empt);
		   	}
		else{ 
			for(int i = 1; i<4;i++){
			   	if(num_stairs >= i){
				   	vector<vector<int>> result = get_ways(num_stairs-i);
				   	for(auto &r:result){
				   		r.insert(r.cbegin(),i);
				   		ways.push_back(r);
				   	}
				   }
			   }
	  		}
	  	m[num_stairs] = ways;
	    return ways;
	}
}

int num_digits(int num){
        /**
            returns the amount of digits in the inputted number
        */
        int digCount = 1;
        while(num > 10){
            num = num / 10;
            digCount++;
        }
        return digCount;
    }
void display_ways(const vector< vector<int> > &ways) {
    // Displays the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    unsigned int size = ways.size();
	int maxDig = num_digits(size);
	cout << size << " way" << ((size > 1) ? "s ": " ") << "to climb " << ways[0].size() << " stair" << ((ways[0].size() > 1) ? "s." : ".") << endl; 
    for(unsigned int i = 0; i < size; i++){
    	cout << setw(maxDig) << i+1 << ". ";
		cout << "[";
		for(unsigned int j = 0; j < ways[i].size(); j++){
			cout << ways[i][j] << ((j+1 == ways[i].size()) ? "" : ", ");	
		}
		cout << "]" << endl;

	}
}


int main(int argc, char * const argv[]) {
	/**
		Processes in the command line argument and returns the number of ways to walk over the stairs of size input
	*/
	int num_stairs;

	istringstream iss;
	if(argc != 2){
		cerr << "Usage: ./stairclimber <number of stairs>"<<endl;
		return 1;
	}
	iss.str(argv[1]);
	if(!(iss >> num_stairs)){
		cerr << "Error: Number of stairs must be a positive integer."<<endl;
		return 1;
	}
	if(num_stairs <= 0){
		cerr << "Error: Number of stairs must be a positive integer."<<endl;
		return 1;
	}
	vector<vector<int>> ways = get_ways(num_stairs);
	display_ways(ways);
	return 0;
}
		