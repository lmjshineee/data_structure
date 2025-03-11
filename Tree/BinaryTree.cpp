#include<iostream>
#include<cmath>
#include<stack>
#include<queue>
using namespace std;
typedef int ElemType;

typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

bool InitTree(BiTree &T){
    T=NULL;
    return true;
}

//二叉树节点的遍历 O(n)
void visit(BiTree T){
    cout<<T->data<<endl;
}

//01 先序遍历---NLR
void PreOrder(BiTree T){
    if(T!=NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
//02 中序遍历---LNR
void InOrder(BiTree T){
    if(T!=NULL){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}
//03 后序遍历---LRN
void PostOrder(BiTree T){
    if(T!=NULL){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}
//非递归方法遍历
void PreOrder2(BiTree T){
    stack<BiTree> s;
    BiTree p=T;
    while(p!=NULL||!s.empty()){
        if(p!=NULL){
            visit(p);
            s.push(p);
            p=p->lchild;
        }else{
            p=s.top();
            s.pop();
            p=p->rchild;
        }
    }
}
void InOrder2(BiTree T){
    stack<BiTree> s;
    BiTree p=T;
    while(p!=NULL||!s.empty()){
        if(p!=NULL){
            s.push(p);
            p=p->lchild;
        }else{
            p=s.top();
            s.pop();
            visit(p);
            p=p->rchild;
        }
    }
}
void PostOrder2(BiTree T){
    stack<BiTree> s;
    BiTree p=T;
    BiTree r=NULL;
    while(p!=NULL||!s.empty()){
        if(p!=NULL){
            s.push(p);
            p=p->lchild;
        }else{
            p=s.top();
            if(p->rchild!=NULL&&p->rchild!=r){
                p=p->rchild;
                s.push(p);
                p=p->lchild;
            }else{
                p=s.top();
                s.pop();
                visit(p);
                r=p;
                p=NULL;
            }
        }
    }
}



//由前序和中序遍历构造二叉树
bool Build_Pre_In(BiTree T,ElemType *pre,ElemType *in,int n){
    if(n<=0){
        return false;
    }
    T->data=pre[0];
    int k=0;
    while(in[k]!=pre[0]){
        k++;
    }
    Build_Pre_In(T->lchild,pre+1,in,k);
    Build_Pre_In(T->rchild,pre+k+1,in+k+1,n-k-1);
    return true;
}

int main(){
    BiTree T;
    InitTree(T);
    ElemType a[]={1,2,3,4,5,6,7,8,9,10};
    ElemType b[]={10,9,8,7,6,5,4,3,2,1};
    if(Build_Pre_In(T,a,b,20)){
        PreOrder(T);
    }
    cout<<endl;
    InOrder(T);
    cout<<endl;
    PostOrder(T);
    cout<<endl;
    return 0;
}