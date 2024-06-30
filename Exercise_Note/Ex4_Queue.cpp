#include <iostream>
#include <stack>
using namespace std;
typedef int ElemType;

#define MaxSize 10
typedef struct{
    ElemType data[MaxSize];
    int front,rear;
    int tag;
}SqQueue;

void InitQueue(SqQueue &Q){
    Q.front=Q.rear=0;
    Q.tag=0;
}

bool isEmpty(SqQueue Q){
    if(Q.front==Q.rear && Q.tag==0)
        return true;
    else
        return false;
}

bool EnQueue(SqQueue &Q,ElemType x){
    if(Q.rear==Q.front && Q.tag==1)
        return false;
    Q.data[Q.rear]=x;
    Q.rear=(Q.rear+1)%MaxSize;
    if(Q.rear==Q.front)
        Q.tag=1;
    return true;
}

bool DeQueue(SqQueue &Q,ElemType &x){
    if(Q.front==Q.rear && Q.tag==0)
        return false;
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;
    Q.tag=0;
    return true;
}

//02
bool Reverse(SqQueue &Q){
    stack<ElemType> S;
    while(!isEmpty(Q)){
        ElemType x;
        DeQueue(Q,x);
        S.push(x);
    }
    while(!S.empty()){
        ElemType x=S.top();
        S.pop();
        EnQueue(Q,x);
    }
    return true;
}

bool EnQueue(Stack &S1,Stack &S2,ElemType x){
    if(!StackOverflow(S1)){
        Push(S1,x);
        return true;
    })
    if(StackOverflow(S1) && StackEmpty(S2)){
        while(!StackEmpty(S1)){
            ElemType e;
            Pop(S1,e);
            Push(S2,e);
        }
        Push(S1,x);
        return true;
    }
    if(StackOverflow(S1) && !StackEmpty(S2)){
        cout<<""<<endl;
        return false;
    } 
}

bool DeQueue(Stack &S1,Stack &S2,ElemType &x){
    if(StackEmpty(S1) && StackEmpty(S2)){
        cout<<""<<endl;
        return false;
    }
    if(StackEmpty(S1) && !StackEmpty(S2)){
        while(!StackEmpty(S2)){
            ElemType e;
            Pop(S2,e);
            Push(S1,e);
        }
        Pop(S1,x);
        return true;
    }
    if(!StackEmpty(S1)){
        Pop(S1,x);
        return true;
    }
}

int main(){
    SqQueue Q;
    InitQueue(Q);
    for(int i=0;i<10;i++)
        EnQueue(Q,i);
    ElemType x;
    DeQueue(Q,x);
    cout<<"Dequeued element is:"<<x<<endl;
    EnQueue(Q,10);
    EnQueue(Q,11);
    while(!isEmpty(Q)){
        DeQueue(Q,x);
        cout<<x<<" ";
    }
    return 0;

}