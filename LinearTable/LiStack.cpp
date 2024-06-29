#include<iostream>
using namespace std;
typedef int ElemType;

//��ʽջ
typedef struct Linknode{
    ElemType data;
    struct Linknode* next;
}Linknode,*LinkStack;

//��ʼ�� ��ͷ���
bool InitLiStack(LinkStack &S){
    S=new Linknode;
    S->next=NULL;
    return true;
}

//�ж�ջ�Ƿ�Ϊ��
bool isEmpty(LinkStack S){
    return S->next==NULL;
}

//��ջ
bool push(LinkStack &S,ElemType e){ //ͷ��ʽ
    LinkStack p=new Linknode;
    p->data=e;
    p->next=S->next;
    S->next=p;
    return true;
}

//��ջ
bool pop(LinkStack &S,ElemType &e){//ɾ����һ��
    if(S->next==NULL) return false;
    LinkStack p=S->next;
    S->next=p->next;
    e=p->data;
    delete p;
    return true;
}

//��ջ��Ԫ��
bool getTop(LinkStack S,ElemType &e){
    if(S->next==NULL) return false;
    e=S->next->data;
    return true;
}

//����ջ
bool DestoryLiStack(LinkStack &S){
    while(S->next!=NULL){
        LinkStack p=S->next;
        S->next=p->next;
        delete p;
    }
    
    return true;
}


int main(){
    LinkStack S;
    InitLiStack(S);
    push(S,1);
    push(S,2);
    push(S,3);
    ElemType e;
    getTop(S,e);
    cout<<e<<endl;
    pop(S,e);
    cout<<e<<endl;
    return 0;
}