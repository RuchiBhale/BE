#include <bits/stdc++.h>
#include <cuda.h>
using namespace std;
using namespace std::chrono;
#define block_size 16
void initialize(int *arr, int n){
  for(int i=0;i<n;i++){
    arr[i] = rand()%100+1;
  }
}
void print(int *arr, int n){
  for(int i=0;i<n;i++){
    cout<<arr[i]<<" ";
  }
  cout<<endl;
}
void cpu_sum(int *a, int *b, int *c,int n){
  for(int i=0;i<n;i++){
    c[i] = a[i] + b[i];
  }
}
__global__ void gpu_sum(int *a,int*b,int*c,int n){
  int id = blockIdx.x *blockDim.x + threadIdx.x;
  if(id<n){
    c[id] = a[id] + b[id];
  }
}
int main(){
  int n;
  cout<<"Enter the size: ";
  cin>>n;
  int *cpu_a,*cpu_b,*cpu_c;
  int *gpu_a,*gpu_b,*gpu_c;
  cpu_a = new int[n];
  cpu_b = new int[n];
  cpu_c = new int[n];
  int vectorbytes = n*sizeof(int);

  initialize(cpu_a, n);
  initialize(cpu_b,n);
  cout<<"Vector A: ";
  print(cpu_a,n);
  cout<<"Vector B: ";
  print(cpu_b,n);
  cudaMalloc(&gpu_a, vectorbytes);
  cudaMalloc(&gpu_b, vectorbytes);
  cudaMalloc(&gpu_c, vectorbytes);
  cudaMemcpy(gpu_a, cpu_a, vectorbytes, cudaMemcpyHostToDevice);
  cudaMemcpy(gpu_b, cpu_b, vectorbytes, cudaMemcpyHostToDevice);
  dim3 dimblock(block_size);
  dim3 gridDim((n+block_size-1)/block_size);
  auto start = high_resolution_clock::now();
  gpu_sum<<<gridDim, dimblock>>>(gpu_a,gpu_b,gpu_c,n);
  auto end = high_resolution_clock::now();
  cudaMemcpy(cpu_c, gpu_c,vectorbytes,cudaMemcpyDeviceToHost);
  cout<<"GPU sum: "<<endl;
  print(cpu_c,n);
  auto duration = duration_cast<microseconds>(end-start);
  cout<<"GPU time: "<<duration.count()<<" microseconds\n";

  cudaFree(gpu_a); cudaFree(gpu_b); cudaFree(gpu_c);
  start = high_resolution_clock::now();
  cpu_sum(cpu_a,cpu_b,cpu_c,n);
  end = high_resolution_clock::now();
  duration = duration_cast<microseconds>(end-start);
  cout<<"CPU sum: "<<endl;
  print(cpu_c,n);
  cout<<"CPU time is: "<<duration.count()<<" microseconds\n";
  free(cpu_a); free(cpu_b); free(cpu_c);
  return 0;
}
