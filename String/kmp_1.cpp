#include <iostream>
#include <string>
using namespace std;

void get_next(const string &pat, int next[])
{
    const int len = pat.length();
    next[0] = -1;
    int j = 0, lastNext = -1;
    //û��ֻҪ�� len - 1 �ĳ� len �Ϳ��԰����һ��Ҳ���ȥ��
    while (j < len)
    {
        if (lastNext == -1 || pat[j] == pat[lastNext])
        {
            ++j; ++lastNext;
            //���ﲻ���Ż�����Ϊ������Ҫ next[i] ����ľ��� i-1 �Ӵ������ƥ��
            //next[j] = (pat[j] == pat[lastNext])? next[lastNext] : lastNext;
            next[j] = lastNext;
        }
        else
            lastNext = next[lastNext];
    }
}

void get_nextval(const string &pat, int next[])
{
    const int len = pat.length();
    //�����ͨ���
    next[0] = -1;
    //����� ptr ���൱�ڷ����е� i, lastNext ���� next[ptr]
    int ptr = 0, lastNext = -1;
    //��ѭ�����У���ǰΪ ptr ��ζ�����ǵ���������� next[ptr + 1] ��ֵ
    //���� ptr ҪС�� len - 1�������� ptr = ptr - 2 ʱ�����ǾͿ������ next[len - 1] ��
    while (ptr < len - 1)
    {
        //Case 1: p[i] = p[t]���� next[i + 1] = next[i] + 1
        if (lastNext == -1 || pat[ptr] == pat[lastNext])
        {
            ++ptr;
            ++lastNext;
            //ǿ��Ҫ�� pat[i] != pat[next[i]]
            next[ptr] = (pat[ptr] == pat[lastNext])? next[lastNext] : lastNext;
        }
        else
            lastNext = next[lastNext];

    }
}

void KMP(const string &src, const string &pat,int next[])
{
    const int slen = src.length();
    const int plen = pat.length();
    int i = 0, j = 0;
    //next ���飬next[i] ��ʾ pat[0~i] �Ĳ���ƥ���� (�����ƥ�����ǰ׺��׺�ĳ���)
    while (i < slen)
    {
        //ƥ������һ��
        if (j == plen)
        {
            //��Ŀ�Ǵ� 1 ��ʼ�� (������!)
            cout << i - j + 1 << endl;
            //next[len] �洢�� pat ���ƥ��ǰ��׺�ĳ���
            //��������� pat[len] ��һ�����κ��ַ�����ͬ�������ڱ�
            //����������˻�Ϊ pat[len] �� src[i] ʧ��������
            j = next[plen];
        }
        else if (j == -1 || src[i] == pat[j])
        {
            ++i;
            ++j;
        }
        else
            j = next[j];
    }
    if (j == plen)
        cout << i - j + 1 << endl;
    //���Ҫ��� next ������ҵĲ�̫һ��...
    for (int i = 1; i <= plen; ++i)
    {
        //��ү����ȣ���ȻĩβҲ�����пո񺦵��Ұװײ��˰��첻��������ô����
        // if (i != 1)
        //     cout << " ";
        cout << next[i] << " ";
    }
    cout<<endl;
}

int main()
{
    string src;
    string pat;
    //???˭���ҽ���һ��Ϊʲô getline(cin, str) �Ͳ����ˣ�
    src="abBBBabababcaaaaaaba";
    pat="ababca";
    //cin >> src >> pat;

    int next[pat.length() + 1];
    int nextval[pat.length() + 1];
    get_next(pat, next);
    get_nextval(pat, nextval);
    KMP(src, pat, next);
    KMP(src, pat, nextval);
    return 0;
}