# include <iostream>
using namespace std;
typedef int ElemType;

typedef struct DNote{
    ElemType data;
    struct DNote *prior,*next;
}DNote, *DLinkList;

// ��ʼ��
DNote *init(){
    DNote *L = new DNote;
    L->prior = L->next = L;
    return L;
}

//����
bool Insert(DNote *L, int i, ElemType e){
    DNote *p = L;
    int j = 0;
    while(p->next != L && j < i){
        p = p->next;
        j++;
    }
    if(j != i) return false;
    DNote *s = new DNote;
    s->data = e;
    s->prior = p;
    s->next = p->next;
    p->next->prior = s;
    p->next = s;
    return true;
}

//ɾ�� q
bool Delete(DNote *L, int i, ElemType &e){
    DNote *p = L;
    int j = 0;
    while(p->next != L && j < i){
        p = p->next;
        j++;
    }
    if(j != i) return false;
    DNote *q = p->next;
    e = q->data;
    p->next = q->next;
    q->next->prior = p;
    delete q;
    return true;
}

// ��̬���� next==-1 ���� �ڲ�֧��ָ��ʱ����
#define MaxSize 50
typedef struct{
    ElemType data;
    int next;
} SLinkList[MaxSize];
