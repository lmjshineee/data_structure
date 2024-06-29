#include <iostream>
using namespace std;	
typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, *LinkList;

bool InitList(LinkList &L){
    L=new LNode;
    L->next=NULL;
    return true;
}

//01 删除所有值为 x 的结点
void Delete_x(LinkList &L,ElemType x){
    LNode *p=L;
    LNode *q;
    for(q=L->next;q!=NULL;q=q->next){
        if(q->data==x){
            p->next=q->next;
            delete q;
        }
        p=q;
    }
}

void Delete_x2(LinkList &L,ElemType x){
    LNode *p=L;
    LNode *q;
    while(p->next!=NULL){
        if(p->next->data==x){
            q=p->next;
            p->next=q->next;
            delete q;
        }
        else p=p->next;
    }
}

//02 删除唯一最小值 O(n)
void Delete_Min(LinkList &L){
    LNode *p=L;
    LNode *q=L->next;
    LNode *min,*minpre;
    min=minpre=q;
    while(q!=NULL){
        if(q->data<min->data){
            min=q;
            minpre=p;
        }
        p=q;
        q=q->next;
    }
    minpre->next=min->next;
    free(min);
}

//03 逆置单链表 S(n)=O(1)
void Reverse(LinkList &L){
    LNode *p=L->next,*q;
    L->next=NULL;
    while(p!=NULL){
        q=p->next;
        p->next=L->next;
        L->next=p;
        p=q;
    }
}

int main(){
    LinkList L;
    InitList(L);
    LNode *p=L;
    for(int i=0;i<10;i++){
        LNode *s=new LNode;
        s->data=i%3;
        s->next=NULL;
        p->next=s;
        p=s;
    }
    Delete_x(L,2);
    p=L->next;
    while(p!=NULL){
        cout<<p->data<<endl;
        p=p->next;
    }
    return 0;
}