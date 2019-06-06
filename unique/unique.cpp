/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Ian Gomez igomez1
 * Date        : 09/16/18
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : "I pledge my honor that I have abided by the Stevens honor system"-igomez1
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
     for(const auto &c : s){
     	if(!islower(c)){
     		return false;
     	}
     }
     return true;
}

bool all_unique_letters(const string &s) {
    // returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // uses bitwise operators and a single usigned int to run the algorithm
    unsigned int store = 0;
    for(const auto &c : s){
    	if((store &  (1 << (c-'a'))) > 0){
    		return false;
    	} 
    	store = store | (1 <<(c-'a'));
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // Reads the command line arguments and returns either
    // an error if imporerly inputted or whether or not there is unique letters.
    if(argc != 2){
    	cerr << "Usage: ./unique <string>" << endl;
    	return 1;
    }
    string inpS = argv[1];
    if(!is_all_lowercase(inpS)){
    	cerr << "Error: String must contain only lowercase letters." << endl;
    	return 1;
    }
    cout << (all_unique_letters(inpS) ? "All letters are unique." : "Duplicate letters found.") << endl;
    return 0;
}
