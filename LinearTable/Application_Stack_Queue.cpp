#include<iostream>
#include<stack>
#include<queue>
using namespace std;
typedef int ElemType;

//¿®∫≈∆•≈‰
bool isMatch(char* str){
    stack<char> s;
    for(int i=0;str[i]!='\0';i++){
        if(str[i]=='('||str[i]=='['||str[i]=='{'){
            s.push(str[i]);
        }else if(str[i]==')'){
            if(s.empty()||s.top()!='('){
                return false;
            }
            s.pop();
        }else if(str[i]==']'){
            if(s.empty()||s.top()!='['){
                return false;
            }
            s.pop();
        }else if(str[i]=='}'){
            if(s.empty()||s.top()!='{'){
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

int F(int x){
    return ((x>0)?x*F(x-1):2);
}

int main(){
    char str[]="((()))";
    cout<<isMatch(str)<<endl;
    int i;
    i=F(F(1));
    cout<<i<<endl;
    return 0;
}