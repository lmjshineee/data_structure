#include<iostream>
using namespace std;
typedef int ElemType;

//˳��ջ
#define MAXSIZE 100
typedef struct{
    ElemType data[MAXSIZE]; //���飿������
    int top;
}SqStack;

//��ʼ��
void InitStack(SqStack &S){
    S.top = -1;
}

//�ж�ջ�Ƿ�Ϊ��
bool StackEmpty(SqStack S){
    if(S.top == -1)
        return true;
    else
        return false;
}

//�ж�ջ�Ƿ�����
bool StackFull(SqStack S){
    if(S.top==MAXSIZE-1)
        return true;
    else
        return false;
}

//��ջ
bool Push(SqStack &S,ElemType e){
    if(StackFull(S))
        return false;
    S.data[++S.top]=e;
    return true;
}

//��ջ
bool Pop(SqStack &S,ElemType &e){
    if(StackEmpty(S))
        return false;
    e=S.data[S.top--];
    return true;
}

//��ȡջ��Ԫ��
bool GetTop(SqStack S,ElemType &e){
    if(StackEmpty(S))
        return false;
    e=S.data[S.top];
    return true;
}

//����ջ
void TraverseStack(SqStack S){
    for(int i=0;i<=S.top;i++)
        cout<<S.data[i]<<" ";
    cout<<endl;
}

//����ջ !!!!!!!!!!!!!
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
    cout<<"��ջԪ��Ϊ��"<<e<<endl;
    TraverseStack(S);
    GetTop(S,e);
    cout<<"ջ��Ԫ��Ϊ��"<<e<<endl;
    return 0;
}