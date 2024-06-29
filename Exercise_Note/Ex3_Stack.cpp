#include <iostream>
#include <stack>

using namespace std;

typedef struct Node {
    string data;
    Node* next;
}Node;
//03 isLegal.cpp
//04  判断对称
bool isSymmetry(Node* L){
    stack<Node*> s;
    Node* p=L->next;
    while(p!=NULL){
        s.push(p);
        p=p->next;
    }
    p=L->next;
    while(p!=NULL){
        if(p->data!=s.top()->data) return false;
        s.pop();
        p=p->next;
    }
    return true;
}
//05 ShareStack.cpp

int main() {
    
    return 0;
}

//03
bool judge(char A[]){
    int i=0,j=0,k=0;
    while(A[i]!='\0'){
        switch(A[i]){
            case 'I': j++;break;
            case 'O':k++;
        }
        i++;
    }
    if(j!=k){
        printf("序号非法\n");
        return false;
    }
    else{
        printf("序号合法\n");
        return true;
    }
}

//04 duichen
bool dc(LinkList L,int n){
    int i;
    char s[n/2];
    LNode *p=L->next;
    for(i=0;i<n/2;i++){
        s[i]=p->data;
        p=p->next;
    }
    i--;
    if(n%2==1)
        p=p->next;
    while(p!=NULL&&s[i]==p->data){
        i--;
        p=p->next;
    }
    if(i==-1)
        return true;
    else
        return false;
}