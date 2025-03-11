#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

using namespace std;

typedef pair<int, int> Edge;  // first: ���룬second: �ڵ�

vector<int> dijkstra(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);  // �������飬��ʼ��Ϊ�����
    vector<bool> visited(n, false);  // ���ʱ������
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;  // С����

    dist[start] = 0;  // ������Ϊ 0
    pq.push({0, start});

    while (!pq.empty()) {
        Edge top = pq.top();
        pq.pop();

        int u = top.second;
        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& e : graph[u]) {
            int v = e.second;
            int weight = e.first;

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n = 5;
    vector<vector<Edge>> graph(n);

    // ��ӱߺ�Ȩ��
    graph[0].push_back({10, 1});
    graph[0].push_back({3, 2});
    graph[1].push_back({1, 2});
    graph[1].push_back({2, 3});
    graph[2].push_back({4, 1});
    graph[2].push_back({8, 3});
    graph[2].push_back({2, 4});
    graph[3].push_back({7, 4});
    graph[4].push_back({9, 3});

    int start = 0;  // ���

    vector<int> distances = dijkstra(graph, start);

    // ���ÿ���ڵ����̾���
    cout << "Shortest distances from node " << start << ":" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Node " << i << " : " << distances[i] << endl;
    }

    return 0;
}

