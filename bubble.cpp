#include<iostream>
using namespace std;
#include<bits/stdc++.h>
#include<omp.h>


void bubble(vector<int>a){

    for(int i =0 ; i<a.size() ;i++){
        int first = i%2;
        #pragma omp parallel shared(a,first)
        for(int j = i ; j<a.size()-1 ;j=j+2){
           
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }cout<<endl;

}
int main(){
    int n;
    cout<<"Enter Number of Elements : ";
    cin>>n;

    vector<int>a(n);;

    for(int i = 0 ; i<n ;i++){
        cin>>a[i];
    }
    

    for(auto x : a){
        cout<<x<<" ";
    }
}