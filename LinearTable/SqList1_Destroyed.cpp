/*
  �� c++ ʵ�ֵ� (��̬����) ˳���������ʼ�������룬ɾ�������ң�����Ȳ���  
*/

#include <iostream>
using namespace std;

typedef int ElemType;
/* ��̬����˳���
#define MaxSize 50
typedef struct{
    ElemType data[MaxSize];
    int length;
}SqList;
*/

// ��̬����˳���
#define InitSize 10
#define Max 50;
typedef struct{
    ElemType *data;
    int MaxSize,length;
}SqList;

//��ʼ��
void InitList(SqList &L){
    
}

//����
bool ListInsert(SqList &L,int i,ElemType e){
    if(i<1||i>L.length+1||L.length>=L.MaxSize) return false;
    for (int j=L.length;j>=i;j--){
        L.data[j]=L.data[j-1];
    }
    L.data[i-1]=e;
    L.length++;
    return true;
}

//ɾ��
bool ListDelete(SqList &L,int i,ElemType e){ //ElemType &e
    if(i<1||i>L.length) return false;
    e=L.data[i-1];
    for (int j=i;j<=L.length;j++){
        L.data[j-1]=L.data[j];
    }
    printf("%d is deleted.\n",e);
    L.length--;
    return true;
}

//���� ������С�����
int LocateElem(SqList L,ElemType e){
    for(int i=0;i<L.length;i++){
        if(L.data[i]==e) return i+1;
    }
    return 0;
}

//���
void ListPrint(SqList L){
    for(int i=0;i<L.length;i++){
        cout<<L.data[i]<<" ";
    }
    cout<<endl;
}

//ɾ���ظ�
void del_repeat(SqList &L){
    if(L.length==0) return;
    for(int j=0;j<L.length;j++){
        for(int k=j+1;k<L.length;k++){
            if(L.data[j]==L.data[k]){
                ListDelete(L,k+1,L.data[k]);
            }
        }
    }
}

//��ת
void reverse(SqList &L,int m=0){
    ElemType temp;
    if(m==0) m=L.length;
    if(m<0||m>L.length) return;
    for(int i=0;i<m/2;i++){
        temp=L.data[i];
        L.data[i]=L.data[m-i-1];
        L.data[m-i-1]=temp;
    }
}
void reverse_ab(SqList &L,int m,int n){
    reverse(L,m);
    reverse(L);
    reverse(L,n);
}


int main(){
    SqList L;
    InitList(L);
    ListInsert(L,1,1);
    ListInsert(L,2,2);
    ListInsert(L,3,1);
    ListInsert(L,4,2);
    ListInsert(L,5,5);
    ListPrint(L);
    /*del_repeat(L);
    ListPrint(L);*/
    reverse_ab(L,2,3);
    ListPrint(L);
   // cout<<LocateElem(L,4)<<endl;
    return 0;
}