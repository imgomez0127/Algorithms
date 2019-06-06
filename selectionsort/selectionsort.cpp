#include <iostream>
using namespace std;
static void swap(int array[], const int a, const int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}
void bubble_sort(int array[], const int length) {
    int len = length,pass_num = 0;
    while (len > 0) {
        int n = 0;
        for (int i = 1; i < len; ++i) {
            if (array[i - 1] > array[i]) {
                swap(array, i - 1, i);
                n = i;
            }
        }
        cout << endl;
        for(int i = 0; i < 6; i++){
			cout << array[i] << " ";
		}
		cout << endl;
		cout<< "Pass count = " << ++pass_num << endl;
        len = n;
    }
}
void insertion_sort(int array[], const int length) {
	int pass_num = 0;
    for (int i = 1; i < length; ++i) {
        int k, current = array[i];
        
        for (k = i - 1; k >= 0 && array[k] > current; --k) {
            array[k + 1] = array[k];
        }
        cout<< "Pass count = " << ++pass_num << endl;
        array[k + 1] = current;
    }
}
void selection_sort(int array[], const int length) {
	int pass_num = 0;
    for (int i = 0, i_bound = length - 1; i < i_bound; ++i) {
        int min_index = i, min = array[i];
        for (int j = i + 1; j < length; ++j) {
            if (array[j] < min) {
                min_index = j;
                min = array[j];
            }
        }
        if (min_index != i) {
            swap(array, i, min_index);
        }

        cout<< "Pass count = " << ++pass_num << endl;
        cout << endl;
        for(int i = 0; i < 6; i++){
			cout << array[i] << " ";
		}
		cout << endl;
    }
}
int main(){
	int arr[6] = {78,15,23,2,97,85};
	cout << "Insertion sort" << endl;
	insertion_sort(arr,6);

	for(int i = 0; i < 6; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
	int arr2[6] = {78,15,23,2,97,85};
	cout << "Bubble sort" << endl;
	bubble_sort(arr2,6);
	for(int i = 0; i < 6; i++){
		cout << arr2[i] << " ";
	}
	cout << endl;
	int arr3[6] = {78,15,23,2,97,85};
	cout << "Selection sort" << endl;
	selection_sort(arr3,6);
	for(int i = 0; i < 6; i++){
		cout << arr3[i] << " ";
	}
	cout << endl;
	return 0;
}	