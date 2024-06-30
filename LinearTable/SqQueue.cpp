#include<iostream>
using namespace std;
typedef int ElemType;

#define MaxSize 50
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

int main(){
    SqQueue Q;
    InitQueue(Q);
    for(int i=0;i<10;i++)
        EnQueue(Q,i);
    ElemType x;
    DeQueue(Q,x);
    cout<<"Dequeued element is:"<<x<<endl;
    cout<<"Length is:"<<GetLength(Q)<<endl;
    DeQueue(Q,x);
    EnQueue(Q,10);
    EnQueue(Q,11);
    return 0;
}