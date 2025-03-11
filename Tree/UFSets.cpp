#include<iostream>
using namespace std;

#define SIZE 100

void Initial(int S[],int n){
    for(int i=0; i<n; i++)
        S[i]=-1;
}

int Find_0(int S[],int x){
    while(S[x]>=0)
        x=S[x];
    return x;
}

void Union_1(int S[],int root1,int root2){
    if(root1==root2) return;
    S[root2]=root1;
}
void Union(int S[],int root1,int root2){
    if(root1==root2) return;
    if(S[root1]>S[root2]){
        S[root2]+=S[root1];
        S[root1]=root2;
    }else{
        S[root1]+=S[root2];
        S[root2]=root1;
    }
}

int Find(int S[],int x){
    int root=x;
    while(S[root]>=0)
        root=S[root];
    while(x!=root){
        int parent=S[x];
        S[x]=root;
        x=parent;
    }
    return root;
}

int main(){
    int S[SIZE];
    Initial(S,5);
    Union(S,Find(S,0),Find(S,1));
    Union(S,Find(S,2),Find(S,3));
    
    return 0;
}