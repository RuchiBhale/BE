//Reference: @teabytes (https://github.com/teabytes)
#include <omp.h>
#include <bits/stdc++.h>
using namespace std;

class Graph{
    int nodes;
    vector<vector<int>> adj;
    vector<bool>visited;

    public:
    Graph(int n){
        nodes = n;
        adj.resize(n);
        visited.resize(n,false);
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void resetvisited(){
        fill(visited.begin(),visited.end(), false);
    }
    void sequentialBFS(int start){
        queue<int>q;
        q.push(start);
        visited[start] = true;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            cout<<node<<" ";
            for(int neighbour: adj[node]){
                if(!visited[neighbour]){
                    q.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }
    }
    void sequentialDFS(int start){
        stack<int>s;
        visited[start] = true;
        s.push(start);
        while(!s.empty()){
            int node = s.top();
            s.pop();
            cout<<node<<" ";
            for(auto it = adj[node].rbegin(); it != adj[node].rend(); it++){
                int neighbour = *it;
                if(!visited[neighbour]){
                    visited[neighbour] = true;
                    s.push(neighbour);
                }
            }
        }
    }
    void parallelBFS(int start){
        queue<int>q;
        visited[start] = true;
        q.push(start);
        while(!q.empty()){
            int levelsize = q.size();
            vector<int>currentLevel;
            for(int i=0;i<levelsize;i++){
                int node = q.front();
                q.pop();
                cout<<node<<" ";
                currentLevel.push_back(node);
            }
            #pragma omp parallel for // parallel traversal of neighbors
            for(int i=0;i<currentLevel.size();i++){
                int node = currentLevel[i];
                for(int neighbour: adj[node]){
                    if(!visited[neighbour]){
                        #pragma omp critical // ensure thread-safe access to visited[]
                        {
                            if(!visited[neighbour]){
                                visited[neighbour] = true;
                                q.push(neighbour);
                            }
                        }
                    }
                }
            }
        }
    }
    void parallelDFSUtil(int node){
        if(visited[node]){ // if already visited, skip
            return;
        }
        visited[node] = true;
        cout<<node<<" ";
        #pragma omp parallel for // parallel traversal of neigbors
        for(int i=0;i<adj[node].size(); i++){
            int u = adj[node][i];
            #pragma omp critical
            {
                if(!visited[u]){
                    #pragma omp task
                    parallelDFSUtil(u);
                }
            }

        }
    }
    void parallelDFS(int start){
        #pragma omp parallel  // parallel section to process each neighbor of start node
        {
            #pragma omp single // ensures only one thread starts the root DFS
            {
                parallelDFSUtil(start);
            }
        }
    }

};
int main(){
    int nodes, edges;
    cout<<"\nEnter no of nodes & edges (N E): ";
    cin>>nodes>>edges;
    Graph g(nodes);
    cout<<"Enter edges (u v): "<<endl;
    for(int i=0;i<edges;i++){
        int u, v;
        cout<<"Edge "<<i + 1 <<": ";
        cin>>u>>v;
        g.addEdge(u,v);
    }
    int src;
    cout<<"\nEnter the starting node for DFS and BFS: ";
    cin>>src;
    cout<<"Executing sequential BFS..\n";
    double start = omp_get_wtime();
    g.resetvisited();
    g.sequentialBFS(src);
    double end = omp_get_wtime();
    cout<<"\nSequential BFS time: "<<(end - start) * 1000<<"ms\n";

    cout<<"Executing Sequential DFS..\n";
    start = omp_get_wtime();
    g.resetvisited();
    g.sequentialDFS(src);
    end = omp_get_wtime();
    cout<<"\nSequential DFS Execution time: "<<(end - start)* 1000<<"ms\n";

    cout<<"Executing Parallel BFS..\n";
    start = omp_get_wtime();
    g.resetvisited();
    g.parallelBFS(src);
    end = omp_get_wtime();
    cout<<"\nParallel BFS Execution time: "<<(end - start) * 1000<<"ms\n";

    cout<<"Executing Parallel DFS..\n";
    start = omp_get_wtime();
    g.resetvisited();
    g.parallelDFS(src);
    end = omp_get_wtime();
    cout<<"\nParallel DFS Execution time: "<<(end - start) * 1000<<"ms\n";

    return 0;

}
