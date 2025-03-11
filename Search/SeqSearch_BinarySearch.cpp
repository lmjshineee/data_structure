#include <iostream>
using namespace std;

typedef int ElemType;

typedef struct{
    ElemType *elem;
    int TableLen;
}SSTable;

//0 号位作为哨兵，不存储数据
int Search_Seq(SSTable ST,ElemType key){
    ST.elem[0]=key;
    int i;
    for(i=ST.TableLen;ST.elem[i]!=key;--i);
    return i;
}

//二分查找，要求有序的顺序表
int Binary_Search(SSTable ST,ElemType key){
    int low=0,high=ST.TableLen-1,mid;
    while(low<=high){
        mid=(low+high)/2;
        if(ST.elem[mid]==key){
            return mid;
        }else if(ST.elem[mid]>key){
            high=mid-1;
        }else{
            low=mid+1;
        }
    }
    return -1;
}

//分块查找，要求有序的顺序表
int Block_Search(SSTable ST,ElemType key){
    int n=ST.TableLen;
    

}



int main(){
    SSTable ST;
    ST.TableLen=10;
    ST.elem=new ElemType[ST.TableLen+1];
    for(int i=1;i<=ST.TableLen;i++){
        ST.elem[i]=i;
    }
    cout<<Search_Seq(ST,5)<<endl;
    cout<<Binary_Search(ST,5)<<endl;

    return 0;
}