#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;  // 表示无穷大

void floydWarshall(vector<vector<int>>& dist) {
    int n = dist.size();

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    int n = 4;
    vector<vector<int>> dist(n, vector<int>(n, INF));

    // 初始化距离矩阵
    dist[0][0] = 0;
    dist[0][1] = 3;
    dist[0][2] = INF;
    dist[0][3] = 5;
    dist[1][0] = 2;
    dist[1][1] = 0;
    dist[1][2] = INF;
    dist[1][3] = 4;
    dist[2][0] = INF;
    dist[2][1] = 1;
    dist[2][2] = 0;
    dist[2][3] = INF;
    dist[3][0] = INF;
    dist[3][1] = INF;
    dist[3][2] = 2;
    dist[3][3] = 0;

    floydWarshall(dist);

    // 输出最短路径距离矩阵
    cout << "Shortest distances between every pair of vertices:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}