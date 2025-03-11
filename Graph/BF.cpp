#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// ����߽ṹ��
struct Edge {
    int u; // ���
    int v; // �յ�
    int weight; // Ȩ��
};

bool bellmanFord(int V, int E, vector<Edge>& edges, int start) {
    // ��ʼ���������飬�������нڵ����Ϊ������
    vector<int> dist(V, INT_MAX);
    dist[start] = 0;  // Դ�ڵ����Ϊ 0

    // ���� V-1 �ε�����ÿ�γ����ɳ����б�
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

    // ����Ƿ���ڸ�Ȩ��
    for (int i = 0; i < E; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "ͼ�д��ڸ�Ȩ��" << endl;
            return false;
        }
    }

    // ������յ����·��
    cout << "��Դ�ڵ� " << start << " �����ڵ����̾��룺" << endl;
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX) {
            cout << "�ڵ� " << i << "�����ɴ�" << endl;
        } else {
            cout << "�ڵ� " << i << "��" << dist[i] << endl;
        }
    }

    return true;
}

int main() {
    // Ԥ����ڵ�����V����������E����Դ�ڵ�
    /*int V = 5; // �ڵ���
    int E = 8; // ����
    int start = 0; // Դ�ڵ�

    // ��ʼ��������
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
    
    int V = 3; // �ڵ���
    int E = 3; // ����
    int start = 0; // Դ�ڵ�
    vector<Edge> edges = {
        {0, 1, 2},
        {1, 2, 1},
        {2, 0, 7}
    };
    // ���� Bellman-Ford �㷨
    bellmanFord(V, E, edges, start);

    return 0;
}
