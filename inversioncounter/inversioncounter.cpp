/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Ian Gomez
 * Version     : 1.0
 * Date        : 10/04/2018
 * Description : Counts the number of inversions in an array.
 * Pledge      : "I pledge my Honor that I have abided by the Stevens honor system" - Ian Gomez igomez1
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;
// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);


long count_inversions_slow(int array[], int length) {
	/**
	* Takes in an integer array and the length of the array as input and returns
 	* the number of inversions in an array in theta(n^2) time.
 	*/
    long inversions = 0;
    for(int i = 0; i < length; ++i){
        for(int j = i; j < length; ++j){
            if(array[i] > array[j]){
                inversions++;
            }
        }
    }
    return inversions;
}

long count_inversions_fast(int array[], int length) {
	/**
 	* Takes in an integer array and the length of the array as input and returns
 	* the number of inversions in an array in theta(n lg n) time.
 	*/
    int *arr = new int[length];
    long inversions = mergesort(array,arr,0,length-1);
    delete [] arr;
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
	/**
	* Takes in an integer array a scratch array the low value
	* for the range of the array to be analyzed and a high valeu
	* for the range of the array to be analyzed.
	* This function recursively performs a mergesort on the array
	* and returns the amount of inversions that the array has
	*/
    long inversions = 0;
    
    if (low < high){
        int mid = low + (high - low) / 2;
        inversions += mergesort(array,scratch,low,mid);
        inversions += mergesort(array,scratch,mid+1,high);
        
        int L = low;
        int H = mid+1;
        for(int k = low; k <= high; k++){

            if(L <= mid && (H > high || array[L] <= array[H])){
                scratch[k] = array[L];
                L++;
            }
            else{   
            	if(L <= mid && array[L] >= array[H]){
            		inversions += (mid+1) - L;
            	}
                scratch[k] = array[H];
                H++;
            }
        }
        for(int k = low; k <= high; k++){
            array[k]=scratch[k];
        }
    }

    return inversions;
}

int main(int argc, char *argv[]) {
    if(argc > 2){
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }
    string algVer = ((argc == 1) ? "" : argv[1]);
    if(algVer != "" && algVer != "slow"){
        cerr << "Error: Unrecognized option '" << algVer << "'." << endl;
        return 1; 
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;
    
    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    // TODO: produce output
    int *arr = &values[0];
    unsigned int vals_len = values.size();
    if(vals_len == 0){
        cerr << "Error: Sequence of integers not received."<< endl; 
        return 1;
    }
    

    long inversions =  (algVer == "slow")? count_inversions_slow(arr,vals_len) : count_inversions_fast(arr,vals_len);
    cout << "Number of inversions: " << inversions << endl;
    return 0;
}
