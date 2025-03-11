#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *next;
    EdgeType weight;  // 添加边权值
} ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

// 创建默认图
void CreateDefaultGraph(ALGraph &G) {
    G.vexnum = 5;
    G.arcnum = 7;

    // 初始化顶点
    char vertexData[] = {'A', 'B', 'C', 'D', 'E'};
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].data = vertexData[i];
        G.vertices[i].firstarc = nullptr;
    }

    // 添加边
    struct Edge {
        int v1, v2;
        EdgeType weight;
    } edges[] = {
        {0, 1, 1}, {0, 2, 1},  // A-B, A-C
        {1, 2, 1}, {1, 3, 1},  // B-C, B-D
        {2, 3, 1},             // C-D
        {3, 4, 1},             // D-E
        {4, 0, 1}              // E-A
    };

    for (const auto &edge : edges) {
        ArcNode *p = new ArcNode{edge.v2, G.vertices[edge.v1].firstarc, edge.weight};
        G.vertices[edge.v1].firstarc = p;

        // 如果是无向图，需要添加反向边
        p = new ArcNode{edge.v1, G.vertices[edge.v2].firstarc, edge.weight};
        G.vertices[edge.v2].firstarc = p;
    }

    cout << "默认图已创建。" << endl;
}

// ... (其他函数保持不变)

// 打印图结构
void PrintGraph(const ALGraph &G) {
    for (int i = 0; i < G.vexnum; i++) {
        cout << G.vertices[i].data << ": ";
        ArcNode *p = G.vertices[i].firstarc;
        while (p) {
            cout << G.vertices[p->adjvex].data << "(" << p->weight << ") ";
            p = p->next;
        }
        cout << endl;
    }
}

// 创建图
void CreateALGraph(ALGraph &G) {
    cout << "请输入顶点数和边数：";
    cin >> G.vexnum >> G.arcnum;
    
    cout << "请输入顶点信息：";
    for (int i = 0; i < G.vexnum; i++) {
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = nullptr;
    }
    
    cout << "请输入边的信息：" << endl;
    for (int k = 0; k < G.arcnum; k++) {
        int v1, v2, weight;
        cout << "请输入边依附的顶点和权重：";
        cin >> v1 >> v2 >> weight;
        
        ArcNode *p = new ArcNode{v2, G.vertices[v1].firstarc, weight};
        G.vertices[v1].firstarc = p;
        
        // 如果是无向图，需要添加反向边
        p = new ArcNode{v1, G.vertices[v2].firstarc, weight};
        G.vertices[v2].firstarc = p;
    }
}

// 判断两个顶点是否邻接
bool Adjacent(const ALGraph &G, int v, int w) {
    ArcNode *p = G.vertices[v].firstarc;
    while (p) {
        if (p->adjvex == w) return true;
        p = p->next;
    }
    return false;
}

// 获取顶点的所有邻接点
vector<int> Neighbors(const ALGraph &G, int v) {
    vector<int> neighbors;
    ArcNode *p = G.vertices[v].firstarc;
    while (p) {
        neighbors.push_back(p->adjvex);
        p = p->next;
    }
    return neighbors;
}

// 插入顶点
bool InsertVertex(ALGraph &G, VertexType v) {
    if (G.vexnum == MaxVertexNum) return false;
    G.vertices[G.vexnum++].data = v;
    return true;
}

// 删除顶点
bool DeleteVertex(ALGraph &G, VertexType v) {
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data == v) break;
    }
    if (i == G.vexnum) return false;

    // 删除以 v 为起点的所有边
    while (G.vertices[i].firstarc) {
        ArcNode *p = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p->next;
        delete p;
        G.arcnum--;
    }

    // 删除以 v 为终点的所有边
    for (int j = 0; j < G.vexnum; j++) {
        if (j == i) continue;
        ArcNode *p = G.vertices[j].firstarc, *prev = nullptr;
        while (p) {
            if (p->adjvex == i) {
                if (prev) prev->next = p->next;
                else G.vertices[j].firstarc = p->next;
                delete p;
                G.arcnum--;
                break;
            }
            prev = p;
            p = p->next;
        }
    }

    // 移动最后一个顶点到被删除的位置
    if (i != G.vexnum - 1) {
        G.vertices[i] = G.vertices[G.vexnum - 1];
        // 更新指向最后一个顶点的边
        for (int j = 0; j < G.vexnum - 1; j++) {
            ArcNode *p = G.vertices[j].firstarc;
            while (p) {
                if (p->adjvex == G.vexnum - 1) p->adjvex = i;
                p = p->next;
            }
        }
    }
    G.vexnum--;
    return true;
}

// 插入边
bool InsertEdge(ALGraph &G, int v, int w, EdgeType weight) {
    if (v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum) return false;
    if (Adjacent(G, v, w)) return false;

    ArcNode *p = new ArcNode{w, G.vertices[v].firstarc, weight};
    G.vertices[v].firstarc = p;
    G.arcnum++;
    return true;
}

// 删除边
bool RemoveEdge(ALGraph &G, int v, int w) {
    if (v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum) return false;

    ArcNode *p = G.vertices[v].firstarc, *prev = nullptr;
    while (p && p->adjvex != w) {
        prev = p;
        p = p->next;
    }
    if (!p) return false;

    if (prev) prev->next = p->next;
    else G.vertices[v].firstarc = p->next;
    delete p;
    G.arcnum--;
    return true;
}

// 获取第一个邻接顶点
int FirstNeighbor(const ALGraph &G, int v) {
    if (v < 0 || v >= G.vexnum) return -1;
    ArcNode *p = G.vertices[v].firstarc;
    return p ? p->adjvex : -1;
}

// 获取下一个邻接顶点
int NextNeighbor(const ALGraph &G, int v, int w) {
    if (v < 0 || v >= G.vexnum) return -1;
    ArcNode *p = G.vertices[v].firstarc;
    while (p && p->adjvex != w) p = p->next;
    return (p && p->next) ? p->next->adjvex : -1;
}

// 获取边的权值
EdgeType GetEdgeValue(const ALGraph &G, int v, int w) {
    if (v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum) return INT_MAX;
    ArcNode *p = G.vertices[v].firstarc;
    while (p && p->adjvex != w) p = p->next;
    return p ? p->weight : INT_MAX;
}

// 设置边的权值
bool SetEdgeValue(ALGraph &G, int v, int w, EdgeType value) {
    if (v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum) return false;
    ArcNode *p = G.vertices[v].firstarc;
    while (p && p->adjvex != w) p = p->next;
    if (p) {
        p->weight = value;
        return true;
    }
    return false;
}

// BFS 遍历
void BFS(const ALGraph &G, int start) {
    vector<bool> visited(G.vexnum, false);
    queue<int> Q;
    
    cout << G.vertices[start].data << " ";
    visited[start] = true;
    Q.push(start);
    
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w]) {
                cout << G.vertices[w].data << " ";
                visited[w] = true;
                Q.push(w);
            }
        }
    }
    cout << endl;
}

// 广度优先搜索求单源最短路径
void BFSShortestPath(const ALGraph &G, int start) {
    vector<bool> visited(G.vexnum, false);
    vector<int> distance(G.vexnum, INT_MAX);
    vector<int> parent(G.vexnum, -1);
    queue<int> Q;

    visited[start] = true;
    distance[start] = 0;
    Q.push(start);

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();

        for (ArcNode *p = G.vertices[v].firstarc; p; p = p->next) {
            int w = p->adjvex;
            if (!visited[w]) {
                visited[w] = true;
                distance[w] = distance[v] + 1;
                parent[w] = v;
                Q.push(w);
            }
        }
    }

    // 打印最短路径结果
    cout << "从顶点 " << G.vertices[start].data << " 到其他顶点的最短路径：" << endl;
    for (int i = 0; i < G.vexnum; i++) {
        if (i != start) {
            cout << G.vertices[start].data << " 到 " << G.vertices[i].data << ": ";
            if (distance[i] == INT_MAX) {
                cout << "不可达" << endl;
            } else {
                cout << "距离 = " << distance[i] << ", 路径 = ";
                vector<int> path;
                for (int j = i; j != -1; j = parent[j]) {
                    path.push_back(j);
                }
                for (int j = path.size() - 1; j >= 0; j--) {
                    cout << G.vertices[path[j]].data;
                    if (j > 0) cout << " -> ";
                }
                cout << endl;
            }
        }
    }
}

// DFS 遍历
void DFS(const ALGraph &G, int v, vector<bool> &visited) {
    cout << G.vertices[v].data << " ";
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]) {
            DFS(G, w, visited);
        }
    }
}

// DFS 遍历（外部接口）
void DFSTraversal(const ALGraph &G) {
    vector<bool> visited(G.vexnum, false);
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            DFS(G, i, visited);
        }
    }
    cout << endl;
}

// BFS 遍历（遍历所有连通分量）
void BFSTraversal(const ALGraph &G) {
    vector<bool> visited(G.vexnum, false);
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            BFS(G, i);
        }
    }
}


//王道 05 邻接矩阵转邻接表
void convert(ALGraph &G,int arcs[MaxVertexNum][MaxVertexNum]){
    for(int i=0;i<G.vexnum;i++){
        ArcNode *p = G.vertices[i].firstarc;
        while(p!=NULL){
            arcs[i][p->adjvex]=1;
            p=p->next;
        }
    }
}

int main() {
    ALGraph G;
    CreateDefaultGraph(G);
    cout << "DFS 遍历结果：";
    DFSTraversal(G);
    cout << "BFS 遍历结果：";
    BFSTraversal(G);
    cout << "\nBFS 单源最短路径：" << endl;
    BFSShortestPath(G, 0);  // 从顶点 A（索引 0）开始
    return 0;
}