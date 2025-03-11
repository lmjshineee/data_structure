#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef enum{DG,UDG} GraphType;

typedef struct {
    char vex[MAX];  //定义一维数组存储顶点
    int arcs[MAX][MAX];  //定义二维数组存储边
    int vexnum,arcnum;  //存储顶点和边的数量
    GraphType type;  //存储图的类型
}Graph;

int position(char c , Graph *G){
    int i;
    for(i=1;i<=G->vexnum;i++){
        if(G->vex[i]==c){
            return i;
        }
    }
    return 0;
}

void Create(Graph * G){
    //获取图的类型
    int type;
    printf("请输入图的类型，有向图输入 1，无向图输入 0:");
    scanf("%d",&type);
    if(type==1){
        G->type=DG;
    }else if(type==0){
        G->type=UDG;
    }else{
        printf("输入的类型不正确！\n");
        return;
    }
    //获取图得顶点数和边数
    printf("图有几个顶点：");
    scanf("%d",&G->vexnum);
    printf("图有几条边：");
    scanf("%d",&G->arcnum);
    getchar();
    //获得每个顶点得值
    
    for(int k=1;k<=G->vexnum;k++){
        printf("请输入第%d个结点的值：",k);
        scanf("%s",&G->vex[k]);
        getchar();
    }
    //值全部获得完毕
    
    //矩阵初始化
    int i,j;
    for (i = 1; i <= G->vexnum; i++)
    {
        for (j = 1; j <= G->vexnum; j++)
        {
            G->arcs[i][j] = 0;
        }
    }
    //有多少个结点循环多少次
    char V1,V2;
    int V1p,V2p;
    for(int l=1;l<=G->arcnum;l++){
        printf("请输第%d个边的信息：",l);
        scanf("%c %c",&V1,&V2);
        V1p=position(V1,G);
        V2p=position(V2,G);
        
        if(G->type==UDG){
            G->arcs[V1p][V2p]=G->arcs[V2p][V1p]=1;
        }else{
            G->arcs[V1p][V2p]=1;
        }
        getchar();
    }
}


void print_MG(Graph MG){
    printf("-------------------------------\n");
    int i, j;
    if(MG.type == DG)
    {
        printf("图类型 : 有向图\n");
    }
    else
    {
        printf("图类型：无向图\n");
    }
    printf("图中的顶点有：%d 个\n",MG.vexnum);
    printf("图中的边/弧有：%d 个\n",MG.arcnum);
    
    printf("顶点的集合：");
    for (i = 1; i <= MG.vexnum; i++){
        printf("%c ", MG.vex[i]);
    }
    printf("\n");
    printf("邻接矩阵:\n");
    
    for (i = 1; i <= MG.vexnum; i++)
    {
        printf("%c ", MG.vex[i]);
        j = 1;
        for (; j < MG.vexnum; j++)
        {
            printf("%d ", MG.arcs[i][j]);
        }
        printf("%d ", MG.arcs[i][j]);
        printf("\n");
    }
}
int main()
{
    Graph MG;
    Create(&MG);
    print_MG(MG);
    return 0;
}