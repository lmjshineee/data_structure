#include <iostream>
using namespace std;	
typedef int ElemType;	// ���� ElemType ����Ϊ int

typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, *LinkList;

//�����ʼ�� ��ͷ����
bool InitList(LinkList &L){
    L=new LNode;
    L->next=NULL;
    return true;
}
//����ͷ����
bool InitList_nohead(LinkList &L){
    L=NULL;
    return true;
} 


//���
int Length(LinkList L){
    int len=0;
    LNode *p=L;
    while(p->next!=NULL){
        len++;
        p=p->next;
    }
    return len;

}

//����Ų��ҽ��
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
//��ֵ���ҽ��
LNode *LocateElem(LinkList L,ElemType e){
    LNode *p=L;
    while(p->next!=NULL && p->data!=e){
        p=p->next;
    }
    return p;
}
//������ ���
bool ListInsert(LinkList &L,int i,ElemType e){
    LNode *p=GetElem(L,i-1);
    if(p==NULL) return false;
    LNode *s=new LNode;
    s->data=e;
    s->next=p->next;
    p->next=s;
    return true;
}

//������ ǰ��  �� p->data �� s->data ��������
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


//ɾ�����
bool ListDelete(LinkList &L,int i,ElemType &e){
    LNode *p=GetElem(L,i-1);
    if(p==NULL) return false;
    LNode *q=p->next;
    e=q->data;
    p->next=q->next;
    delete q; //free(q);
    return true;
}

//ɾ���������*p
bool DeleteNode(LNode *p){
    if(p==NULL) return false;
    LNode *q=p->next;
    p->data=q->data;
    p->next=q->next;
    delete q;
    return true;
}
//ͷ�巨��������
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
    ������ͷ��� ÿ�β��붼Ҫ���½���ַ����ͷָ�� L
    L=s;
    */
    return L;
}

//β�巨��������
LinkList List_TailInsert(LinkList &L){
    InitList(L);
    LNode *s,*r=L;   //r Ϊβָ��
    int x;
    scanf("%d",&x);
    while(x!=9999){
        LNode *s=new LNode;
        s->data=x;
        r->next=s;
        s->next=NULL;
        r=s;
        scanf("%d",&x); //c ����
        //cin>>x; //c++ ����
    }
    return L;
}

//��������
void DeleteList(LinkList &L){
    LNode *p;
    while(L!=NULL){
        p=L;
        L=L->next;
        delete p;
    }
}
//��������
void TraverseList(LinkList L){
    LNode *p=L->next;
    while(p!=NULL){
        //cout<<p->data<<" ";//c++ ���
        printf("%d ",p->data);//c ���
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