#include <iostream>
using namespace std;
typedef int ElemType;
#define InitSize 10
typedef struct{
    ElemType *data;
    int MaxSize,length;
}SqList;
//01 用最后一位填上最小的一位，并删除最后一位
bool del_min(SqList &L,ElemType &value){
    if(L.length==0) return false;
    value=L.data[0];
    int pos=0;
    for(int i=0;i<L.length;i++){
        if (L.data[i]<value){
            value=L.data[i];
            pos=i;
        }
    }
    L.data[pos]=L.data[L.length-1];
    L.length--;
    return true;
}

//02 高效算法 逆置顺序表
void reverse1(SqList &L){
    ElemType temp;
    for(int i=0;i<L.length/2;i++){
        temp=L.data[i];
        L.data[i]=L.data[L.length-i-1];
        L.data[L.length-i-1]=temp;
    }
}           

//03 T(n)=O(n) S(n)=O(1) 删除所有值为 x 的元素
void del_x(SqList &L,ElemType x){
    int k=0;
    for(int i=0;i<L.length;i++){
        if(L.data[i]!=x){
            L.data[k]=L.data[i];
            k++;
        }
    }
    L.length=k;
}

//04 T(n)=O(n) S(n)=O(1) 删除 s<=i<=t 之间的所有的元素
void del_st(SqList &L,ElemType s,ElemType t){
    if(s>=t||L.length==0) return;
    int k=0;
    for(int i=0;i<L.length;i++){
        if(L.data[i]<s||L.data[i]>t){
            L.data[++k]=L.data[i];
        }
    }
    L.length=k;
    if(k==0) return;
}

//05 T(n)=O(n) S(n)=O(1) 删除有序表中重复的元素 !!! 有问题!!!
void del_repeat1(SqList &L){
    if(L.length==0) return;
    int i,j;
    for(i=0,j=1;j<L.length;j++){
        if(L.data[i]!=L.data[j]){
            L.data[++i]=L.data[j];
        }
    }
    L.length=i+1;
}

//05 修改版
void del_repeat(SqList &L){
    if(L.length==0) return;
    int i,j;
    for(i=0,j=1;j<L.length;j++){
        if(L.data[i]!=L.data[j]){
            L.data[++i]=L.data[j];
        }
    }
    L.length=i+1;
}

//06 合并两个有序顺序表
bool merge(SqList L1,SqList L2,SqList &L){
    if(L1.length+L2.length>L.MaxSize) return false;
    int i=0,j=0,k=0;
    while(i<L1.length&&j<L2.length){
        if(L1.data[i]<=L2.data[j]){
            L.data[k++]=L1.data[i++];
        }else{
            L.data[k++]=L2.data[j++];
        }
    }
    while(i<L1.length){
        L.data[k++]=L1.data[i++];
    }
    while(j<L2.length){
        L.data[k++]=L2.data[j++];
    }
    L.length=k;
    return true;   
}


//07 逆置 A+B -> B+A   ?
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

//08 顺序表最快查找，找到与后一个互换位置，没找到插入  ???
void find_x(SqList &L,ElemType x){
    int low=0,high=L.length-1,mid;
    while(low<=high){
        mid=(low+high)/2;
        if(L.data[mid]==x) break;
        if(L.data[mid]<x) low=mid+1;
        else high=mid-1;
    }
    if(L.data[mid]==x&&mid!=L.length-1){
        ElemType temp=L.data[mid];
        L.data[mid]=L.data[mid+1];
        L.data[mid+1]=temp;
    }
    if(low>high){
        for(int i=L.length;i>high;i--){
            L.data[i]=L.data[i-1];
        }
        L.data[high+1]=x;
        L.length++;
    }
}

//09 输出同时存在三个序列的所有元素
/*
T(n)=O(n) S(n)=O(1)  
*/
void find_common(ElemType A[],ElemType B[],ElemType C[],int n){
    int i=0,j=0,k=0;
    while(i<n&&j<n&&k<n){
        if(A[i]==B[j]&&B[j]==C[k]){
            cout<<A[i]<<" ";
            i++,j++,k++;
        }
        else{
            ElemType maxNum=max(max(A[i],B[j]),C[k]);
            if(A[i]<maxNum) i++;
            if(B[j]<maxNum) j++;
            if(C[k]<maxNum) k++;
        }
    }
}

//10 循环左移 p 个位置
//T(n)=O(p/2)+O((n-p)/2)+O(n/2)=O(n) S(n)=O(1)
void reverse_num(ElemType A[],int n,int p=0){
    ElemType temp;
    if(p=0) p=n;
    for(int i=0;i<p/2;i++){
        temp=A[i];
        A[i]=A[p-i-1];
        A[p-i-1]=temp;
    }
}
void shift_cycle(ElemType A[],int n,int p){
    p=p%n;
    reverse_num(A,n,p);
    reverse_num(A,n);
    reverse_num(A,n,n-p);
}

//10 解法 2
void Reverse(int A[],int from,int to) {
    int i,temp;
    for(i=0;i<(to-from+1)/2;i++) {
        temp=A[from+i];
        A[from+i]=A[to-i];
        A[to-i]=temp;
    }
}
void shift_reverse(ElemType A[],int n,int p){
    p=p%n;
    Reverse(A,0,p-1);
    Reverse(A,p,n-1);
    Reverse(A,0,n-1);
}

// 先做 10 个吧 还有 4 个没做