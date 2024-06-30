#include<iostream>
using namespace std;
typedef int ElemType;

typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;
typedef struct{
    LinkNode *front,*rear;
}LinkQueue;

//带头结点
void InitQueue(LinkQueue &Q){
    Q.front=Q.rear=new LinkNode;
    Q.front->next=NULL;
}
bool isEmpty(LinkQueue Q){
    if(Q.front==Q.rear)
        return true;
    else
        return false;
}
void EnQueue(LinkQueue &Q,ElemType x){
    LinkNode *s=new LinkNode;
    s->data=x;
    s->next=NULL;
    Q.rear->next=s;
    Q.rear=s;
}

bool DeQueue(LinkQueue &Q,ElemType &x){
    if(Q.front==Q.rear)
        return false;
    LinkNode *p=Q.front->next;
    x=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
        Q.rear=Q.front;
    free(p);
    return true;
}

ElemType GetHead(LinkQueue Q){
    if(Q.front==Q.rear)
        return -1;
    return Q.front->next->data;
}

/*
//不带头结点
void InitQueue(LinkQueue &Q){
    Q.front=Q.rear=NULL;
}
bool isEmpty(LinkQueue Q){
    if(Q.front==NULL)
        return true;
    else
        return false;
}
void EnQueue(LinkQueue &Q,ElemType x){
    LinkNode *s=(LinkNode*)malloc(sizeof(LinkNode));
    s->data=x;
    s->next=NULL;
    if(Q.rear==NULL)
        Q.front=Q.rear=s;
    else{
        Q.rear->next=s;
        Q.rear=s;
    }
}

bool DeQueue(LinkQueue &Q,ElemType &x){
    if(Q.front==NULL)
        return false;
    x=Q.front->data;
    LinkNode *p=Q.front;
    Q.front=Q.front->next;
    if(Q.front==NULL)
        Q.rear=NULL;//如果删除后队列为空，则 rear 指针也置空
    free(p);
    return true;
}

ElemType GetHead(LinkQueue Q){
    if(Q.front!=NULL)
        return Q.front->data;
    else
        return -1;
}
*/
int main(){
    LinkQueue Q;
    InitQueue(Q);
    for(int i=0;i<10;i++)
        EnQueue(Q,i);
    ElemType x;
    DeQueue(Q,x);
    cout<<"Dequeued element is:"<<x<<endl;
    cout<<"Head element is:"<<GetHead(Q)<<endl;
    return 0;
}