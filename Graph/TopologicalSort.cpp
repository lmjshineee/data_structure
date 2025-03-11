#include <iostream>
#include <stack>
using namespace std;

#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;
typedef int InfoType;

//邻接表表示法
#define MaxVertexNum 100
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *next;
    InfoType info;
}ArcNode;
typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
}VNode,AdjList[MaxVertexNum];
typedef struct{
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;

//
bool TopologicalSort(ALGraph G){
    stack<int> S;
    int indegree[G.vexnum];
    for(int i=0;i<G.vexnum;i++){
        indegree[i] = 0;
    }
    for(int i=0;i<G.vexnum;i++){
        ArcNode *p = G.vertices[i].firstarc;
        while(p){
            indegree[p->adjvex]++;
            p = p->next;
        }
    }
    for(int i=0;i<G.vexnum;i++){
        if(indegree[i] == 0){
            S.push(i);
        }
    }
    int count = 0;
    while(!S.empty()){
        int i = S.top();
        S.pop();
        cout<<i<<' ';
        count++;
        ArcNode *p = G.vertices[i].firstarc;
        while(p){
            int k = p->adjvex;
            indegree[k]--;
            if(indegree[k] == 0){
                S.push(k);
            }
            p = p->next;
        }
    }
    if(count<G.vexnum){
        return false;
    }
    return true;
}

int main(){
    ALGraph G;
    G.vexnum = 5;
    G.arcnum = 5;
    for(int i=0;i<G.vexnum;i++){
        G.vertices[i].data = 'A'+i;
        G.vertices[i].firstarc = NULL;
    }
    ArcNode *p1 = new ArcNode;
    p1->adjvex = 1;
    p1->info = 1;
    p1->next = G.vertices[0].firstarc;
    G.vertices[0].firstarc = p1;
    ArcNode *p2 = new ArcNode;
    p2->adjvex = 2;
    p2->info = 1;
    p2->next = G.vertices[0].firstarc;
    G.vertices[0].firstarc = p2;
    ArcNode *p3 = new ArcNode;
    p3->adjvex = 3;
    p3->info = 1;
    p3->next = G.vertices[1].firstarc;
    G.vertices[1].firstarc = p3;
    ArcNode *p4 = new ArcNode;
    p4->adjvex = 4;
    p4->info = 1;
    p4->next = G.vertices[1].firstarc;
    G.vertices[1].firstarc = p4;
    ArcNode *p5 = new ArcNode;
    p5->adjvex = 2;
    p5->info = 1;
    p5->next = G.vertices[2].firstarc;
    G.vertices[2].firstarc = p5;
    if(TopologicalSort(G)){
        cout<<"有向无环图的拓扑排序为："<<endl;
    }else{
        cout<<"有向无环图有回路"<<endl;
    }
    return 0;
}