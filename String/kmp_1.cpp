#include <iostream>
#include <string>
using namespace std;

void get_next(const string &pat, int next[])
{
    const int len = pat.length();
    next[0] = -1;
    int j = 0, lastNext = -1;
    //没错，只要把 len - 1 改成 len 就可以把最后一个也填进去了
    while (j < len)
    {
        if (lastNext == -1 || pat[j] == pat[lastNext])
        {
            ++j; ++lastNext;
            //这里不能优化，因为我们需要 next[i] 保存的就是 i-1 子串的最大匹配
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
    //虚拟的通配符
    next[0] = -1;
    //这里的 ptr 就相当于分析中的 i, lastNext 就是 next[ptr]
    int ptr = 0, lastNext = -1;
    //在循环体中，当前为 ptr 意味着我们的任务是填充 next[ptr + 1] 的值
    //所以 ptr 要小于 len - 1，这样在 ptr = ptr - 2 时，我们就可以填充 next[len - 1] 了
    while (ptr < len - 1)
    {
        //Case 1: p[i] = p[t]，则 next[i + 1] = next[i] + 1
        if (lastNext == -1 || pat[ptr] == pat[lastNext])
        {
            ++ptr;
            ++lastNext;
            //强制要求 pat[i] != pat[next[i]]
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
    //next 数组，next[i] 表示 pat[0~i] 的部分匹配数 (即最长相匹配的真前缀后缀的长度)
    while (i < slen)
    {
        //匹配完了一次
        if (j == plen)
        {
            //题目是从 1 开始的 (该死的!)
            cout << i - j + 1 << endl;
            //next[len] 存储了 pat 最长的匹配前后缀的长度
            //可以想象成 pat[len] 是一个和任何字符都不同的虚拟哨兵
            //这样情况就退化为 pat[len] 和 src[i] 失配的情况了
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
    //洛谷要求的 next 数组和我的不太一样...
    for (int i = 1; i <= plen; ++i)
    {
        //大爷的洛谷，居然末尾也可以有空格害得我白白查了半天不明白是怎么回事
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
    //???谁跟我解释一下为什么 getline(cin, str) 就不行了？
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