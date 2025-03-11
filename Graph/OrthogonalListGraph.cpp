#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// �߽��
struct ArcNode {
    int tailvex, headvex;  // ��β�ͻ�ͷ�����λ��
    ArcNode *hlink, *tlink;  // ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
    int weight;  // Ȩ��

    ArcNode(int tail, int head, int w) : tailvex(tail), headvex(head), hlink(nullptr), tlink(nullptr), weight(w) {}
};

// ������
struct VNode {
    char data;
    ArcNode *firstin, *firstout;  // ָ���һ���뻡�ͳ���

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

        // ���ö���
        vertices[0].data = 'A';
        vertices[1].data = 'B';
        vertices[2].data = 'C';
        vertices[3].data = 'D';
        vertices[4].data = 'E';

        // ��ӱ�
        InsertArc(0, 1, 1); // A->B
        InsertArc(0, 2, 1); // A->C
        InsertArc(1, 2, 1); // B->C
        InsertArc(1, 3, 1); // B->D
        InsertArc(2, 3, 1); // C->D
        InsertArc(3, 4, 1); // D->E
        InsertArc(4, 0, 1); // E->A

        cout << "Ĭ��ͼ�Ѵ�����" << endl;
    }

    void InsertArc(int tail, int head, int weight) {
        ArcNode* p = new ArcNode(tail, head, weight);

        // ���뵽��������
        p->tlink = vertices[tail].firstout;
        vertices[tail].firstout = p;

        // ���뵽�뻡����
        p->hlink = vertices[head].firstin;
        vertices[head].firstin = p;
    }

    void PrintGraph() const {
        for (int i = 0; i < vexnum; i++) {
            cout << vertices[i].data << " ������";
            ArcNode* p = vertices[i].firstout;
            while (p) {
                cout << vertices[p->headvex].data << "(" << p->weight << ") ";
                p = p->tlink;
            }
            cout << endl;

            cout << vertices[i].data << " �뻡��";
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
    
    cout << "ͼ�Ľṹ��" << endl;
    G.PrintGraph();

    cout << "DFS ���������";
    G.DFSTraversal();
    
    cout << "BFS ���������";
    G.BFSTraversal();

    return 0;
}