#include <iostream>
using namespace std;
typedef int ElemType;

typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
}ThreadNode,*ThreadTree;


//二叉树的线索化
void InThread(ThreadTree &p, ThreadTree &pre){
    if(p != NULL){
        InThread(p->lchild, pre);
        if(p->lchild == NULL){
            p->ltag = 1;
            p->lchild = pre;
        }
        if(pre != NULL && pre->rchild == NULL){
            pre->rtag = 1;
            pre->rchild = p;
        }
        pre = p;
        InThread(p->rchild, pre);
    }
}

void CreateInThread(ThreadTree T){
    ThreadTree pre = NULL;
    if(T != NULL){
        InThread(T, pre);
        pre->rchild = NULL; //处理最后一个节点
        pre->rtag = 1;
    }
}

void PreThread(ThreadTree &p, ThreadTree &pre){
    if(p != NULL){
        if(p->lchild == NULL){
            p->ltag = 1;
            p->lchild = pre;
        }
        if(pre != NULL && pre->rchild == NULL){
            pre->rtag = 1;
            pre->rchild = p;
        }
        pre = p;
        if(p->ltag == 0){
            PreThread(p->lchild, pre);
        }
        if(p->rtag == 0){
            PreThread(p->rchild, pre);
        }
    }
}
void CreatePreThread(ThreadTree T){
    ThreadTree pre = NULL;
    if(T != NULL){
        PreThread(T, pre);
        pre->rchild = NULL; //处理最后一个节点
        pre->rtag = 1;
    }
}


//
typedef struct PostThreadNode{
    ElemType data;
    struct PostThreadNode *lchild, *rchild, *parent;
    int ltag, rtag;
}PostThreadNode,*PostThreadTree;


void PostThread(ThreadTree &p, ThreadTree &pre){
    if(p != NULL){
        PostThread(p->lchild, pre);
        PostThread(p->rchild, pre);
        if(p->lchild == NULL){
            p->ltag = 1;
            p->lchild = pre;
        }
        if(pre != NULL && pre->rchild == NULL){
            pre->rtag = 1;
            pre->rchild = p;
        }
        pre = p;
    }
}
void CreatePostThread(ThreadTree T){
    ThreadTree pre = NULL;
    if(T != NULL){
        PostThread(T, pre);
        pre->rchild = NULL; //处理最后一个节点
        pre->rtag = 1;
    }
}


//中序线索二叉树的中序遍历
//01
ThreadNode *FirstNode(ThreadNode *p){
    while(p->ltag == 0){
        p = p->lchild;
    }
    return p;
}
ThreadNode *NextNode(ThreadNode *p){
    if(p->rtag == 0){
        return FirstNode(p->rchild);
    }else{
        return p->rchild;
    }
}

void InOrder(ThreadTree T){
    for(ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p))
        cout<<p->data;
    cout<<endl;
}
void PreOrder(ThreadTree T){
    ThreadNode *p = T;
    while(p != NULL){
        cout<<p->data;
        if(p->ltag == 0){
            p = p->lchild;
        }else if(p->rtag == 0){
            p = p->rchild;
        }else{
            while(p->rtag == 1){
                p = p->rchild;
            }
            p = p->rchild;
        }
    }
    cout<<endl;
}

void PostOrder(ThreadTree T){
    ThreadNode *p = T;
    while(p->ltag == 0 || p->rtag == 0){
        if(p->ltag == 0){
            p = p->lchild;
        }else if(p->rtag == 0){
            p = p->rchild;
        }
    }
    cout<<p->data;
    while(p != T){
        if(p == p->rchild){
            p = p->rchild;
        }else{
            p = p->rchild;
            while(p->ltag == 0 || p->rtag == 0){
                if(p->ltag == 0){
                    p = p->lchild;
                }else if(p->rtag == 0){
                    p = p->rchild;
                }
            }
        }
        cout<<p->data;
    }
    cout<<endl;
}

//测试
int main(){
    ThreadTree T = new ThreadNode;
    T->data = 1;
    T->lchild = new ThreadNode;
    T->lchild->data = 2;
    T->lchild->lchild = new ThreadNode;
    T->lchild->lchild->data = 4;
    T->lchild->rchild = new ThreadNode;
    T->lchild->rchild->data = 5;
    T->rchild = new ThreadNode;
    T->rchild->data = 3;
    T->rchild->lchild = new ThreadNode;
    T->rchild->lchild->data = 6;
    T->rchild->rchild = new ThreadNode;
    T->rchild->rchild->data = 7;
    CreateInThread(T);
    InOrder(T);
    CreatePreThread(T);
    PreOrder(T);
    CreatePostThread(T);
    PostOrder(T);
    return 0;
}