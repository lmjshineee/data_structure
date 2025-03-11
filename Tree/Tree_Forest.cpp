#include <iostream>
using namespace std;
typedef int ElemType;

//
#define MaxTreeSize 100
typedef struct{
    ElemType data;
    int parent;
}PTNode;
typedef struct{
    PTNode nodes[MaxTreeSize];
    int n;
}PTree;


//
typedef struct{
    ElemType data;
    int child[MaxTreeSize];
    int n;
}CTNode;
typedef struct{
    CTNode nodes[MaxTreeSize];
    int n;
}CTree;

//
typedef struct CSNode{
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

//
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//
// bool TreeToForst()


//
void InTravelTree(CSTree T){
    if(T){
        InTravelTree(T->firstchild);
        cout<<T->data<<' ';
        InTravelTree(T->nextsibling);
    }
}

void PreTravelTree(CSTree T){
    if(T){
        cout<<T->data<<' ';
        PreTravelTree(T->firstchild);
        PreTravelTree(T->nextsibling);
    }
}


//
int main(){
    CSTree T;
    CSTree T1=new CSNode;
    CSTree T2=new CSNode;
    CSTree T3=new CSNode;
    CSTree T4=new CSNode;
    CSTree T5=new CSNode;
    T1->data=1;
    T2->data=2;
    T3->data=3;
    T4->data=4;
    T5->data=5;
    T1->firstchild=T2;
    T1->nextsibling=T3;
    T2->firstchild=T4;
    T2->nextsibling=T5;
    T3->firstchild=NULL;
    T3->nextsibling=NULL;
    T4->firstchild=NULL;
    T4->nextsibling=NULL;
    T5->firstchild=NULL;
    T5->nextsibling=NULL;
    T=T1;
    cout<<"In order traversal of the tree: ";
    InTravelTree(T);
    cout<<endl;
    cout<<"Pre order traversal of the tree: ";
    PreTravelTree(T);
    cout<<endl;
    return 0;
}