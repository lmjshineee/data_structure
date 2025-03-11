// Description: ˳��洢������
#include<iostream>
#include<cmath>
using namespace std;
typedef int ElemType;
#define MaxSize 255

typedef struct{
    ElemType data[MaxSize];
    int n;
}SqTree;

//�����ն�����
void InitTree(SqTree &T){
    for(int i=0;i<MaxSize;i++)
        T.T[i]=0;
    T.n=0;
}
//˳��洢������ �����������
int father(int A[],int i){
    if(i>=0&&A[i]!=0)
        return floor(i/2);
    else
        return -1;
}
int LCA(int A[],int i,int j){
    int f_i=i;
    int f_j=j;
    while(f_i!=f_j){
        if(f_i>f_j)
            f_i=father(A,f_i);
        else
            f_j=father(A,f_j);
    }
    return f_i;
}

ElemType comm_Ancestor(SqTree T,int i,int j){
    if(i==j)
        return T[i];
    if(i>j)
        return comm_Ancestor(T,floor((i-1)/2),j);
    if(i<j)
        return comm_Ancestor(T,i,floor((j-1)/2));
}

int main(){


    return 0;
}