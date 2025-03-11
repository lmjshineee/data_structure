#include <iostream>

using namespace std;
typedef int ElemType;

typedef struct BSTNode{
    ElemType data;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BiTree;

BSTNode *BST_Search(BiTree T,ElemType key){
    while(T&&key!=T->data){
        if(key<T->data){
            T=T->lchild;
        }else{
            T=T->rchild;
        }
    }
    return T;
}

BSTNode *BST_Search_Recursion(BiTree T,ElemType key){
    if (T){
        if(key==T->data){
            return T;
        }else if(key<T->data){
            return BST_Search(T->lchild,key);
        }else{
            return BST_Search(T->rchild,key);
        }
    }else{
        return NULL;
    }
}

bool BST_Insert(BiTree &T,ElemType key){
    if(!T){
        T=new BSTNode;
        T->data=key;
        T->lchild=T->rchild=NULL;
        return true;
    }
    if(key==T->data){
        return false;
    }else if(key<T->data){
        BST_Insert(T->lchild,key);
    }else{
        BST_Insert(T->rchild,key);
    }
    return false;
}

void Create_BST(BiTree &T,ElemType str[],int n){
    T=NULL;
    for(int i=0;i<n;i++){
        BST_Insert(T,str[i]);
    }
}

bool Delete_BSTNode(BiTree &T,BSTNode *p){
    BSTNode *q,*s;
    if(!p->rchild){ //右子树空 用左子女填补
        q=p;
        p=p->lchild;
        delete q;
    }else if(!p->lchild){ // 左子树空，用右子女填补
        q=p;
        p=p->rchild;
        delete q;
    }else{ // 左右子树均不空，用右子树的中序前驱填补
        q=p;
        s=p->lchild;
        while(s->rchild){
            q=s;
            s=s->rchild;
        }
        p->data=s->data;
        if(q!=p){
            q->rchild=s->lchild;
        }else{
            q->lchild=s->lchild;
        }
        delete s;
    }
    return true;

}

void InOrderTraverse(BiTree T){
    if(T){
        InOrderTraverse(T->lchild);
        cout<<T->data<<" ";
        InOrderTraverse(T->rchild);
    }
}

int main(){
    BiTree T;
    ElemType key;
    T=NULL;
    // Insert some nodes into the binary search tree
    BST_Insert(T,10);
    BST_Insert(T,20);
    BST_Insert(T,30);
    BST_Insert(T,40);
    BST_Insert(T,50);
    BST_Insert(T,25);
    BST_Insert(T,35);
    // Print the binary search tree
    cout<<"The binary search tree is:"<<endl;
    InOrderTraverse(T);
    // Search for a node in the binary search tree
    key=30;
    BSTNode *p=BST_Search(T, key);
    if(p){
        cout<<"\nThe node "<<key<<" is found in the binary search tree."<<endl;
    }else{
        cout<<"\nThe node "<<key<<" is not found in the binary search tree."<<endl;
    }

    key=20;
    p=BST_Search_Recursion(T, key);
    if(p){
        cout<<"\nThe node "<<key<<" is found in the binary search tree."<<endl;
    }else{
        cout<<"\nThe node "<<key<<" is not found in the binary search tree."<<endl;
    }
    
    return 0;
}