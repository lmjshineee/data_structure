#include <iostream>
#include <queue>
#include <climits>
#include <vector>
using namespace std;

typedef char VertexType;
typedef int EdgeType;

struct ArcNode {
    int adjvex;
    ArcNode *next;
    EdgeType weight;  // 添加边权值
};

struct VNode {
    VertexType data;
    ArcNode *firstarc;
};

class ALGraph {
private:
    vector<VNode> vertices;
    int vexnum, arcnum;

public:
    ALGraph() : vexnum(0), arcnum(0) {}

    ~ALGraph() {
        for (int i = 0; i < vexnum; i++) {
            ArcNode *p = vertices[i].firstarc;
            while (p) {
                ArcNode *q = p;
                p = p->next;
                delete q;
            }
        }
    }

    // 新增方法：创建一个默认的图结构
    void CreateDefaultGraph() {
        // 清除之前的数据
        vertices.clear();
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
        InsertEdge(0, 1, 1); // A-B
        InsertEdge(0, 2, 1); // A-C
        InsertEdge(1, 2, 1); // B-C
        InsertEdge(1, 3, 1); // B-D
        InsertEdge(2, 3, 1); // C-D
        InsertEdge(3, 4, 1); // D-E
        InsertEdge(4, 0, 1); // E-A

        cout << "默认图已创建。" << endl;
    }

    // 打印图的结构
    void PrintGraph() const {
        for (int i = 0; i < vexnum; i++) {
            cout << vertices[i].data << ": ";
            ArcNode* p = vertices[i].firstarc;
            while (p) {
                cout << vertices[p->adjvex].data << "(" << p->weight << ") ";
                p = p->next;
            }
            cout << endl;
        }
    }

    void CreateALGraph() {
        cout << "请输入顶点数和边数：";
        cin >> vexnum >> arcnum;
        vertices.resize(vexnum);

        cout << "请输入顶点信息：";
        for (int i = 0; i < vexnum; i++) {
            cin >> vertices[i].data;
            vertices[i].firstarc = nullptr;
        }

        cout << "请输入边的信息：" << endl;
        for (int k = 0; k < arcnum; k++) {
            int v1, v2, weight;
            cout << "请输入边依附的顶点和权重：";
            cin >> v1 >> v2 >> weight;
            InsertEdge(v1, v2, weight);
            InsertEdge(v2, v1, weight);  // 无向图需要添加两次
        }
    }

    bool Adjacent(int v, int w) const {
        ArcNode *p = vertices[v].firstarc;
        while (p) {
            if (p->adjvex == w) return true;
            p = p->next;
        }
        return false;
    }

    void Neighbors(int v) const {
        ArcNode *p = vertices[v].firstarc;
        while (p) {
            cout << vertices[p->adjvex].data << "(" << p->weight << ") ";
            p = p->next;
        }
        cout << endl;
    }

    bool InsertVertex(VertexType v) {
        if (vexnum == vertices.size()) return false;
        vertices[vexnum++].data = v;
        return true;
    }

    bool DeleteVertex(VertexType v) {
        int i = GetVertexPos(v);
        if (i == -1) return false;

        while (vertices[i].firstarc) {
            ArcNode *p = vertices[i].firstarc;
            vertices[i].firstarc = p->next;
            delete p;
        }

        for (int j = 0; j < vexnum; j++) {
            if (j != i) {
                RemoveEdge(j, i);
            }
        }

        vertices[i] = vertices[--vexnum];
        return true;
    }

    bool InsertEdge(int v, int w, EdgeType weight) {
        if (v < 0 || v >= vexnum || w < 0 || w >= vexnum) return false;
        if (Adjacent(v, w)) return false;

        ArcNode *p = new ArcNode{w, vertices[v].firstarc, weight};
        vertices[v].firstarc = p;
        arcnum++;
        return true;
    }

    bool RemoveEdge(int v, int w) {
        if (v < 0 || v >= vexnum || w < 0 || w >= vexnum) return false;

        ArcNode *p = vertices[v].firstarc, *q = nullptr;
        while (p && p->adjvex != w) {
            q = p;
            p = p->next;
        }
        if (!p) return false;

        if (q) q->next = p->next;
        else vertices[v].firstarc = p->next;

        delete p;
        arcnum--;
        return true;
    }

    int FirstNeighbor(int v) const {
        if (v < 0 || v >= vexnum) return -1;
        ArcNode *p = vertices[v].firstarc;
        return p ? p->adjvex : -1;
    }

    int NextNeighbor(int v, int w) const {
        if (v < 0 || v >= vexnum) return -1;
        ArcNode *p = vertices[v].firstarc;
        while (p && p->adjvex != w) p = p->next;
        return (p && p->next) ? p->next->adjvex : -1;
    }

    EdgeType GetEdgeValue(int v, int w) const {
        if (v < 0 || v >= vexnum || w < 0 || w >= vexnum) return INT_MAX;
        ArcNode *p = vertices[v].firstarc;
        while (p && p->adjvex != w) p = p->next;
        return p ? p->weight : INT_MAX;
    }

    bool SetEdgeValue(int v, int w, EdgeType value) {
        if (v < 0 || v >= vexnum || w < 0 || w >= vexnum) return false;
        ArcNode *p = vertices[v].firstarc;
        while (p && p->adjvex != w) p = p->next;
        if (p) {
            p->weight = value;
            return true;
        }
        return false;
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
            for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) {
                if (!visited[w]) {
                    cout << vertices[w].data << " ";
                    visited[w] = true;
                    Q.push(w);
                }
            }
        }
        cout << endl;
    }

    void DFS(int v, vector<bool>& visited) const {
        cout << vertices[v].data << " ";
        visited[v] = true;
        for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) {
            if (!visited[w]) {
                DFS(w, visited);
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

    void BFSTraversal() const {
        for (int i = 0; i < vexnum; i++) {
            BFS(i);
        }
    }

private:
    int GetVertexPos(VertexType v) const {
        for (int i = 0; i < vexnum; i++) {
            if (vertices[i].data == v) return i;
        }
        return -1;
    }
};

int main() {
    ALGraph G;
    G.CreateDefaultGraph();
    cout << "图的结构：" << endl;
    G.PrintGraph();
    cout << "DFS 遍历结果：";
    G.DFSTraversal();
    cout << "BFS 遍历结果：";
    G.BFSTraversal();
    return 0;
}