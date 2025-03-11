#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;

/*有向图*/
struct MGraph {
    vector<VertexType> Vex;
    vector<vector<EdgeType>> Edge;
    int vexnum, arcnum;

    MGraph(int n) : vexnum(n), arcnum(0), Vex(n), Edge(n, vector<EdgeType>(n, 0)) {}
};

// 打印顶点（出入度）
void printVerticesDegrees(const MGraph& G) {
    for (int i = 0; i < G.vexnum; i++) {
        int indegree = 0, outdegree = 0;
        for (int j = 0; j < G.vexnum; j++) {
            indegree += G.Edge[j][i];
            outdegree += G.Edge[i][j];
        }
        cout << "顶点 " << G.Vex[i] << ": 入度 = " << indegree << ", 出度 = " << outdegree << endl;
    }
}

int isExistEL(MGraph G){
    int count=0;
    int i,j,degree=0;
    for(i=0;i<G.vexnum;i++){
        for(j=0;j<G.vexnum;j++){
            if(G.Edge[i][j]==1)
                degree++;
        }
        if(degree%2==1)
            count++;
        degree=0;
    }
    if(count==2||count==0)
        return 1;
    else
        return 0;
}

// 打印出度大于入度的顶点（K 顶点）
int printVertices(const MGraph& G) {
    int count = 0;
    for (int i = 0; i < G.vexnum; i++) {
        int indegree = 0, outdegree = 0;
        for (int j = 0; j < G.vexnum; j++) {
            indegree += G.Edge[j][i];
            outdegree += G.Edge[i][j];
        }
        if (indegree < outdegree) {
            cout << G.Vex[i] << " ";
            count++;
        }
    }
    return count;
}

void visit(const MGraph& G, int v) {
    cout << G.Vex[v] << " ";
}

void BFS(const MGraph& G, int start) {
    vector<bool> visited(G.vexnum, false);
    queue<int> Q;
    
    visit(G, start);
    visited[start] = true;
    Q.push(start);
    
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int w = 0; w < G.vexnum; w++) {
            if (G.Edge[v][w] == 1 && !visited[w]) {
                visit(G, w);
                visited[w] = true;
                Q.push(w);
            }
        }
    }
}

void DFSUtil(const MGraph& G, int v, vector<bool>& visited) {
    visit(G, v);
    visited[v] = true;
    for (int w = 0; w < G.vexnum; w++) {
        if (G.Edge[v][w] == 1 && !visited[w]) {
            DFSUtil(G, w, visited);
        }
    }
}

void DFS(const MGraph& G, int start) {
    vector<bool> visited(G.vexnum, false);
    DFSUtil(G, start, visited);
}

// 矩阵乘法函数
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// 计算 A^N 的函数
vector<vector<int>> calculatePowerN(const MGraph& G, int N) {
    int n = G.vexnum;
    vector<vector<int>> result(n, vector<int>(n, 0));
    vector<vector<int>> temp = G.Edge;

    // 单位矩阵
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }

    // 快速幂算法
    while (N > 0) {
        if (N & 1) {
            result = matrixMultiply(result, temp);
        }
        temp = matrixMultiply(temp, temp);
        N >>= 1;
    }

    return result;
}

// 打印矩阵的函数
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    MGraph G(5);
    G.Vex = {'A', 'B', 'C', 'D', 'E'};
    
    G.Edge[0][1] = G.Edge[0][2] = 1;
    G.Edge[1][2] = G.Edge[1][3] = 1;
    G.Edge[2][3] = 1;
    G.Edge[3][4] = 1;
    G.Edge[4][0] = 1;
    G.arcnum = 7;

    printVerticesDegrees(G);
    cout << "Vertices with outdegree > indegree: ";
    int k = printVertices(G);
    cout << "\nCount: " << k << endl;

    cout << "DFS: ";
    DFS(G, 0);
    cout << endl;

    cout << "BFS: ";
    BFS(G, 0);
    cout << endl;
    
    int N = 3;
    vector<vector<int>> result = calculatePowerN(G, N);
    cout << "A^" << N << ":\n";
    printMatrix(result);
    return 0;
}