#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;

    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    // 查找操作，带路径压缩
    int find(int p) {
        if (parent[p] != p) {
            parent[p] = find(parent[p]);
        }
        return parent[p];
    }

    // 合并操作，按秩合并
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
                rank[rootP] += 1;
            }
        }
    }
};

int main() {
    UnionFind uf(5);
    
    // 合并集合
    uf.unionSets(0, 1);
    uf.unionSets(1, 2);
    uf.unionSets(3, 4);
    
    // 查找集合代表
    cout << uf.find(0) << endl;  // 输出 0
    cout << uf.find(1) << endl;  // 输出 0
    cout << uf.find(2) << endl;  // 输出 0
    cout << uf.find(3) << endl;  // 输出 3
    cout << uf.find(4) << endl;  // 输出 3
    
    // 判断两个元素是否属于同一集合
    cout << (uf.find(0) == uf.find(2)) << endl;  // 输出 1（true）
    cout << (uf.find(0) == uf.find(4)) << endl;  // 输出 0（false）
    
    return 0;
}
