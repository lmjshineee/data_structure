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
    EdgeType weight;  // ��ӱ�Ȩֵ
} ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

// ����Ĭ��ͼ
void CreateDefaultGraph(ALGraph &G) {
    G.vexnum = 5;
    G.arcnum = 7;

    // ��ʼ������
    char vertexData[] = {'A', 'B', 'C', 'D', 'E'};
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].data = vertexData[i];
        G.vertices[i].firstarc = nullptr;
    }

    // ��ӱ�
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

        // ���������ͼ����Ҫ��ӷ����
        p = new ArcNode{edge.v1, G.vertices[edge.v2].firstarc, edge.weight};
        G.vertices[edge.v2].firstarc = p;
    }

    cout << "Ĭ��ͼ�Ѵ�����" << endl;
}

// ... (�����������ֲ���)

// ��ӡͼ�ṹ
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

// ����ͼ
void CreateALGraph(ALGraph &G) {
    cout << "�����붥�����ͱ�����";
    cin >> G.vexnum >> G.arcnum;
    
    cout << "�����붥����Ϣ��";
    for (int i = 0; i < G.vexnum; i++) {
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = nullptr;
    }
    
    cout << "������ߵ���Ϣ��" << endl;
    for (int k = 0; k < G.arcnum; k++) {
        int v1, v2, weight;
        cout << "������������Ķ����Ȩ�أ�";
        cin >> v1 >> v2 >> weight;
        
        ArcNode *p = new ArcNode{v2, G.vertices[v1].firstarc, weight};
        G.vertices[v1].firstarc = p;
        
        // ���������ͼ����Ҫ��ӷ����
        p = new ArcNode{v1, G.vertices[v2].firstarc, weight};
        G.vertices[v2].firstarc = p;
    }
}

// �ж����������Ƿ��ڽ�
bool Adjacent(const ALGraph &G, int v, int w) {
    ArcNode *p = G.vertices[v].firstarc;
    while (p) {
        if (p->adjvex == w) return true;
        p = p->next;
    }
    return false;
}

// ��ȡ����������ڽӵ�
vector<int> Neighbors(const ALGraph &G, int v) {
    vector<int> neighbors;
    ArcNode *p = G.vertices[v].firstarc;
    while (p) {
        neighbors.push_back(p->adjvex);
        p = p->next;
    }
    return neighbors;
}

// ���붥��
bool InsertVertex(ALGraph &G, VertexType v) {
    if (G.vexnum == MaxVertexNum) return false;
    G.vertices[G.vexnum++].data = v;
    return true;
}

// ɾ������
bool DeleteVertex(ALGraph &G, VertexType v) {
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data == v) break;
    }
    if (i == G.vexnum) return false;

    // ɾ���� v Ϊ�������б�
    while (G.vertices[i].firstarc) {
        ArcNode *p = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p->next;
        delete p;
        G.arcnum--;
    }

    // ɾ���� v Ϊ�յ�����б�
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

    // �ƶ����һ�����㵽��ɾ����λ��
    if (i != G.vexnum - 1) {
        G.vertices[i] = G.vertices[G.vexnum - 1];
        // ����ָ�����һ������ı�
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

// �����
bool InsertEdge(ALGraph &G, int v, int w, EdgeType weight) {
    if (v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum) return false;
    if (Adjacent(G, v, w)) return false;

    ArcNode *p = new ArcNode{w, G.vertices[v].firstarc, weight};
    G.vertices[v].firstarc = p;
    G.arcnum++;
    return true;
}

// ɾ����
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

// ��ȡ��һ���ڽӶ���
int FirstNeighbor(const ALGraph &G, int v) {
    if (v < 0 || v >= G.vexnum) return -1;
    ArcNode *p = G.vertices[v].firstarc;
    return p ? p->adjvex : -1;
}

// ��ȡ��һ���ڽӶ���
int NextNeighbor(const ALGraph &G, int v, int w) {
    if (v < 0 || v >= G.vexnum) return -1;
    ArcNode *p = G.vertices[v].firstarc;
    while (p && p->adjvex != w) p = p->next;
    return (p && p->next) ? p->next->adjvex : -1;
}

// ��ȡ�ߵ�Ȩֵ
EdgeType GetEdgeValue(const ALGraph &G, int v, int w) {
    if (v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum) return INT_MAX;
    ArcNode *p = G.vertices[v].firstarc;
    while (p && p->adjvex != w) p = p->next;
    return p ? p->weight : INT_MAX;
}

// ���ñߵ�Ȩֵ
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

// BFS ����
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

// �������������Դ���·��
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

    // ��ӡ���·�����
    cout << "�Ӷ��� " << G.vertices[start].data << " ��������������·����" << endl;
    for (int i = 0; i < G.vexnum; i++) {
        if (i != start) {
            cout << G.vertices[start].data << " �� " << G.vertices[i].data << ": ";
            if (distance[i] == INT_MAX) {
                cout << "���ɴ�" << endl;
            } else {
                cout << "���� = " << distance[i] << ", ·�� = ";
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

// DFS ����
void DFS(const ALGraph &G, int v, vector<bool> &visited) {
    cout << G.vertices[v].data << " ";
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]) {
            DFS(G, w, visited);
        }
    }
}

// DFS �������ⲿ�ӿڣ�
void DFSTraversal(const ALGraph &G) {
    vector<bool> visited(G.vexnum, false);
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            DFS(G, i, visited);
        }
    }
    cout << endl;
}

// BFS ����������������ͨ������
void BFSTraversal(const ALGraph &G) {
    vector<bool> visited(G.vexnum, false);
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            BFS(G, i);
        }
    }
}


//���� 05 �ڽӾ���ת�ڽӱ�
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
    cout << "DFS ���������";
    DFSTraversal(G);
    cout << "BFS ���������";
    BFSTraversal(G);
    cout << "\nBFS ��Դ���·����" << endl;
    BFSShortestPath(G, 0);  // �Ӷ��� A������ 0����ʼ
    return 0;
}