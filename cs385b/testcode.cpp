/*
 * testcode.cpp
 *
 *  Created on: Aug 31, 2018
 *      Author: ianm0
 */

#include <iostream>
#include <sstream>

using namespace std;

int max(int m, int n){
	return m > n ? m : n;
}

int main(int argc, char *argv[]){
	int m,n;
	istringstream iss;
	if(argc != 3){
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if(!(iss>>m)){
		cerr << "Error: M is not an Integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if(!(iss>>n)){
		cerr << "Error: N is not an Integer." << endl;
		return 1;
	}
	cout << "max(" << m << ", " << m << ") = " << max(m,n) << endl;
	return 0;
}
