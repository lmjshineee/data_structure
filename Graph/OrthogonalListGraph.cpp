#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 边结点
struct ArcNode {
    int tailvex, headvex;  // 弧尾和弧头顶点的位置
    ArcNode *hlink, *tlink;  // 弧头相同和弧尾相同的弧的链域
    int weight;  // 权重

    ArcNode(int tail, int head, int w) : tailvex(tail), headvex(head), hlink(nullptr), tlink(nullptr), weight(w) {}
};

// 顶点结点
struct VNode {
    char data;
    ArcNode *firstin, *firstout;  // 指向第一条入弧和出弧

    VNode() : firstin(nullptr), firstout(nullptr) {}
};

class OrthogonalListGraph {
private:
    vector<VNode> vertices;
    int vexnum, arcnum;

public:
    OrthogonalListGraph() : vexnum(0), arcnum(0) {}

    void CreateDefaultGraph() {
        vexnum = 5;
        arcnum = 7;
        vertices.resize(vexnum);

        // 设置顶点
        vertices[0].data = 'A';
        vertices[1].data = 'B';
        vertices[2].data = 'C';
        vertices[3].data = 'D';
        vertices[4].data = 'E';

        // 添加边
        InsertArc(0, 1, 1); // A->B
        InsertArc(0, 2, 1); // A->C
        InsertArc(1, 2, 1); // B->C
        InsertArc(1, 3, 1); // B->D
        InsertArc(2, 3, 1); // C->D
        InsertArc(3, 4, 1); // D->E
        InsertArc(4, 0, 1); // E->A

        cout << "默认图已创建。" << endl;
    }

    void InsertArc(int tail, int head, int weight) {
        ArcNode* p = new ArcNode(tail, head, weight);

        // 插入到出弧链表
        p->tlink = vertices[tail].firstout;
        vertices[tail].firstout = p;

        // 插入到入弧链表
        p->hlink = vertices[head].firstin;
        vertices[head].firstin = p;
    }

    void PrintGraph() const {
        for (int i = 0; i < vexnum; i++) {
            cout << vertices[i].data << " 出弧：";
            ArcNode* p = vertices[i].firstout;
            while (p) {
                cout << vertices[p->headvex].data << "(" << p->weight << ") ";
                p = p->tlink;
            }
            cout << endl;

            cout << vertices[i].data << " 入弧：";
            p = vertices[i].firstin;
            while (p) {
                cout << vertices[p->tailvex].data << "(" << p->weight << ") ";
                p = p->hlink;
            }
            cout << endl << endl;
        }
    }

    void DFS(int v, vector<bool>& visited) const {
        cout << vertices[v].data << " ";
        visited[v] = true;
        for (ArcNode* p = vertices[v].firstout; p; p = p->tlink) {
            if (!visited[p->headvex]) {
                DFS(p->headvex, visited);
            }
        }
    }

    void DFSTraversal() const {
        vector<bool> visited(vexnum, false);
        for (int i = 0; i < vexnum; i++) {
            if (!visited[i]) {
                DFS(i, visited);
            }
        }
        cout << endl;
    }

    void BFS(int start) const {
        vector<bool> visited(vexnum, false);
        queue<int> Q;
        
        cout << vertices[start].data << " ";
        visited[start] = true;
        Q.push(start);
        
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (ArcNode* p = vertices[v].firstout; p; p = p->tlink) {
                int w = p->headvex;
                if (!visited[w]) {
                    cout << vertices[w].data << " ";
                    visited[w] = true;
                    Q.push(w);
                }
            }
        }
        cout << endl;
    }

    void BFSTraversal() const {
        for (int i = 0; i < vexnum; i++) {
            BFS(i);
        }
    }
};

int main() {
    OrthogonalListGraph G;
    G.CreateDefaultGraph();
    
    cout << "图的结构：" << endl;
    G.PrintGraph();

    cout << "DFS 遍历结果：";
    G.DFSTraversal();
    
    cout << "BFS 遍历结果：";
    G.BFSTraversal();

    return 0;
}