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

    // ���Ҳ�������·��ѹ��
    int find(int p) {
        if (parent[p] != p) {
            parent[p] = find(parent[p]);
        }
        return parent[p];
    }

    // �ϲ����������Ⱥϲ�
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
    
    // �ϲ�����
    uf.unionSets(0, 1);
    uf.unionSets(1, 2);
    uf.unionSets(3, 4);
    
    // ���Ҽ��ϴ���
    cout << uf.find(0) << endl;  // ��� 0
    cout << uf.find(1) << endl;  // ��� 0
    cout << uf.find(2) << endl;  // ��� 0
    cout << uf.find(3) << endl;  // ��� 3
    cout << uf.find(4) << endl;  // ��� 3
    
    // �ж�����Ԫ���Ƿ�����ͬһ����
    cout << (uf.find(0) == uf.find(2)) << endl;  // ��� 1��true��
    cout << (uf.find(0) == uf.find(4)) << endl;  // ��� 0��false��
    
    return 0;
}
