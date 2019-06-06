#include "rbtree.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <ctype.h>
using namespace std;
string printMostCommon(int m, RedBlackTree<string,int> *most_common_words){

	return "yes";
}
bool validString(string s){
	for(const char &c:s){
		if(c != 45 && c != 39 && !isalpha(c)){
			return false;
		}
	}
	return true;
}
string lowerAll(string s){
	ostringstream oss;
	for(char &c: s){
		oss << (char) tolower(c);
	}
	return oss.str();
}
int main(int argc, char *argv[]){
	if(argc != 2){
		cerr << "Usage: ./CommonWords <filename>"<< endl;
		return 1;
	}
	RedBlackTree<string,int> *most_common_words = new RedBlackTree<string,int>();
	string line;
	istringstream iss;
	ifstream file(argv[1]);
	if(file.is_open()){
		while(getline(file,line)){
			line = lowerAll(line);
			iss.str(line);
			for(string s; iss>>s;){
				if(validString(s)){
					RedBlackTree<string,int>::iterator it = most_common_words->find(s);
					if(it == most_common_words->end()){
						most_common_words->insert(s,1);
					}
					else{
						it->set_value(it->value()+1);
					}
				}
			}
			iss.clear();
		}
	}
	int i;
	cout << "How many of the most common words do you wish to display: ";
	cin >> i;
	cout << printMostCommon(i,most_common_words) << "\n";
	cout << most_common_words->to_ascii_drawing() << endl;
	delete most_common_words;
	return 0;
}