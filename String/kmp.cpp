#include <iostream>
#include <string.h>
using namespace std;
#define MAXLEN 255

typedef struct{
    char ch[MAXLEN];
    int length;
}SString;  
//赋值
bool StrAssign(SString &T, const char* chars){ // 注意：这里应该是 const char* 而不是 const char
    if(strlen(chars) > MAXLEN)
        return false;
    T.length = strlen(chars);
    for(int i = 0; i < T.length; i++)
        T.ch[i] = chars[i];
    return true;
}

//KMP 算法
//1.get_next
void get_next(SString T,int next[]){
    int i = 1,j = 0;
    next[1] = 0;
    while(i < T.length){
        if(j == 0 || T.ch[i] == T.ch[j]){
            ++i;
            ++j;
            next[i] = j;
        }else
            j = next[j];
    }

}

//2.KMP
int Index_KMP(SString S,SString T,int next[]){
    int i = 1,j = 1;
    while(i <= S.length && j <=T.length){
        if(j == 0 || S.ch[i] == T.ch[j]){
            ++i;
            ++j;
        }
        else
            j = next[j];
    }
    if(j>T.length)
        return i-T.length;
   else
        return 0;
}


// 改进
void get_nextval(SString T,int nextval[]){
    int i=1,j=0;
    nextval[1]=0;
    while(i<T.length){
        if(j==0 || T.ch[i]==T.ch[j]){
            ++i;
            ++j;
            if(T.ch[i]!=T.ch[j])
                nextval[i]=j;
            else
                nextval[i]=nextval[j];
        }else
            j=nextval[j];
    }
}

int main(){
    SString S,T;
    StrAssign(S,"abcababcacaaa");
    StrAssign(T,"abcac");
    int next[MAXLEN],nextval[MAXLEN];
    //get_nextval(T,nextval);
    get_next(T,next);
    cout << Index_KMP(S,T,next) << endl;
    //cout << Index_KMP(S,T,nextval) << endl;
    return 0;
}