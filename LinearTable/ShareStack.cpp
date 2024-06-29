#include<iostream>
using namespace std;
typedef int ElemType;

//顺序栈
#define MAXSIZE 100
typedef struct{
    ElemType data[MAXSIZE];
    int top0;//从小到大
    int top1;//从大到小
}ShareStack;

void InitShareStack(ShareStack &S){
    S.top0 = -1;
    S.top1 = MAXSIZE;
}

bool Push(ShareStack &S,ElemType x,int i){
    if(S.top0+1==S.top1)
        return false;
    if(i==0)
        S.data[++S.top0]=x;
    else if(i==1)
        S.data[--S.top1]=x;
    return true;
}

bool Pop(ShareStack &S,ElemType &x,int i){
    if(i==0&&S.top0==-1 || i==1&&S.top1==MAXSIZE)
        return false;
    if(i==0)
        x=S.data[S.top0--];
    if(i==1)
        x=S.data[S.top1++];
    return true;
}

int main(){
    ShareStack S;
    InitShareStack(S);
    Push(S,1,0);
    Push(S,2,0);
    Push(S,3,0);
    Push(S,4,1);
    Push(S,5,1);
    Push(S,6,1);
}