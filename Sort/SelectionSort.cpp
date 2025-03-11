#include <iostream>

using namespace std;
typedef int ElemType;

void SelectionSort(ElemType A[],int n){
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if(A[j]<A[min])
                min=j;
        }
        if(min!=i)
            swap(A[i],A[min]);
    }
}

void HeapAdjust(ElemType A[],int k,int len){
    A[0]=A[k];
    for(int i=2*k;i<=len;i*=2){
        if(i<len && A[i]<A[i+1])
            i++;
        if(A[0]>=A[i])
            break;
        else{
            A[k]=A[i];
            k=i;
        }
    }
    A[k]=A[0];
}

void BuildMaxHeap(ElemType A[],int len){
    for(int i=len/2;i>0;i--){
        HeapAdjust(A,i,len);
    }
}

void HeapSort(ElemType A[],int len){
    BuildMaxHeap(A,len);
    for(int i=len;i>1;i--){
        swap(A[i],A[1]);
        HeapAdjust(A,1,i-1);
    }
}

int main(){
    ElemType A[9]={3,1,4,1,5,9,2,6,5};
    SelectionSort(A,9);
    for(int i=0;i<9;i++){
        cout<<A[i]<<" ";
    }
    cout<<endl;
    ElemType B[9]={3,1,4,1,5,9,2,6,5};
    HeapSort(B,9);
    for(int i=0;i<9;i++){
        cout<<B[i]<<" ";
    }
    return 0;

}