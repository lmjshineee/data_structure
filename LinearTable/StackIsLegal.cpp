#include <iostream>
#include <stack>
using namespace std;

//判断出入栈操作是否合法
bool judge(int a[],int n){
    stack<int> s;
    for(int i=0;i<n;i++){
        if(a[i]==1){
            s.push(i);
        }
        else{
            if(s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

void create(int a[],int n){
    stack<int> s;
    for(int i=0;i<n;i++){
        if(a[i]==1){
            s.push(i);
        }
        else{
            if(s.empty()) return;
            s.pop();
        }
    }
    return;
}

int main(){
    int a[]={1,0,1,1,0,0,1,0};
    int n=8;
    if(judge(a,n)){
        cout<<"合法"<<endl;
        create(a,n);
    }
    else{
        cout<<"不合法"<<endl;
    }
    return 0;
    
}

/*int main() {
    stack<int> s; // 创建一个空栈
    s.push(1); // 入栈
    s.push(2); // 入栈
    s.push(3); // 入栈
    while (!s.empty()) { // 栈非空
        cout << s.top() << endl; // 输出栈顶元素
        s.pop(); // 出栈
    }
    int i=0;
    cout<<i++<<endl;// 先赋值再加一
    cout<<++i<<endl;// 先加一再赋值
    cout<<i<<endl;
    cout<<i--<<endl;
    cout<<--i<<endl;
    cout<<i<<endl;
    return 0;
}*/