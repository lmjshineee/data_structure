#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

using namespace std;

typedef pair<int, int> Edge;  // first: 权重，second: 目标节点

vector<Edge> prim(const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<bool> inMST(n, false);  // 标记节点是否已包含在最小生成树中
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;  // 小根堆，优先队列
    vector<Edge> result;  // 存储 MST 的边
    int mstCost = 0;  // 最小生成树的总权重

    pq.push({0, 0});  // 从节点 0 开始，权重为 0

    while (!pq.empty()) {
        Edge top = pq.top();
        pq.pop();

        int weight = top.first;
        int u = top.second;

        if (inMST[u]) continue;  // 如果该节点已在 MST 中，跳过

        inMST[u] = true;  // 标记节点 u 为已访问
        mstCost += weight;

        // 如果 u 不是开始节点，则加入结果中
        if (weight != 0) {
            result.push_back(top);
        }

        // 将 u 的所有相邻节点加入优先队列
        for (const Edge& e : graph[u]) {
            int v = e.second;
            int w = e.first;
            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }

    // 输出 MST 的总权重
    cout << "Total cost of MST: " << mstCost << endl;

    return result;
}

int main() {
    int n = 5;
    vector<vector<Edge>> graph(n);

    // 添加边和权重
    graph[0].push_back({2, 1});
    graph[0].push_back({3, 3});
    graph[1].push_back({2, 0});
    graph[1].push_back({2, 2});
    graph[2].push_back({2, 1});
    graph[2].push_back({3, 3});
    graph[3].push_back({3, 0});
    graph[3].push_back({3, 2});
    graph[3].push_back({1, 4});
    graph[4].push_back({1, 3});
    graph[4].push_back({2, 2});
    graph[2].push_back({2, 4});

    vector<Edge> mst = prim(graph);

    // 输出 MST 的边
    cout << "Edges in the MST:" << endl;
    for (const Edge& e : mst) {
        cout << "Node " << e.second << " - weight: " << e.first << endl;
    }

    return 0;
}