#include <iostream>
using namespace std;	
typedef int ElemType;	// 定义 ElemType 类型为 int

typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, *LinkList;

//链表初始化 带头结点的
bool InitList(LinkList &L){
    L=new LNode;
    L->next=NULL;
    return true;
}
//不带头结点的
bool InitList_nohead(LinkList &L){
    L=NULL;
    return true;
} 


//求表长
int Length(LinkList L){
    int len=0;
    LNode *p=L;
    while(p->next!=NULL){
        len++;
        p=p->next;
    }
    return len;

}

//按序号查找结点
LNode *GetElem(LinkList L,int i){
    LNode *p=L;
    int j=0;
    if(i>Length(L)) return NULL;
    while(p->next!=NULL && j<i){
        p=p->next;
        j++;
    }
    return p;
}
//按值查找结点
LNode *LocateElem(LinkList L,ElemType e){
    LNode *p=L;
    while(p->next!=NULL && p->data!=e){
        p=p->next;
    }
    return p;
}
//插入结点 后插
bool ListInsert(LinkList &L,int i,ElemType e){
    LNode *p=GetElem(L,i-1);
    if(p==NULL) return false;
    LNode *s=new LNode;
    s->data=e;
    s->next=p->next;
    p->next=s;
    return true;
}

//插入结点 前插  把 p->data 和 s->data 交换即可
bool ListInsert_pre(LinkList &L,int i,ElemType e){
    LNode *p=GetElem(L,i-1);
    if(p==NULL) return false;
    LNode *s=new LNode;
    s->next=p->next;
    p->next=s;
    s->data=p->data;
    p->data=e;
    return true;
}


//删除结点
bool ListDelete(LinkList &L,int i,ElemType &e){
    LNode *p=GetElem(L,i-1);
    if(p==NULL) return false;
    LNode *q=p->next;
    e=q->data;
    p->next=q->next;
    delete q; //free(q);
    return true;
}

//删除给定结点*p
bool DeleteNode(LNode *p){
    if(p==NULL) return false;
    LNode *q=p->next;
    p->data=q->data;
    p->next=q->next;
    delete q;
    return true;
}
//头插法建立链表
LinkList List_HeadInsert(LinkList &L){
    InitList(L);
    LNode *s;   
    int x;
    scanf("%d",&x);
    while(x!=9999){
        s=new LNode;
        s->data=x;
        s->next=L->next;
        L->next=s;
        scanf("%d",&x);
    }
    /*  
    int x;
    while(scanf("%d",&x)!=EOF){
        LNode *s=new LNode;
        s->data=x;
        s->next=L->next;
        L->next=s;
    }
    若不带头结点 每次插入都要将新结点地址赋给头指针 L
    L=s;
    */
    return L;
}

//尾插法建立链表
LinkList List_TailInsert(LinkList &L){
    InitList(L);
    LNode *s,*r=L;   //r 为尾指针
    int x;
    scanf("%d",&x);
    while(x!=9999){
        LNode *s=new LNode;
        s->data=x;
        r->next=s;
        s->next=NULL;
        r=s;
        scanf("%d",&x); //c 输入
        //cin>>x; //c++ 输入
    }
    return L;
}

//销毁链表
void DeleteList(LinkList &L){
    LNode *p;
    while(L!=NULL){
        p=L;
        L=L->next;
        delete p;
    }
}
//遍历链表
void TraverseList(LinkList L){
    LNode *p=L->next;
    while(p!=NULL){
        //cout<<p->data<<" ";//c++ 输出
        printf("%d ",p->data);//c 输出
        p=p->next;
    }
    cout<<endl;
}


int main(){
    LinkList L;
    List_HeadInsert(L);
    TraverseList(L);
    DeleteList(L);
    LNode e=GetElem(L,1);
    cout<<e.data<<endl;
    return 0;
}