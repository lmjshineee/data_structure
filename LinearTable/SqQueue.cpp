#include<iostream>
using namespace std;
typedef int ElemType;

#define MaxSize 10
typedef struct{
    ElemType data[MaxSize];
    int front,rear;
}SqQueue;

void InitQueue(SqQueue &Q){
    Q.front=Q.rear=0;
}
//循环队列 解决假溢出问题


bool isEmpty(SqQueue Q){
    if(Q.front==Q.rear)
        return true;
    else
        return false;
}

bool EnQueue(SqQueue &Q,ElemType x){
    if((Q.rear+1)%MaxSize==Q.front)
        return false;
    Q.data[Q.rear]=x;
    Q.rear=(Q.rear+1)%MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q,ElemType &x){
    if(Q.front==Q.rear)
        return false;
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;
    return true;
}

int GetLength(SqQueue Q){
    return (Q.rear-Q.front+MaxSize)%MaxSize;
}

int GetHead(SqQueue Q){
    if(!isEmpty(Q))
        return Q.data[Q.front];
    else
        return -1;
}

int GetTail(SqQueue Q){
    if(!isEmpty(Q))
        return Q.data[Q.rear-1];
    else
        return -1;
}


int main(){
    SqQueue Q;
    InitQueue(Q);
    for(int i=1;i<MaxSize;i++)
        EnQueue(Q,i);
    ElemType x;
    for(int i=1;i<MaxSize;i++){
        DeQueue(Q,x);
        cout<<x<<endl;
    }
    EnQueue(Q,10);
    EnQueue(Q,11);
    EnQueue(Q,12);
    EnQueue(Q,13);

    cout<<GetLength(Q)<<endl;

    cout<<Q.front<<endl;
    cout<<Q.rear<<endl;

    cout<<GetHead(Q)<<endl;
    cout<<GetTail(Q)<<endl;
    return 0;
}