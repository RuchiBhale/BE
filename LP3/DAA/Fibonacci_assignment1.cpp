#include <iostream>
using namespace std;

int fibonacci_recur(int i){
    if(i==0) return 0;
    if(i==1) return 1;
    return fibonacci_recur(i-1) + fibonacci_recur(i-2);
}

void print_fibonacci(int n){
    for(int i=0;i<n;i++){
        int ans = fibonacci_recur(i);
        cout<<ans<<" , ";
    }
    
}
void fibonacci_iterative(int n){
    int a = 0;
    int b = 1;
    int c;
    cout<<a<<" , "<<b<<" , ";
    for(int i = 0;i < n-2;i++){
        c = a + b;
        cout<<c<<" , ";
        a = b;
        b = c;
        

    }


}
int main(){
    int ch;
    while(true){
        int n;
        cout<<endl;
        cout<<"\nEnter the value of n: ";
        cin>>n;
        cout<<"1. Recursive\n2. Iterative\n3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>ch;
        switch(ch){
            case 1: 
                print_fibonacci(n);
                break;
            case 2:
                fibonacci_iterative(n);
                break;
            case 3: 
                exit(0);
                break;
        }

    }
}
