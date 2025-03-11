#include<iostream>
#include<cstring>
using namespace std;
 
const int N = 100, M = 100;
 
//读入点数 和 边数
int n, m;
//dis 数组，记录上次状态的 dis 数组
int dis[N];
 
//存储边的结构体数组
struct Edge {
    int a, b, w;
}edges[M];
 
void bellmanford(int x) {
    //初始化 dist 数组
    memset(dis, 0x3f, sizeof(dis));
    dis[x] = 0;// x 是源点
 
    //经过 n - 1 次松驰
    //对所有边进行一次松弛操作，就求出了源点到所有点，经过的边数最多为 1 的最短路
	//对所有边进行两次松弛操作，就求出了源点到所有点，经过的边数最多为 2 的最短路
	//....
	//对所有边进行 n- 1 次松弛操作，就求出了源点到所有点，经过的边数最多为 n - 1 的最短路
    for(int i = 0; i < n - 1; i++) {
        
        //遍历所有边
        for(int j = 0; j < m; j++) {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            if(dis[a] != 0x3f3f3f3f && dis[b] > dis[a] + w) //松弛操作
                dis[b] = dis[a] + w;
        }
    }
    
}
int main() {
    //读入点数，边数
    //cin >> n >> m;
    n=3,m=3;
    //读入边
    /*for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }*/
    edges[0]={0,1,2};
    edges[1]={1,2,1};
    edges[2]={2,0,7};
    int x;
    cin>>x;
    //调用 bellman - ford 算法
    bellmanford(x);
    
    //打印 dis 数组
    for(int i = 1; i <= n; i++)
        cout << dis[i] << " ";
    cout << endl;
 
    system("pause");
    return 0;
}
/*
输出样例
5 5
2 3 2
1 2 -3
1 5 5
4 5 2
3 4 3
输出样例
0 -3 -1 2 4
*/