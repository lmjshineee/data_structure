#include <iostream>
#include <stack>
using namespace std;

//�жϳ���ջ�����Ƿ�Ϸ�
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
        cout<<"�Ϸ�"<<endl;
    }
    else{
        cout<<"���Ϸ�"<<endl;
        cout<<"�Ϸ������ǣ�"<<n<<endl;
    }
    return 0;
    
}