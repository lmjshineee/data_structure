#include<iostream>
#define ElemType char
#define MaxSize 100

using namespace std;

typedef struct Node{
    struct Node* l=NULL; 
    struct Node* r=NULL; 
    int lt=0,rt=0;//left tag, right tag，如果为 1 表示左（右）结点不存在，为前驱（后继） 
    ElemType data;
    Node(ElemType data=0):data(data){
    }
}Node;

Node* buildSampleTree(){//样例树形结构来自天勤 2019 版 142 页 
    Node* nd=new Node('A');
    nd->l= new Node('B');
    nd->r= new Node('G');
    nd->l->l= new Node('C');
    nd->l->r= new Node('D');
    nd->r->l= new Node('H');
    nd->l->r->l= new Node('E');
    nd->l->r->r= new Node('F');
    return nd;
}

void visit(Node* p){
    cout<<p->data<<' ';
}

void PreThread(Node* p,Node* &pre){
    if(p) {
        if(p->l==NULL){    //左结点不存在 
            p->lt=1;    //设置 p 的前驱 
            p->l=pre;
        }
        //注意加上 pre 非空的短路判断条件，避免空指针操作 
        if(pre!=NULL && pre->r==NULL){    //右结点不存在 
            pre->r=p;    //设置 pre 的后继 
            pre->rt=1; 
        }
        pre=p;    //前驱结点更新
        if(p->lt==0)    //左子树存在 
            PreThread(p->l,pre);
        if(p->lt==0)    //右子树存在 
            PreThread(p->r,pre);
    }
}

void createPreThread(Node* root){    //对根节点进行中序线索化 
    Node * pre=NULL;    //第一个结点的前驱为 0 
    if(root!=NULL){
        PreThread(root,pre);
        pre->r=NULL;//最后一个结点的后继为 0  
        pre->rt=1; 
    }
}

void PreOrderTraversal(Node* root){    //中序线索化遍历 
    if(root==NULL)  return;
    Node* p=root;
    while(p){
        while(p->lt==0){
            visit(p);
            p=p->l;
        }
        visit(p);    //此时 p 必为前驱结点的后继（线索），但还没有访问到，访问。
        p=p->r;        //指向 p 的右子树 或 后继 
    }
}

int main(){
    Node *root=buildSampleTree();
    createPreThread(root);
    PreOrderTraversal(root);
}