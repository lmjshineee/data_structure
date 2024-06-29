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
}