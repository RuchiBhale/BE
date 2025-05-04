#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
#define TEST_ARR_SIZE 500000
void maxpar(vector<int> arr){
    int maxelement = INT_MIN;
    double start = omp_get_wtime();
    #pragma omp parallel for reduction(max: maxelement)
    for(int i = 0; i<arr.size();i++){   
        if(arr[i] > maxelement){
            maxelement = arr[i];
        }
    }
    double end = omp_get_wtime();
    cout<<"Parallel Max Reduction time: "<<(end-start) * 1000<<"ms"<<endl;
    cout<<"Max: "<<maxelement<<endl;


}
void maxseq( vector<int>arr){
    int maxele = INT_MIN;
    double start = omp_get_wtime();
    for(int i=0;i<arr.size();i++){
        if(arr[i] > maxele){
            maxele = arr[i];
        }
    }
    double end = omp_get_wtime();
    cout<<"Sequential Max Reduction time:  "<<(end-start) * 1000<<"ms"<<endl;
    cout<<"Max: "<<maxele<<endl;

}
void minseq(vector<int> &arr){

    int minele = INT_MAX;
    double start = omp_get_wtime();
    for(int i =0 ;i< arr.size(); i++){
        if(arr[i] < minele){
            minele = arr[i];
        }
    }
    double end = omp_get_wtime();
    cout<<"Sequential min reduction time: "<<(end-start)*1000<<"ms"<<endl;
    cout<<"Sequrntial min: "<<minele<<endl;
}
void minpar(vector<int> &arr){
    int minelement = INT_MAX;
    double start = omp_get_wtime();
    #pragma omp parallel for reduction(min: minelement)
    for(int i=0;i<arr.size();i++){
        if(arr[i] < minelement){
            minelement =arr[i];
        }
    }
    double end = omp_get_wtime();
    cout<<"Parallel min reduction time: "<<(end-start) *1000<<"ms"<<endl;
    cout<<"Parallel min is: "<<minelement<<endl;
}
void sumseq(vector<int>&arr){
    int sum=0;
    double start = omp_get_wtime();
    for(int i=0;i<arr.size();i++){
        sum = sum + arr[i];

    }
    double end = omp_get_wtime();
    cout<<"Sequential Sum execution time is: "<< (end - start) * 1000<<"ms\n";
    cout<<"Sequential sum is: "<<sum<<endl;
}
void sumpar(vector<int> &arr){
    int sum = 0; 
    double start = omp_get_wtime();
    #pragma omp parallel for reduction(+: sum)
    for(int i=0;i<arr.size();i++){
        sum = sum + arr[i];
    }
    double end = omp_get_wtime();
    cout<<"Parallel sum reduction time: "<<(end - start) * 1000<<"ms\n";
    cout<<"Parallel sum is: "<<sum<<endl;
}
void avgseq(vector<int> &arr){
    int sum = 0;
    double start = omp_get_wtime();
    for(int i=0;i<arr.size();i++){
        sum+=arr[i];
    }
    double average = sum/arr.size();
    double end = omp_get_wtime();
    cout<<"Sequential average execution time is: "<<(end-start) *1000<<"ms\n";
    cout<<"Sequential average is: "<<average<<endl;
}
void avgpar(vector<int> &arr){
    int sum = 0;
    double start = omp_get_wtime();
    #pragma omp parallel for reduction(+: sum)
    for(int i=0;i<arr.size();i++){
        sum+=arr[i];
    }
    double average = sum/arr.size();
    double end = omp_get_wtime();
    cout<<"Parallel average execution time is: "<<(end-start) *1000<<"ms\n";
    cout<<"Parallel average is: "<<average<<endl;
}
int main(int argc, char* argv[]){
    vector<int>arr(TEST_ARR_SIZE);
    for(int i=0; i<TEST_ARR_SIZE; i++){
        arr[i] = rand() %1000 +1;

    }

    cout<<"Calculating maximum..\n";
    maxseq(arr);
    maxpar(arr);
    cout<<"Calculating minimum..\n";
    minseq(arr);
    minpar(arr);
    cout<<"Calculating sum..\n";
    sumseq(arr);
    sumpar(arr);
    cout<<"Calculating average\n";
    avgseq(arr);
    avgpar(arr);

    return 0;
}