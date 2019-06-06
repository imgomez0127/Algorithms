/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Ian Gomez 
 * Pledge        : "I pledge my honor that I have abided by the Stevens honor system"-igomez1
 * Date          : 10/28/18
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;
void swap(int *array,size_t i,size_t j){
    /**
    *Takes in an array, and two indices i and j
    * and switches the values held within these indices
    */
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}
size_t lomuto_partition(int array[], size_t left, size_t right) {
    /**
    * Takes in an array and the index for the left most index and the right most index of what should be partitioned
    * it then partitions the portion of the array which is in between these indices
    */
    int p = array[left];
    unsigned int s = left;
    for(unsigned int i = left+1; i <= right; ++i){
    	if(array[i] < p){
    		s = s + 1;
    		swap(array,i,s);
    	}
    }
    swap(array,left,s);
    return s;
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
    /**
    * takes in an array, indices left and right, and the k smallest value which is to be found
    * it then performs a quickselect on the array portion in between the left and right indices and then
    * recursively calls until it find the kth smallest value in the array
    * it does this by either recursing on the left side of the pivot if s is greather than the leftmost index + k -1 
    * and if not then it recurses the right half of the pivot
    */
    unsigned int s = lomuto_partition(array,left,right);
    if(s-left == k-1){
    	return array[s];
    }
    else if (s>left + k - 1){
    	return quick_select(array,left,s-1,k);
    }
    else{
    	return quick_select(array,s+1,right,k-1-(s-left));
    }
}

int quick_select(int array[], const size_t length, size_t k) {
    /**
    *  Performs quickselect from the beginning of the array to the end of the array
    */
    return quick_select(array, 0, length-1 , k);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
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

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    if(k > num_values){
    	cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " value" << ((num_values > 1)?"s":"") << "." << endl;
    	return 1;
    }
    
    int *arr = new int[num_values];
    for(int i = 0; i < num_values; ++i){
        arr[i] = values[i];
    }
    int result = quick_select(arr,num_values,k);
   	cout <<  "Smallest element " << k << ": " << result << endl;
    delete [] arr;
    return 0;
}
