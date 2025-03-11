#include <iostream>
#include <stack>
using namespace std;

//判断出入栈操作是否合法
bool judge(int a[],int &n){
    stack<int> s;
    for(int i=0;i<n;i++){
        if(a[i]==1){
            s.push(i);
        }
        else{
            if(s.empty()) 
            {
                n=i;
                return false;
            }
            s.pop();
        }
    }
    return true;
}

int main(){
    int a[]={1,0,1,1,0,0,1,0,0,0,0};
    int n=11;
    if(judge(a,n)){
        cout<<"合法"<<endl;
    }
    else{
        cout<<"不合法"<<endl;
        cout<<"合法长度是："<<n<<endl;
    }
    return 0;
    
}