/*
** 目前最快的 N 皇后递归解决方法
** N Queens Problem
** 试探 - 回溯算法，递归实现
*/
//#include "stdafx.h"
#include "iostream"
#include <math.h>
using namespace std;
#include "time.h"

// sum 用来记录皇后放置成功的不同布局数；upperlim 用来标记所有列都已经放置好了皇后。
long sum = 0, upperlim = 1;

// 试探算法从最右边的列开始。
void test(long row, long ld, long rd)
{
    if (row != upperlim)
    {
        // row，ld，rd 进行“或”运算，求得所有可以放置皇后的列，对应位为 0，
        // 然后再取反后“与”上全 1 的数，来求得当前所有可以放置皇后的位置，对应列改为 1
        // 也就是求取当前哪些列可以放置皇后
        long pos = upperlim & ~(row | ld | rd);
        while (pos)    // 0 -- 皇后没有地方可放，回溯
        {
            // 拷贝 pos 最右边为 1 的 bit，其余 bit 置 0
            // 也就是取得可以放皇后的最右边的列
            long p = pos & -pos;

            // 将 pos 最右边为 1 的 bit 清零
            // 也就是为获取下一次的最右可用列使用做准备，
            // 程序将来会回溯到这个位置继续试探
            pos -= p;

            // row + p，将当前列置 1，表示记录这次皇后放置的列。
            // (ld + p) << 1，标记当前皇后左边相邻的列不允许下一个皇后放置。
            // (ld + p) >> 1，标记当前皇后右边相邻的列不允许下一个皇后放置。
            // 此处的移位操作实际上是记录对角线上的限制，只是因为问题都化归
            // 到一行网格上来解决，所以表示为列的限制就可以了。显然，随着移位
            // 在每次选择列之前进行，原来 N×N 网格中某个已放置的皇后针对其对角线
            // 上产生的限制都被记录下来了
            test(row + p, (ld + p) << 1, (rd + p) >> 1);
        }
    }
    else
    {
        // row 的所有位都为 1，即找到了一个成功的布局，回溯
        sum++;
    }
}

int main(int argc, char *argv[])
{
    time_t tm;
    int n =8;

    if (argc != 1)
        n = atoi(argv[1]);
    tm = time(0);

    // 因为整型数的限制，最大只能 32 位，
    // 如果想处理 N 大于 32 的皇后问题，需要
    // 用 bitset 数据结构进行存储
    if ((n < 1) || (n > 32))
    {
        printf(" 只能计算 1-32 之间\n");
        exit(-1);
    }
    printf("%d 皇后\n", n);

    // N 个皇后只需 N 位存储，N 列中某列有皇后则对应 bit 置 1。
    //upperlim = (upperlim << n) - 1;

    upperlim = long(upperlim*pow(2, n) - 1);

    test(0, 0, 0);
    printf("共有 %ld 种排列，计算时间%d秒 \n", sum, (int)(time(0) - tm));
    system("pause");
    return 0;
}