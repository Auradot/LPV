#include<iostream>
using namespace std;
#include<bits/stdc++.h>

void maxi(vector<int>a){
    int maxim = INT_MIN;

    #pragma omp parallel for reduction(max:maxim)
    for(int i = 0 ; i<a.size() ;i++){
        if(a[i]>maxim){
            maxim = a[i];
        }
    }
    cout<<"Maximum Value is : "<<maxim<<endl;
}

void mini(vector<int>a){
    int minim = INT_MAX;

    #pragma omp parallel for reduction(min:minim)
    for(int i = 0 ; i<a.size() ;i++){
        if(a[i]<minim){
            minim = a[i];
        }
    }
    cout<<"Minimum Value is : "<<minim<<endl;
}

void sum_reduction(vector<int>a){
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0 ; i<a.size() ;i++){
        sum = sum + a[i];
    }
    cout<<"Sum Value is : "<<sum<<endl;
}

void average_reduction(vector<int>a){
    double sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0 ; i<a.size() ;i++){
        sum = sum + a[i];
    }
    // sum = double(double(sum)/double(a.size()));
    cout<<"Average Value is : "<<static_cast<double>(sum) / a.size()<<endl;
}

int main(){
    vector<int>a;
    int n = 0;
    cout<<"Enter number of element : ";
    cin>>n;

    for(int i = 0 ; i<n ;i++){
        int k =0;
        cin>>k;
        a.push_back(k);
        k--;
    
    }
    maxi(a);
    mini(a);
    sum_reduction(a);
    average_reduction(a);
}