#include <iostream>
#include <stack>
using namespace std;

//�жϳ���ջ�����Ƿ�Ϸ�
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
        cout<<"�Ϸ�"<<endl;
        create(a,n);
    }
    else{
        cout<<"���Ϸ�"<<endl;
    }
    return 0;
    
}

/*int main() {
    stack<int> s; // ����һ����ջ
    s.push(1); // ��ջ
    s.push(2); // ��ջ
    s.push(3); // ��ջ
    while (!s.empty()) { // ջ�ǿ�
        cout << s.top() << endl; // ���ջ��Ԫ��
        s.pop(); // ��ջ
    }
    int i=0;
    cout<<i++<<endl;// �ȸ�ֵ�ټ�һ
    cout<<++i<<endl;// �ȼ�һ�ٸ�ֵ
    cout<<i<<endl;
    cout<<i--<<endl;
    cout<<--i<<endl;
    cout<<i<<endl;
    return 0;
}*/