/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Ian Gomez
 * Version     : 1.0
 * Date        : 12/4/18
 * Description : Given a file perform floyd's shortest paths algorithm for the graph represented in the file
 * Pledge      : "I pledge my honor that I have abided by the Stevens honor system"- igomez1
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
#include <cctype>
#include <unordered_map>
using namespace std;
enum Label{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};
long INF = LONG_MAX/2;
unordered_map<char,int> toEnumVal;
/**
* Fills the global unordered_map to map chars A-Z with the correct enum values
*/
void populate_map(){
    char startChar = 'A';
    for(int i = 0; i < 26; ++i){
        toEnumVal[startChar+i] = i;
    }
}
/**
*  given a number compute the amount of digits it has 
*/
int len(long val){
    int digits = 1;
    while(val > 9){
        ++digits;
        val /= 10;
    }
    return digits;
}

/**
* Displays the matrix on the the screen formatted as a table
*/
void display_table(long** const matrix,unsigned int num_vertices, const string &label, const bool use_letters = false){
    cout << label << endl;
    long max_val = 0;
    for(unsigned int i = 0; i < num_vertices; ++i){
        for(unsigned int j = 0; j < num_vertices; ++j){
            long cell = matrix[i][j];
            if(cell < INF && cell > max_val){
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = len(max(static_cast<long>(num_vertices),max_val));
    cout << ' ';
    for(unsigned int j = 0; j < num_vertices; ++j){
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for(unsigned int i = 0; i < num_vertices; ++i){
        cout << static_cast<char>(i+'A');
        for(unsigned int j = 0; j < num_vertices; ++j){
            cout << " " << setw(max_cell_width);
            if(matrix[i][j] == INF){
                cout << "-";
            }
            else if(use_letters){
                cout << static_cast<char>(matrix[i][j] + 'A');
            }else{
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}
/**
*   Creates and returns a matrix NxN matrix that is initially filled with infinites and has a diagonal of 0's
*/
long ** createMat(unsigned int nodeCount){
    long ** temp = new long*[nodeCount];

    for(unsigned int i = 0; i < nodeCount; ++i){
        long * innerTemp = new long[nodeCount];
        for(unsigned int j = 0; j < nodeCount; ++j){

            innerTemp[j] = (i!=j) ? INF : 0; 
        }
        temp[i] = innerTemp;
    }
    return temp;

}
/**
*   Creates and returns the vertices matrix which is initially filled with all infinities
*/
long ** createVerticesMat(unsigned int nodeCount){
    long ** temp = new long*[nodeCount];

    for(unsigned int i = 0; i < nodeCount; ++i){
        long * innerTemp = new long[nodeCount];
        for(unsigned int j = 0; j < nodeCount; ++j){

            innerTemp[j] = INF; 
        }
        temp[i] = innerTemp;
    }
    return temp;
}
/**
*  Creates and returns a copy of the input matrix
*/
long ** copy(long** originalMatrix,unsigned int nodeCount){
    long ** temp = new long*[nodeCount];

    for(unsigned int i = 0; i < nodeCount; ++i){
        long * innerTemp = new long[nodeCount];
        for(unsigned int j = 0; j < nodeCount; ++j){

            innerTemp[j] = originalMatrix[i][j]; 
        }
        temp[i] = innerTemp;
    }
    return temp;
}
/**
*   takes in a given matrix and its NxN size and performs a delete operation to ensure that memory is not lost
*/
void deleteMatrix(long ** distanceMatrix,unsigned int nodeCount){
    for(unsigned int i = 0; i < nodeCount; ++i){
        delete [] distanceMatrix[i];
    }
    delete [] distanceMatrix;
}
/**
*  Takes in a given vector and a value and checks whether or not the value is in the vector
*/
bool not_in(vector<long> nodePath,int val){
    for(unsigned int i = 0; i < nodePath.size(); ++i){
        if(nodePath[i] == val){
            return false;
        }
    }
    return true;
}
/**
*  given a matrix of vertices returns a vector that contains that path traveled to get from one node to the other
*/
vector<long> computePaths(long ** intermediateVertices, int i, int j, vector<long> nodePath){
    if(intermediateVertices[i][j] == INF){
        if(not_in(nodePath,j)){
            nodePath.insert(nodePath.begin(),j);
        }
        return nodePath;
    }
    if(not_in(nodePath,j)){
        nodePath.insert(nodePath.begin(),j);
    }
    nodePath = computePaths(intermediateVertices,intermediateVertices[i][j],j,nodePath);
    return computePaths(intermediateVertices,i,intermediateVertices[i][j],nodePath);
    

}

/**
*  given a matrix of graph vertices, a matrix of path lengths, and the NxN count returns the given path and the distance for each path in a string format
*/
string allPaths(long ** intermediatePaths, long** intermediateVertices, unsigned int nodeCount){
    ostringstream oss;
    for(unsigned int i = 0; i < nodeCount ; ++i){
        for(unsigned int j = 0; j < nodeCount; ++j){
            oss << static_cast<char>('A' + i) << " -> " << static_cast<char>('A' + j) << ", distance: " << (intermediatePaths[i][j] == INF ? "infinity" : to_string(intermediatePaths[i][j])) << ", path: ";
            if(i == j){
                oss << static_cast<char>('A' + i) << "\n";
            }
            else if(intermediatePaths[i][j] != INF){
                vector<long> nodePaths;
                oss << static_cast<char> ('A' + i);
                nodePaths = computePaths(intermediateVertices,i,j,nodePaths);
                for(unsigned int k = 0; k < nodePaths.size(); ++k){
                    oss << " -> " << static_cast<char>('A' + nodePaths[k]);
                }
                oss << "\n";
            }
            else{
                oss << "none\n";
            }

        }   
    }
    return oss.str();
}
/**
*  This function performs floyd's algorithm on a given matrix and then prints out a representation of all the paths that were found using this algorithm
*/
void floyd(long ** distanceMatrix, unsigned int nodeCount){
    long ** intermediatePaths = copy(distanceMatrix,nodeCount);
    long ** intermediateVertices = createVerticesMat(nodeCount);
    for(unsigned int k = 0; k < nodeCount; ++k){
        for(unsigned int i = 0; i < nodeCount; ++i){
            for(unsigned int j = 0; j < nodeCount; ++j){

                if(intermediatePaths[i][j] > (intermediatePaths[i][k] + intermediatePaths[k][j])){
                    intermediatePaths[i][j] = intermediatePaths[i][k] + intermediatePaths[k][j];
                    intermediateVertices[i][j] = k;
                }
            }
        }
    }
    display_table(distanceMatrix,nodeCount,"Distance matrix:",false);
    display_table(intermediatePaths,nodeCount,"Path lengths:");
    display_table(intermediateVertices,nodeCount,"Intermediate vertices:",true);
    cout << allPaths(intermediatePaths,intermediateVertices,nodeCount) << endl;
    deleteMatrix(intermediatePaths,nodeCount);
    deleteMatrix(intermediateVertices,nodeCount);
}
int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    int nodeCount;
    populate_map();
    long ** distanceMatrix;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
            if(line_number == 1){
                
                istringstream iss;
                iss.str(line);
                if(!(iss >> nodeCount) || nodeCount == 0 || nodeCount > 26){
                    cerr << "Error: Invalid number of vertices '" + line + "' on line "<< line_number <<  "." << endl;
                    return 1;
                }
                distanceMatrix = createMat(nodeCount);
            }
            else{
                istringstream iss;
                iss.str(line);
                int lineItem = 0;
                int pathLength;
                vector<string> seperatedLine;
                for(string s; iss >> s;){
                    seperatedLine.push_back(s);
                    lineItem++;
                }
                iss.clear();
                if(lineItem != 3){
                    deleteMatrix(distanceMatrix,nodeCount);
                    cerr << "Error: Invalid edge data '" + line + "' on line " << line_number << "." << endl;
                    return 1;
                }
                if(seperatedLine[0].length() > 1 || toEnumVal[seperatedLine[0].c_str()[0]] >= nodeCount || !isalpha(seperatedLine[0].c_str()[0]) || !isupper(seperatedLine[0].c_str()[0])){
                    deleteMatrix(distanceMatrix,nodeCount);
                    cerr << "Error: Starting vertex '" + seperatedLine[0] + "' on line " << line_number << " is not among valid values A-" << static_cast<char> ('A' + nodeCount-1) << "." << endl;
                    return 1;
                }
                if(seperatedLine[1].length() > 1 || toEnumVal[seperatedLine[1].c_str()[0]] >= nodeCount || !isalpha(seperatedLine[1].c_str()[0]) || !isupper(seperatedLine[0].c_str()[0])){
                    deleteMatrix(distanceMatrix,nodeCount);
                    cerr << "Error: Ending vertex '" + seperatedLine[1] + "' on line " << line_number << " is not among valid values A-" << static_cast<char> ('A' + nodeCount-1) << "." << endl;
                    return 1;
                }
                iss.str(seperatedLine[2]);
                if(!(iss >> pathLength) || pathLength <= 0){
                    deleteMatrix(distanceMatrix,nodeCount);
                    cerr << "Error: Invalid edge weight '" << seperatedLine[2] << "' on line " << line_number << "." << endl;
                    return 1;
                }
                distanceMatrix[toEnumVal[seperatedLine[0].c_str()[0]]][toEnumVal[seperatedLine[1].c_str()[0]]] = pathLength;
            }
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    floyd(distanceMatrix,nodeCount);
    deleteMatrix(distanceMatrix,nodeCount);
    return 0;
}
