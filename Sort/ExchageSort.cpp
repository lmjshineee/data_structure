#include <iostream>
using namespace std;
typedef int ElemType;

void BubbleSort(ElemType A[],int n){
    for(int i=0;i<n-1;i++){
        bool flag=false;
        for(int j=n-1;j>i;j--){
            if(A[j-1]>A[j]){
                swap(A[j-1],A[j]);
                flag=true;
            }
        }
        if(!flag) break;
    }
}


int Partition(ElemType A[],int low,int high){
    ElemType pivot=A[low];
    while(low<high){
        while(low<high&&A[high]>=pivot) --high;
        A[low]=A[high];
        while(low<high&&A[low]<=pivot) ++low;
        A[high]=A[low];
    }
    A[low]=pivot;
    return low;
}
void QuickSort(ElemType A[],int low,int high){
    if(low<high){
        int pivotpos=Partition(A,low,high);
        QuickSort(A,low,pivotpos-1);
        QuickSort(A,pivotpos+1,high);
    }
}


int main(){
    ElemType A[9]={3,1,4,1,5,9,2,6,5};
    ElemType B[9]={3,1,4,1,5,9,2,6,5};
    BubbleSort(A,9);
    for(int i=0;i<9;i++){
        cout<<A[i]<<" ";
    }
    cout<<endl;
    QuickSort(B,0,9);
    for(int i=0;i<9;i++){
        cout<<A[i]<<" ";
    }
    cout<<endl;
    return 0;
}