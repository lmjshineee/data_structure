#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// 定义边结构体
struct Edge {
    int u; // 起点
    int v; // 终点
    int weight; // 权重
};

bool bellmanFord(int V, int E, vector<Edge>& edges, int start) {
    // 初始化距离数组，设置所有节点距离为正无穷
    vector<int> dist(V, INT_MAX);
    dist[start] = 0;  // 源节点距离为 0

    // 进行 V-1 次迭代，每次尝试松弛所有边
    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // 检查是否存在负权环
    for (int i = 0; i < E; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "图中存在负权环" << endl;
            return false;
        }
    }

    // 输出最终的最短路径
    cout << "从源节点 " << start << " 到各节点的最短距离：" << endl;
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX) {
            cout << "节点 " << i << "：不可达" << endl;
        } else {
            cout << "节点 " << i << "：" << dist[i] << endl;
        }
    }

    return true;
}

int main() {
    // 预定义节点数（V）、边数（E）和源节点
    /*int V = 5; // 节点数
    int E = 8; // 边数
    int start = 0; // 源节点

    // 初始化边数据
    vector<Edge> edges = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };*/
    
    int V = 3; // 节点数
    int E = 3; // 边数
    int start = 0; // 源节点
    vector<Edge> edges = {
        {0, 1, 2},
        {1, 2, 1},
        {2, 0, 7}
    };
    // 调用 Bellman-Ford 算法
    bellmanFord(V, E, edges, start);

    return 0;
}
