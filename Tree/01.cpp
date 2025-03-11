#include<iostream>
#define ElemType char
#define MaxSize 100

using namespace std;

typedef struct Node{
    struct Node* l=NULL; 
    struct Node* r=NULL; 
    int lt=0,rt=0;//left tag, right tag�����Ϊ 1 ��ʾ���ң���㲻���ڣ�Ϊǰ������̣� 
    ElemType data;
    Node(ElemType data=0):data(data){
    }
}Node;

Node* buildSampleTree(){//�������νṹ�������� 2019 �� 142 ҳ 
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
        if(p->l==NULL){    //���㲻���� 
            p->lt=1;    //���� p ��ǰ�� 
            p->l=pre;
        }
        //ע����� pre �ǿյĶ�·�ж������������ָ����� 
        if(pre!=NULL && pre->r==NULL){    //�ҽ�㲻���� 
            pre->r=p;    //���� pre �ĺ�� 
            pre->rt=1; 
        }
        pre=p;    //ǰ��������
        if(p->lt==0)    //���������� 
            PreThread(p->l,pre);
        if(p->lt==0)    //���������� 
            PreThread(p->r,pre);
    }
}

void createPreThread(Node* root){    //�Ը��ڵ�������������� 
    Node * pre=NULL;    //��һ������ǰ��Ϊ 0 
    if(root!=NULL){
        PreThread(root,pre);
        pre->r=NULL;//���һ�����ĺ��Ϊ 0  
        pre->rt=1; 
    }
}

void PreOrderTraversal(Node* root){    //�������������� 
    if(root==NULL)  return;
    Node* p=root;
    while(p){
        while(p->lt==0){
            visit(p);
            p=p->l;
        }
        visit(p);    //��ʱ p ��Ϊǰ�����ĺ�̣�������������û�з��ʵ������ʡ�
        p=p->r;        //ָ�� p �������� �� ��� 
    }
}

int main(){
    Node *root=buildSampleTree();
    createPreThread(root);
    PreOrderTraversal(root);
}