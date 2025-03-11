/*
  用 c++ 实现的 (动态分配) 顺序表，包括初始化，插入，删除，查找，输出等操作  
*/

#include <iostream>
using namespace std;

typedef int ElemType;
/* 静态分配顺序表
#define MaxSize 50
typedef struct{
    ElemType data[MaxSize];
    int length;
}SqList;
*/

// 动态分配顺序表
#define InitSize 10
#define Max 50;
typedef struct{
    ElemType *data;
    int MaxSize,length;
}SqList;

//初始化
void InitList(SqList &L){
    
}

//插入
bool ListInsert(SqList &L,int i,ElemType e){
    if(i<1||i>L.length+1||L.length>=L.MaxSize) return false;
    for (int j=L.length;j>=i;j--){
        L.data[j]=L.data[j-1];
    }
    L.data[i-1]=e;
    L.length++;
    return true;
}

//删除
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

//查找 返回最小的序号
int LocateElem(SqList L,ElemType e){
    for(int i=0;i<L.length;i++){
        if(L.data[i]==e) return i+1;
    }
    return 0;
}

//输出
void ListPrint(SqList L){
    for(int i=0;i<L.length;i++){
        cout<<L.data[i]<<" ";
    }
    cout<<endl;
}

//删除重复
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

//翻转
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