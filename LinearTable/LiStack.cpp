#include<iostream>
using namespace std;
typedef int ElemType;

//链式栈
typedef struct Linknode{
    ElemType data;
    struct Linknode* next;
}Linknode,*LinkStack;

//初始化 带头结点
bool InitLiStack(LinkStack &S){
    S=new Linknode;
    S->next=NULL;
    return true;
}

//判断栈是否为空
bool isEmpty(LinkStack S){
    return S->next==NULL;
}

//入栈
bool push(LinkStack &S,ElemType e){ //头插式
    LinkStack p=new Linknode;
    p->data=e;
    p->next=S->next;
    S->next=p;
    return true;
}

//出栈
bool pop(LinkStack &S,ElemType &e){//删除第一个
    if(S->next==NULL) return false;
    LinkStack p=S->next;
    S->next=p->next;
    e=p->data;
    delete p;
    return true;
}

//读栈顶元素
bool getTop(LinkStack S,ElemType &e){
    if(S->next==NULL) return false;
    e=S->next->data;
    return true;
}

//销毁栈
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