#include <iostream>
#include <cstring>
using namespace std;
#define MAXLEN 255

// �����ַ����ṹ��
typedef struct {
    char ch[MAXLEN];
    int length;
} SString;

// �ַ�����ֵ����
bool StrAssign(SString &T, const char* chars) {
    if (strlen(chars) >= MAXLEN)
        return false;
    T.length = strlen(chars);
    strncpy(T.ch, chars, T.length);
    T.ch[T.length] = '\0'; // ȷ���ַ����� null ��β
    return true;
}

// ��ȡ next ����
void getNext(const SString &T, int next[]) {
    int i = 1, j = 0;
    next[0] = -1; // ��һ��Ԫ����Ϊ -1
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

// KMP ƥ�亯��
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
        return -1; // δ�ҵ�ƥ�䣬���� -1
}

// �Ľ��� next ������㺯��
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

// ����һ���ַ����ṹ��
typedef struct{
    char ch[MAXLEN]; // �ַ����飬���ڴ洢�ַ���
    int length; // �ַ�����ʵ�ʳ���
}SString;  

// �ַ�����ֵ����
bool StrAssign(SString &T, const char* chars){ // ע�⣺����Ӧ���� const char* ������ const char
    if(strlen(chars) > MAXLEN) // ��������ַ������ȳ���������ƣ����� false
        return false;
    T.length = strlen(chars); // �����ַ�����ʵ�ʳ���
    for(int i = 0; i < T.length; i++) // �������ַ�����ÿ���ַ����Ƶ��ṹ����
        T.ch[i] = chars[i];
    return true; // ��ֵ�ɹ������� true
}

// KMP �㷨
// 1. ��ȡ next ����
void get_next(SString T,int next[]){
    int i = 1,j = 0; // i ������ָ�룬j ��ģʽ��ָ��
    next[1] = 0; // next ����ĵ�һ��Ԫ����Ϊ -1
    while(i < T.length){ // ����ģʽ��
        if(j == 0 || T.ch[i] == T.ch[j]){ // ��� j Ϊ -1 ��ǰ�ַ�ƥ��
            ++i; // ����ָ�����
            ++j; // ģʽ��ָ�����
            next[i] = j; // ���� next ֵ
        }else
            j = next[j]; // ģʽ��ָ�����
    }
}

// 2. KMP ƥ�亯��
int Index_KMP(SString S,SString T,int next[]){
    int i = 1,j = 1; // i ������ָ�룬j ��ģʽ��ָ��
    while(i < S.length&&j < T.length){ // ��������
        if(j == 0 || S.ch[i] == T.ch[j]){ // ��� j Ϊ -1 ��ǰ�ַ�ƥ��
            ++i; // ����ָ�����
            ++j; // ģʽ��ָ�����
        }
        else
            j = next[j]; // ģʽ��ָ�����
    }
    if(j>T.length) // ���ģʽ����ȫƥ��
        return i-T.length; // ����ƥ�����ʼλ��
   else
        return 0; // δ�ҵ�ƥ�䣬���� 0
}

// �Ľ��� next ������㺯��
void get_nextval(SString T,int nextval[]){
    int i=1,j=0; // i ������ָ�룬j ��ģʽ��ָ��
    nextval[1]=0; // nextval ����ĵڶ���Ԫ����Ϊ 0
    while(i<T.length){ // ����ģʽ��
        if(j==0 || T.ch[i]==T.ch[j]){ // ��� j Ϊ 0 ��ǰ�ַ�ƥ��
            ++i; // ����ָ�����
            ++j; // ģʽ��ָ�����
            if(T.ch[i]!=T.ch[j]) // �����һ���ַ���ƥ��
                nextval[i]=j; // ���� nextval ֵ
            else
                nextval[i]=nextval[j]; // ��������Ϊǰһ�� nextval ֵ
        }else
            j=nextval[j]; // ģʽ��ָ�����
    }
}

int main(){
    SString S,T; // ���������ַ����ṹ��
    StrAssign(S,"abcababcacaaa"); // ��������ֵ
    StrAssign(T,"abcac"); // ��ģʽ����ֵ
    cout<<S.length<<" "<<T.length<<endl; // ���������ģʽ���ĳ���

    int next[T.length],nextval[T.length]; // ���� next �� nextval ����
    //get_nextval(T,nextval); // ����Ľ��� next ���飨ע�͵��ˣ�
    get_next(T,next); // ����ԭʼ�� next ����
    cout << Index_KMP(S,T,next) << endl; // ʹ�� KMP �㷨����ƥ�䲢������
    //cout << Index_KMP(S,T,nextval) << endl; // ʹ�øĽ��� KMP �㷨����ƥ�䲢��������ע�͵��ˣ�
    return 0;
}*/