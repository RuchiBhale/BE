#include <iostream>
#include <ctime>
#include <vector>
#include <chrono>
#include <omp.h>
#include <cstdlib>
using namespace std;

#define TEST_ARR_SIZE 100000
#define N_CPU_CORES 4
void sequentialBubbleSort(vector<int> &arr){
    for(int i=0;i<arr.size();i++){
        for(int j = 0; j<arr.size()-i-1; j++){
            if(arr[j]> arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
void parallelBubbleSort(vector<int> &arr ){
    bool sorted = false;
    while(!sorted){
        bool localSorted = true;
        #pragma omp parallel for reduction(&&: localSorted) 
            for(int i=0;i<arr.size()-1;i+=2){
                if(arr[i]> arr[i+1]){
                    swap(arr[i], arr[i+1]);
                    localSorted = false;
                }
            }
        #pragma omp parallel for reduction(&&: localSorted) 
        
        for(int i=1; i<arr.size();i+=2) {
                if(arr[i] > arr[i+1]){
                    swap(arr[i], arr[i+1]);
                    localSorted = false;
                }
            }
        
        sorted = localSorted;
        
    }
}

void merge(vector<int> & arr, int low, int mid, int high){
    int n1 = mid - low + 1;
    int n2 = high - mid;
    vector<int>arr1(n1);
    vector<int>arr2(n2);
    for(int i=0;i<n1;i++){
        arr1[i] = arr[i+low];

    }
    for(int i=0;i<n2;i++){
        arr2[i] = arr[mid+1+i];
    }
    int i=0;
    int j=0;
    int k = low;
    while( i< n1 && j < n2){
        if(arr1[i]< arr2[j]){
            arr[k] = arr1[i];
            i++; 
        }
        else{
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }
    while(i<n1) {
        arr[k] = arr1[i];
        i++;
        k++;
    }
    while(j < n2) {
        arr[k] = arr2[j];
        j++;
        k++;
    }
}
void sequentialMergeSort(vector<int> &arr, int low, int high){
    if(low < high){
        int mid = (low + high) /2;
        sequentialMergeSort(arr, low, mid);
        sequentialMergeSort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}
void parallelMergeSort(vector<int> &arr, int low, int high, int depth = 0){
    if(low < high){
        int mid = (low + high) / 2;
        if(depth < N_CPU_CORES){
            #pragma omp parallel sections 
            {
                #pragma omp section 
                {
                    parallelMergeSort(arr, low, mid, depth+1);

                }
                #pragma omp section 
                {
                    parallelMergeSort(arr, mid+1, high, depth + 1);
                }

            }
            
        }
        else {
            parallelMergeSort(arr, low, mid, depth+1);
            parallelMergeSort(arr, mid+1, high, depth+1);
        }
        merge(arr, low, mid, high);
        
    }

}
vector<int> generateRandomArray(int size){
    vector<int> arr(size);
    for(int i=0;i<size; i++){
        arr[i] = rand() % 100 + 1;
    }
    return arr;
}
int main(int argc, char * argv[]){
    vector<int> arr1 = generateRandomArray(TEST_ARR_SIZE);
    vector<int>arr1_copy = arr1;
    cout<<"Executing sequential bubble sort..\n";
    double start = omp_get_wtime();
    sequentialBubbleSort(arr1);
    auto end = omp_get_wtime();
   

    cout<<"Executing Parallel Bubble sort.. \n";
    auto s1 = omp_get_wtime();
    parallelBubbleSort(arr1_copy);
    auto e1 = omp_get_wtime();
   

    vector<int> arr2 = generateRandomArray(TEST_ARR_SIZE);
    vector<int>arr2_copy = arr2;
    cout<<"Executing sequential merge sort..\n";
    auto s2 = omp_get_wtime();
    sequentialMergeSort(arr2, 0, arr2.size()-1);
    auto e2 = omp_get_wtime();
   

    cout<<"Executing Parallel Merge sort.. \n";
    auto s3 = omp_get_wtime();
    parallelMergeSort(arr2_copy, 0 , arr2_copy.size()-1);
    auto e3 = omp_get_wtime();
  
    
    cout<<"Execution time for Sequential Bubble Sort: "<< (end - start)* 1000<<"ms"<<endl;
    cout<<"Execution time for Parallel Bubble Sort: "<< (e1 - s1) * 1000 <<"ms"<<endl;
    cout<<"Parallel Bubble sort is faster than sequential by: "<<
    ((end - start) - (e1-s1))* 1000<<"ms"<<endl;
    cout<<"Execution time for Sequential Merge Sort: "<< (e2 - s2) * 1000<<"ms"<<endl;
    cout<<"Execution time for Parallel Merge Sort: "<< (e3-s3) * 1000 <<"ms"<<endl;
    cout<<"Parallel Merge sort is faster than sequential by: "<<
    ((e2 - s2) - (e3-s3)) * 1000<<"ms"<<endl;
    return 0;

}
