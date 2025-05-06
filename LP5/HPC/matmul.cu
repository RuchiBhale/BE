#include <bits/stdc++.h>
#include <cuda.h>
using namespace std;
using namespace std::chrono;
#define block_size 16
void initialize(int *arr, int rows,int cols){
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      arr[i*cols+j] = rand()%100+1;
    }
  }
}
void print(int *arr,int rows,int cols){
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      cout<<arr[i*cols+j]<<" ";
    }
  }
}
void matmul(int *a, int *b,int *c, int common,int c_rows,int c_cols){
  for(int i=0;i<c_rows;i++){
    for(int j=0;j<c_cols;j++){
      int sum=0;
      for(int k=0;k<common;k++){
        sum+= a[i*common+k]*b[k*c_cols+j];

      }
      c[i*c_cols+j] = sum;

    }
  }
}
__global__ void gpu_mul(int *a, int *b,int *c, int common, int c_rows, int c_cols){
  int rows = blockIdx.y * blockDim.y + threadIdx.y;
  int cols = blockIdx.x * blockDim.x +threadIdx.x;
  if(rows<c_rows && cols < c_cols){
    int sum =0;
    for(int j=0;j<common;j++){
      sum+=a[rows*common+j]*b[j*c_cols+cols];
    }
    c[rows*c_cols+cols] = sum;
  }
}
int main(){
  int *cpu_a,*cpu_b,*cpu_c;
  int a_rows, a_cols, b_rows,b_cols;
  cout<<"\nEnter the no of rows in A: ";
  cin>>a_rows;
  cout<<"\nEnter the number of cols in A: ";
  cin>>a_cols;
  cout<<"\nEnter B rows: ";
  cin>> b_rows;
  cout<<"\nEnter B cols: ";
  cin>>b_cols;
  int a_size = a_rows*a_cols;
  int b_size = b_rows *b_cols;
  int c_size = a_rows * b_cols;
  cpu_a = new int[a_size];
  cpu_b = new int[b_size];
  cpu_c = new int[c_size];
  initialize(cpu_a, a_rows,a_cols);
  initialize(cpu_b, b_rows,b_cols);
  int *gpu_a, *gpu_b, *gpu_c;
  int vectorbytes_a = a_size *sizeof(int);
  int vectorbytes_b = b_size *sizeof(int);
  int vectorbytes_c = c_size * sizeof(int);

  cudaMalloc(&gpu_a, vectorbytes_a);
  cudaMalloc(&gpu_b, vectorbytes_b);
  cudaMalloc(&gpu_c, vectorbytes_c);

  cout<<"\nMatrix A: ";
  print(cpu_a,a_rows, a_cols);
  cout<<"\nMatrix B: ";
  print(cpu_b, b_rows, b_cols);

  cudaMemcpy(gpu_a, cpu_a,vectorbytes_a, cudaMemcpyHostToDevice);
  cudaMemcpy(gpu_b, cpu_b, vectorbytes_b, cudaMemcpyHostToDevice);
  dim3 dimblock(block_size*block_size);
  dim3 gridDim ((a_rows+block_size-1)/ block_size, (b_cols+block_size-1)/block_size);

  auto start= high_resolution_clock::now();
  gpu_mul<<<gridDim, dimblock>>>(gpu_a,gpu_b,gpu_c,a_cols,a_rows,b_cols);
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<microseconds> (end-start);
  cudaMemcpy(cpu_c,gpu_c, vectorbytes_c, cudaMemcpyDeviceToHost);
  cout<<"gpu Multiplication is: "<<endl;
  print(cpu_c, a_rows,b_cols);
  cout<<"\nGPU time: "<<duration.count()<<" microseconds\n"<<endl;

  cudaFree(gpu_a);cudaFree(gpu_b);cudaFree(gpu_c);
  start = high_resolution_clock::now();
  matmul(cpu_a,cpu_b,cpu_c,a_cols,a_rows,b_cols);
  end = high_resolution_clock::now();
  duration = duration_cast<microseconds>(end-start);
  cout<<"CPU Multiplication: "<<endl;
  print(cpu_c, a_rows, b_cols);
  cout<<"\nCPU time: "<<duration.count()<<" microseconds\n";

  free(cpu_a);free(cpu_b);free(cpu_c);
  return 0;


}
