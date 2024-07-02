#include <iostream>
//#include <cstring>
using namespace std;

//定长顺序存储
#define MAXLEN 255
typedef struct{
    char ch[MAXLEN];
    int length;
}SString;

//堆分配存储
typedef struct{
    char *ch;
    int length;
}HString;

//块链存储
typedef struct Chunk{
    char ch;
    struct Chunk *next;
}Chunk,*ChunkLink;

typedef struct{
    ChunkLink head;
    ChunkLink tail;
    int length;
}BString;

//初始化字符串
void InitString(SString &S){
    S.length = 0;
}

//求字符串长度
int StrLength(SString S){
    return S.length;
}

//判空
bool StrEmpty(SString S){
    return S.length==0;
}


int strlen(const char* chars){
    int i = 0;
    while(chars[i] != '\0')
        i++;
    return i;
}   
//赋值
bool StrAssign(SString &T, const char* chars){ // 注意：这里应该是 const char* 而不是 const char
    if(strlen(chars) > MAXLEN)
        return false;
    T.length = strlen(chars);
    for(int i = 0; i < T.length; i++)
        T.ch[i] = chars[i];
    return true;
}

//复制
bool StrCopy(SString &T,SString S){
    if(S.length>MAXLEN)
        return false;
    T.length = S.length;
    for(int i=0;i<S.length;i++)
        T.ch[i]=S.ch[i];
    return true;
}

//比较
int StrCompany(SString S,SString T){
    for(int i=0;i<S.length&&i<T.length;i++){
        if(S.ch[i]<T.ch[i])
            return -1;
        else if(S.ch[i]>T.ch[i])
            return 1;
    }
    if(S.length<T.length)
        return -1;
    else if(S.length>T.length)
        return 1;
    else
        return 0;
}

//子串
bool SubString(SString &Sub,SString S,int pos,int len){
    if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
        return false;
    Sub.length=len;
    for(int i=pos-1;i<pos+len-1;i++)
        Sub.ch[i-pos+1]=S.ch[i];
    return true;
}

//串连接
bool Concat(SString &T,SString S1,SString S2){
    if(S1.length+S2.length>MAXLEN)
        return false;
    T.length = S1.length+S2.length;
    for(int i=0;i<S1.length;i++)
        T.ch[i]=S1.ch[i];
    for(int i=0;i<S2.length;i++)
        T.ch[i+S1.length]=S2.ch[i];
    return true;
}

//定位
int Index(SString S,SString T){
    int i=1,j=1;
    while(i<=S.length&&j<=T.length){
        if(S.ch[i-1]==T.ch[j-1]){
            i++;
            j++;
        }else{
            i=i-j+2;
            j=1;
        }
    }
    if (j>T.length)
        return i-T.length;
    else
        return 0;
    
}

//清空
bool ClearString(SString &S){
    S.length=0;
    return true;
}

//销毁
bool DestoryString(BString &S){
    ChunkLink p;
    while(S.head){
        p=S.head;
        S.head=S.head->next;
        delete p;
    }
    S.length=0;
    return true;
}

int main()
{
    SString S,T;
    char chars[10]="abcdefg";
    StrAssign(S,chars);
    cout<<S.ch<<endl;
    cout<<StrLength(S)<<endl;
    cout<<StrEmpty(S)<<endl;
    StrCopy(T,S);
    cout<<T.ch<<endl;
    cout<<StrCompany(S,T)<<endl;
    SString Sub;
    SubString(Sub,S,2,3);
    cout<<Sub.ch<<endl;
    SString S1,S2;
    StrAssign(S1,"abc");
    StrAssign(S2,"def");
    SString S3;
    Concat(S3,S1,S2);
    cout<<S3.ch<<endl;
    cout<<Index(S3,S1)<<endl;
    ClearString(S3);
    cout<<"S3:"<<S3.ch<<endl;
    return 0;

}