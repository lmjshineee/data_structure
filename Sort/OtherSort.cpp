#include <iostream>
#include <vector>

using namespace std;
typedef int ElemType;
#define num 100

ElemType *B=new ElemType[num+1];
//B[100] ��ȫ�ֱ������� main �����ж��壬�ں����п���ֱ��ʹ�ã�����Ҫ����

/* �鲢���� */
void Merge(ElemType A[],int low,int mid,int high){
    int i,j,k;
    for(k=low;k<=high;k++){
        B[k]=A[k];
    }
    for(i=low,j=mid+1,k=i;i<=mid&&j<=high;k++){
        if(B[i]<=B[j])
            A[k]=B[i++];
        else
            A[k]=B[j++];
    }
    while(i<=mid)
        A[k++]=B[i++];
    while(j<=high)
        A[k++]=B[j++];
}
void MergeSort(ElemType A[],int low,int high){
    if(low<high){
        int mid=(low+high)/2;
        MergeSort(A,low,mid);
        MergeSort(A,mid+1,high);
        Merge(A,low,mid,high);
    }
}

/* �������� */
void RadixSort(ElemType A[],int n){
    int i,j,k;
    vector<vector<int>> bucket(10);
    for(i=0;i<10;i++){
        bucket[i].clear();
    }
    for(i=0;i<n;i++){
        bucket[A[i]%10].push_back(A[i]);
    }
    k=0;
    for(i=0;i<10;i++){
        for(j=0;j<bucket[i].size();j++){
            A[k++]=bucket[i][j];
        }
    }
    for(i=0;i<10;i++){
        bucket[i].clear();
    }
    for(i=0;i<n;i++){
        bucket[A[i]/10%10].push_back(A[i]);
    }
    k=0;
    for(i=0;i<10;i++){
        for(j=0;j<bucket[i].size();j++){
            A[k++]=bucket[i][j];
        }
    }
}
//����������ȶ��ԣ������������ȶ��������㷨����Ϊ�ڷ�����ռ��Ĺ����У���ͬ�ؼ��ֵļ�¼����Դ����ǲ���ı�ġ�

/* �������� */
//���������˼·��
//1.�ҳ��������������������С��Ԫ�أ�
//2.ͳ��������ÿ��Ԫ�س��ֵĴ������������� C��
//3.�����еļ����ۼӣ��� C[0] �� C[k]�����õ��µ����� B��
//4.����������� A����������Ľ����
void CountSort(ElemType A[],ElemType B[],int n){
    int i,C[n];
    for(i=0;i<n;i++) C[i]=0;
    for(i=0;i<n;i++) C[A[i]]++;
    for(i=1;i<n;i++) C[i]+=C[i-1];
    for(i=n-1;i>=0;i--){
        B[--C[A[i]]]=A[i];
    }
}

int main(){
    ElemType A[9]={3,1,4,1,5,9,2,6,5};
    MergeSort(A,0,8);
    for(int i=0;i<9;i++){
        cout<<A[i]<<" ";
    }
    cout<<endl;
    ElemType B[9]={3,1,4,1,5,9,2,6,5};
    RadixSort(B,9);
    for(int i=0;i<9;i++){
        cout<<B[i]<<" ";
    }
    cout<<endl;
    ElemType C[9]={3,1,4,1,5,9,2,6,5};
    ElemType D[9]={0};
    CountSort(C,D,10);
    for(int i=0;i<9;i++){
        cout<<D[i]<<" ";
    }
    cout<<endl;
    return 0;
}