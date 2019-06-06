/*
 * helloworld.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: ianm0
 */
#include <iostream>

using namespace std;

int main(){
	cout << "Hello World!" << endl;
	bool yeet = true;
	bool yert = false;
	int sksksk = 0;
	sksksk = yeet + yert;
	for(int i = 0; i < 10; i++){
		sksksk += yeet;
	}
	yeet ? sksksk+= yeet : sksksk += yert;
	yeet = false,yert=true;
	cout <<yeet << " " << yert << endl;
	cout << sksksk << endl;
	return 0;
}
