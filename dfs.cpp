#include<iostream>
using namespace std;
#include<omp.h>
#include<bits/stdc++.h>

void dfs(vector<vector<int>>&node,int start,vector<bool>&visited){
    bool ex = 0;
    #pragma omp critical
    {
        if(visited[start]){
            ex = 1;
        }
        else{
            visited[start] = 1;
            cout<<start<<" ";
        }
    }
    if(ex){
        return;
    }
    
    for(auto x : node[start]){
        #pragma omp task firstprivate(start)
        dfs(node,x,visited);
    }
    #pragma omp taskwait
}
int main(){
    int n = 0;
    cout<<"Enter Number of Nodes : ";
    cin>>n;
    vector<vector<int>>node(n);
    vector<bool>visited(n,0);

    for(int i = 0 ; i<n ;i++){
        cout<<"Enter number of connected node to "<<i<<": ";
        int k = 0;
        cin>>k;

        while(k){
            int v =0;
            cin>>v;
            node[i].push_back(v);
            k--;
        }
        cout<<endl;
        
    }

    #pragma omp parallel
        #pragma omp single
            dfs(node,0,visited);
}

// 5
// 3
// 1 2 3
// 2
// 1 2
// 3
// 0 1 4
// 1
// 0
// 1
// 2