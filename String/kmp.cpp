#include <iostream>
#include <cstring>
using namespace std;
#define MAXLEN 255

// 定义字符串结构体
typedef struct {
    char ch[MAXLEN];
    int length;
} SString;

// 字符串赋值函数
bool StrAssign(SString &T, const char* chars) {
    if (strlen(chars) >= MAXLEN)
        return false;
    T.length = strlen(chars);
    strncpy(T.ch, chars, T.length);
    T.ch[T.length] = '\0'; // 确保字符串以 null 结尾
    return true;
}

// 获取 next 数组
void getNext(const SString &T, int next[]) {
    int i = 1, j = 0;
    next[0] = -1; // 第一个元素设为 -1
    while (i < T.length) {
        if (j == -1 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

// KMP 匹配函数
int indexKMP(const SString &S, const SString &T, const int next[]) {
    int i = 0, j = 0;
    while (i < S.length && j < T.length) {
        if (j == -1 || S.ch[i] == T.ch[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    if (j >= T.length)
        return i - T.length;
    else
        return -1; // 未找到匹配，返回 -1
}

// 改进的 next 数组计算函数
void getNextval(const SString &T, int nextval[]) {
    int i = 1, j = 0;
    nextval[0] = -1;
    while (i < T.length) {
        if (j == -1 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            if (T.ch[i] != T.ch[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        } else {
            j = nextval[j];
        }
    }
}

int main() {
    SString S, T;
    StrAssign(S, "abcababcacaaa");
    StrAssign(T, "abcac");
    cout << "Main string length: " << S.length << ", Pattern length: " << T.length << endl;

    int next[MAXLEN], nextval[MAXLEN];
    getNext(T, next);
    getNextval(T, nextval);

    int result = indexKMP(S, T, next);
    for(int i = 0; i < T.length; i++)
        cout << next[i] << " ";
    cout << endl;
    for(int i = 0; i < T.length; i++)
        cout << nextval[i] << " ";
    cout << endl;
    cout << "KMP result (using next): " << result << endl;

    result = indexKMP(S, T, nextval);
    cout << "KMP result (using nextval): " << result << endl;

    return 0;
}

/*#include <iostream>
#include <string.h>
using namespace std;
#define MAXLEN 255

// 定义一个字符串结构体
typedef struct{
    char ch[MAXLEN]; // 字符数组，用于存储字符串
    int length; // 字符串的实际长度
}SString;  

// 字符串赋值函数
bool StrAssign(SString &T, const char* chars){ // 注意：这里应该是 const char* 而不是 const char
    if(strlen(chars) > MAXLEN) // 如果输入字符串长度超过最大限制，返回 false
        return false;
    T.length = strlen(chars); // 设置字符串的实际长度
    for(int i = 0; i < T.length; i++) // 将输入字符串的每个字符复制到结构体中
        T.ch[i] = chars[i];
    return true; // 赋值成功，返回 true
}

// KMP 算法
// 1. 获取 next 数组
void get_next(SString T,int next[]){
    int i = 1,j = 0; // i 是主串指针，j 是模式串指针
    next[1] = 0; // next 数组的第一个元素设为 -1
    while(i < T.length){ // 遍历模式串
        if(j == 0 || T.ch[i] == T.ch[j]){ // 如果 j 为 -1 或当前字符匹配
            ++i; // 主串指针后移
            ++j; // 模式串指针后移
            next[i] = j; // 设置 next 值
        }else
            j = next[j]; // 模式串指针回溯
    }
}

// 2. KMP 匹配函数
int Index_KMP(SString S,SString T,int next[]){
    int i = 1,j = 1; // i 是主串指针，j 是模式串指针
    while(i < S.length&&j < T.length){ // 遍历主串
        if(j == 0 || S.ch[i] == T.ch[j]){ // 如果 j 为 -1 或当前字符匹配
            ++i; // 主串指针后移
            ++j; // 模式串指针后移
        }
        else
            j = next[j]; // 模式串指针回溯
    }
    if(j>T.length) // 如果模式串完全匹配
        return i-T.length; // 返回匹配的起始位置
   else
        return 0; // 未找到匹配，返回 0
}

// 改进的 next 数组计算函数
void get_nextval(SString T,int nextval[]){
    int i=1,j=0; // i 是主串指针，j 是模式串指针
    nextval[1]=0; // nextval 数组的第二个元素设为 0
    while(i<T.length){ // 遍历模式串
        if(j==0 || T.ch[i]==T.ch[j]){ // 如果 j 为 0 或当前字符匹配
            ++i; // 主串指针后移
            ++j; // 模式串指针后移
            if(T.ch[i]!=T.ch[j]) // 如果下一个字符不匹配
                nextval[i]=j; // 设置 nextval 值
            else
                nextval[i]=nextval[j]; // 否则设置为前一个 nextval 值
        }else
            j=nextval[j]; // 模式串指针回溯
    }
}

int main(){
    SString S,T; // 定义两个字符串结构体
    StrAssign(S,"abcababcacaaa"); // 给主串赋值
    StrAssign(T,"abcac"); // 给模式串赋值
    cout<<S.length<<" "<<T.length<<endl; // 输出主串和模式串的长度

    int next[T.length],nextval[T.length]; // 定义 next 和 nextval 数组
    //get_nextval(T,nextval); // 计算改进的 next 数组（注释掉了）
    get_next(T,next); // 计算原始的 next 数组
    cout << Index_KMP(S,T,next) << endl; // 使用 KMP 算法进行匹配并输出结果
    //cout << Index_KMP(S,T,nextval) << endl; // 使用改进的 KMP 算法进行匹配并输出结果（注释掉了）
    return 0;
}*/