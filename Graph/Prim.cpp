#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

using namespace std;

typedef pair<int, int> Edge;  // first: Ȩ�أ�second: Ŀ��ڵ�

vector<Edge> prim(const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<bool> inMST(n, false);  // ��ǽڵ��Ƿ��Ѱ�������С��������
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;  // С���ѣ����ȶ���
    vector<Edge> result;  // �洢 MST �ı�
    int mstCost = 0;  // ��С����������Ȩ��

    pq.push({0, 0});  // �ӽڵ� 0 ��ʼ��Ȩ��Ϊ 0

    while (!pq.empty()) {
        Edge top = pq.top();
        pq.pop();

        int weight = top.first;
        int u = top.second;

        if (inMST[u]) continue;  // ����ýڵ����� MST �У�����

        inMST[u] = true;  // ��ǽڵ� u Ϊ�ѷ���
        mstCost += weight;

        // ��� u ���ǿ�ʼ�ڵ㣬���������
        if (weight != 0) {
            result.push_back(top);
        }

        // �� u ���������ڽڵ�������ȶ���
        for (const Edge& e : graph[u]) {
            int v = e.second;
            int w = e.first;
            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }

    // ��� MST ����Ȩ��
    cout << "Total cost of MST: " << mstCost << endl;

    return result;
}

int main() {
    int n = 5;
    vector<vector<Edge>> graph(n);

    // ��ӱߺ�Ȩ��
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

    // ��� MST �ı�
    cout << "Edges in the MST:" << endl;
    for (const Edge& e : mst) {
        cout << "Node " << e.second << " - weight: " << e.first << endl;
    }

    return 0;
}