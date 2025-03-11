#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, pair<int, int>> Edge;  // first: 权重，second: (节点 u, 节点 v)

class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int p) {
        if (parent[p] != p) {
            parent[p] = find(parent[p]);
        }
        return parent[p];
    }

    void unionSets(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP != rootQ) {
            if (rank[rootP] > rank[rootQ]) {
                parent[rootQ] = rootP;
            } else if (rank[rootP] < rank[rootQ]) {
                parent[rootP] = rootQ;
            } else {
                parent[rootQ] = rootP;
                rank[rootP]++;
            }
        }
    }
};

vector<Edge> kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    vector<Edge> result;

    for (const Edge& edge : edges) {
        int weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if (uf.find(u) != uf.find(v)) {
            uf.unionSets(u, v);
            result.push_back(edge);
        }
    }

    return result;
}

int main() {
    int n = 5;
    vector<Edge> edges = {
        {2, {0, 1}},
        {2, {1, 2}},
        {3, {0, 3}},
        {3, {2, 3}},
        {1, {3, 4}}
    };

    vector<Edge> mst = kruskal(n, edges);

    for (const Edge& e : mst) {
        cout << "(" << e.second.first << ", " << e.second.second << ") ";
    }
    cout << endl;

    return 0;
}
