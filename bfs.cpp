#include <iostream>
using namespace std;
#include <bits/stdc++.h>
#include<omp.h>

class node
{
public:
    node *left, *right;
    int data = 0;
    node()
    {
        left = right = NULL;
    }
};

void ins(node *&root, int data)
{
    if (root == NULL)
    {
        root = new node();
        root->data = data;
        return;
    }
    queue<node *> q;
    q.push(root);

    while (q.size())
    {
        node *cur = q.front();

            if (cur->left == NULL)
            {
                cur->left = new node();
                cur->left->data = data;
                return;
            }
            else
            {
                q.push(cur->left);
            }

        
            if (cur->right == NULL)
            {
                cur->right = new node();
                cur->right->data = data;
                return;
            }
            else
            {
                q.push(cur->right);
            }
            q.pop();
            
    }
}

void bfs(node * root){
    if(root==NULL){
        return;
    }
    queue<node *>q;
    q.push(root);

    while(!q.empty()){
        
        int s = q.size();
        
#pragma omp parallel for
        for(int i = 0 ; i<s ; i++){
            node *k = NULL;

#pragma omp critical
            {
                // cout<<"{"<<omp_get_thread_num<<"}";
                k = q.front();
                q.pop();
                cout<<k->data<<" ";
                
            }
            
#pragma omp critical
            {
                // cout<<"{"<<omp_get_thread_num<<"}";
                if(k->left!=NULL){
                    q.push(k->left);
                }
                if(k->right!=NULL){
                    q.push(k->right);
                }
            }
            
            
        }
        cout<<omp_get_thread_num<<endl;
    }
    // return;
}


int main()
{
    node *k = NULL;
    bool y = 1;
    cout << "Do you want to insert node Y/N" << endl;
    char c = '1';
    cin >> c;
    if (c != 'Y'){
        y = 0;
    }

    while (y){
        int d = 0;
        cout << "Enter Data : ";
        cin >> d;
        ins(k, d);

        cout << "Do you want to insert node Y/N" << endl;
        c = '1';
        cin >> c;
        if (c != 'Y')
        {
            y = 0;
        }
    }
    bfs(k); cout<<endl<<endl;
    
}