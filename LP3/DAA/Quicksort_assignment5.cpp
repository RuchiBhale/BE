#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to perform deterministic Quick Sort
int deterministicPartition(vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // Pivot is the first element
    int left = low + 1;
    int right = high;

    while (true) {
        while (left <= right && arr[left] <= pivot) {
            left++;
        }
        while (left <= right && arr[right] >= pivot) {
            right--;
        }
        if (left > right) {
            break;
        }
        swap(arr[left], arr[right]);
    }
    swap(arr[low], arr[right]);
    return right;
}

void deterministicQuickSort(vector<int>& arr, int low, int high, int& comparisons, int& swaps) {
    if (low < high) {
        int pivotIndex = deterministicPartition(arr, low, high);
        comparisons += (high - low); // Count comparisons made during partition
        swaps += 2; // Count the swaps made during partition

        deterministicQuickSort(arr, low, pivotIndex - 1, comparisons, swaps);
        deterministicQuickSort(arr, pivotIndex + 1, high, comparisons, swaps);
    }
}

// Function to perform randomized Quick Sort
int randomizedPartition(vector<int>& arr, int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[low], arr[pivotIndex]); // Swap pivot with the first element
    int pivot = arr[low];
    int left = low + 1;
    int right = high;

    while (true) {
        while (left <= right && arr[left] <= pivot) {
            left++;
        }
        while (left <= right && arr[right] >= pivot) {
            right--;
        }
        if (left > right) {
            break;
        }
        swap(arr[left], arr[right]);
    }
    swap(arr[low], arr[right]);
    return right;
}

void randomizedQuickSort(vector<int>& arr, int low, int high, int& comparisons, int& swaps) {
    if (low < high) {
        int pivotIndex = randomizedPartition(arr, low, high);
        comparisons += (high - low); // Count comparisons made during partition
        swaps += 2; // Count the swaps made during partition

        randomizedQuickSort(arr, low, pivotIndex - 1, comparisons, swaps);
        randomizedQuickSort(arr, pivotIndex + 1, high, comparisons, swaps);
    }
}

// Function to print the array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0)); // Seed for random number generation

    
    int n;
    cout<<"Enter the number of elements: ";
    cin>>n;
    vector<int> arr1(n);
    cout<<"Enter elements: \n";
    for(int i=0;i<n;i++){
        cin>>arr1[i];
    }
    vector<int> arr2 = arr1;
    int ch;
    while(1){

    
    int comparisonsDet = 0, swapsDet = 0;
    int comparisonsRand = 0, swapsRand = 0;
    
    cout<<"1.Deterministic Quick Sort\n2.Randomized Quick Sort\n3.Exit\n";
    cout<<"Enter your choice: ";
    cin>>ch;
    switch(ch){
        case 1:
            cout << "Original array for deterministic quick sort:\n";
            printArray(arr1);

            deterministicQuickSort(arr1, 0, arr1.size() - 1, comparisonsDet, swapsDet);

            cout << "Sorted array (Deterministic):\n";
            printArray(arr1);
            cout << "Deterministic Quick Sort Comparisons: " << comparisonsDet << endl;
            cout << "Deterministic Quick Sort Swaps: " << swapsDet << endl;
            break;
        case 2:
            // Perform randomized quick sort
            cout << "\nOriginal array for randomized quick sort:\n";
            printArray(arr2);

            randomizedQuickSort(arr2, 0, arr2.size() - 1, comparisonsRand, swapsRand);

            cout << "Sorted array (Randomized):\n";
            printArray(arr2);
            cout << "Randomized Quick Sort Comparisons: " << comparisonsRand << endl;
            cout << "Randomized Quick Sort Swaps: " << swapsRand << endl;
            break;
        case 3:
            exit(0);
            break;


    }
    }

    

    return 0;
}