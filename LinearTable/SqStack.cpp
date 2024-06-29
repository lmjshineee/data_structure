#include<iostream>
using namespace std;
typedef int ElemType;

//顺序栈
#define MAXSIZE 100
typedef struct{
    ElemType data[MAXSIZE]; //数组？？？？
    int top;
}SqStack;

//初始化
void InitStack(SqStack &S){
    S.top = -1;
}

//判断栈是否为空
bool StackEmpty(SqStack S){
    if(S.top == -1)
        return true;
    else
        return false;
}

//判断栈是否已满
bool StackFull(SqStack S){
    if(S.top==MAXSIZE-1)
        return true;
    else
        return false;
}

//入栈
bool Push(SqStack &S,ElemType e){
    if(StackFull(S))
        return false;
    S.data[++S.top]=e;
    return true;
}

//出栈
bool Pop(SqStack &S,ElemType &e){
    if(StackEmpty(S))
        return false;
    e=S.data[S.top--];
    return true;
}

//读取栈顶元素
bool GetTop(SqStack S,ElemType &e){
    if(StackEmpty(S))
        return false;
    e=S.data[S.top];
    return true;
}

//遍历栈
void TraverseStack(SqStack S){
    for(int i=0;i<=S.top;i++)
        cout<<S.data[i]<<" ";
    cout<<endl;
}

//销毁栈 !!!!!!!!!!!!!
void DestroyStack(SqStack &S){
    S.top=-1;
}

int main(){
    SqStack S;
    InitStack(S);
    Push(S,1);
    Push(S,2);
    Push(S,3);
    TraverseStack(S);
    ElemType e;
    Pop(S,e);
    cout<<"出栈元素为："<<e<<endl;
    TraverseStack(S);
    GetTop(S,e);
    cout<<"栈顶元素为："<<e<<endl;
    return 0;
}