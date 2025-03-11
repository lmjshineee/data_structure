#include <iostream>
#include <chrono>

using namespace std;
typedef int ElemType;

/* Ê¹ÓÃÉÚ±øµÄ²åÈëÅÅĞò */
void InsertSort(ElemType A[], int n){
    int i,j;
    for(i=2;i<=n;i++){
        if(A[i]<A[i-1]){
            A[0]=A[i];
            for(j=i-1;A[0]<A[j];--j){
                A[j+1]=A[j];
            }
            A[j+1]=A[0];
        }
    }
}

/* ÕÛ°ë²åÈëÅÅĞò */
void BInsertSort(ElemType A[],int n){
    int  i,j,low,high,mid;
    for(i=2;i<=n;i++){
        if(A[i]<A[i-1]){
            A[0]=A[i];
            low=1;high=i-1;
            while(low<=high){
                mid=(low+high)/2;
                if(A[mid]>A[0])
                    high=mid-1;
                else
                    low=mid+1;   
            }
            for(j=i-1;j>=high+1;--j)
                A[j+1]=A[j];
            A[high+1]=A[0];
        }
    }
}

/* Ï£¶ûÅÅĞò A[0] ÊÇÔİ´æµ¥Ôª ²»ÊÇÉÚ±ø£¿??? */
void ShellSort(ElemType A[],int n){
    int i,j,dk;
    for(dk=n/2;dk>=1;dk=dk/2){
        for(i=dk+1;i<=n;i++){
            if(A[i]<A[i-dk]){
                A[0]=A[i];
                for(j=i-dk;j>0&&A[0]<A[j];j-=dk)
                    A[j+dk]=A[j];
                A[j+dk]=A[0];
            }
        }
    }
}

int main(){
    ElemType A[10]={0,3,1,4,1,5,9,2,6,5};
    auto start = std::chrono::high_resolution_clock::now();
    // Ö´ĞĞÄãµÄ´úÂë
    InsertSort(A,9);
    auto stop1 = std::chrono::high_resolution_clock::now();
    
    ElemType C[10]={0,3,1,4,1,5,9,2,6,5};
    auto start2 = std::chrono::high_resolution_clock::now();
    BInsertSort(C,9);
    auto stop2 = std::chrono::high_resolution_clock::now();

    ElemType B[10]={0,3,1,4,1,5,9,2,6,5};
    auto start3 = std::chrono::high_resolution_clock::now();
    ShellSort(B,9);
    auto stop3 = std::chrono::high_resolution_clock::now();

    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start).count();
    std::cout << "Elapsed time: " << duration1 << " Î¢Ãë\n";
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2).count();
    std::cout << "Elapsed time: " << duration2 << " Î¢Ãë\n";
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3).count();
    std::cout << "Elapsed time: " << duration3 << " Î¢Ãë\n";
    return 0;
}