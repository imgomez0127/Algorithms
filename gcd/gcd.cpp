/*
 * gcd.cpp
 * "I pledge my honor that I have abided by the Stevens honor system" -igomez1
 *  Created on: Aug 31, 2018
 *      Author: igomez1
 */
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;
int gcd(int m, int n){
	int r;
	while(n != 0){
		r = abs(m % n);
		m = n;
		n = r;
	}
	return m;
}
int gcd_rec(int m, int n){
	if(n == 0){
		return m;
	}
	return gcd_rec(n, abs(m % n));
}
int main(int argc, char *argv[]){
	int m,n;
	istringstream iss;
	if(argc != 3){
		cerr << "Usage: ./gcd <integer m> <integer n>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if(!(iss >> m)){
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if(!(iss>>n)){
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}
	cout << "Iterative: gcd(" << m << ", "  << n << ")" <<  " = " << gcd(m,n) << endl;
	cout << "Recursive: gcd(" << m << ", "  << n << ")" << " = " << gcd(m,n);
}

