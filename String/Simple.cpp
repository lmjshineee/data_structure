#include <iostream>
#include <cstring>
using namespace std;

int violence(char *pat, char *str){
    int i=0,j=0;
    while(i<strlen(str)&&j<strlen(pat)){
        if(str[i]==pat[j]){
            i++;
            j++;
        }else{
            i=i-j+1; // �������˵��ϴ�ƥ����λ����һλ
            j=0;
        }
    }
    if(j==strlen(pat))
        return i-j;
    else
        return -1;
}

int main(){
    char pat[]="abcac";
    char str[]="ababcabcacbab";
    cout<<violence(pat,str);
    return 0;
}