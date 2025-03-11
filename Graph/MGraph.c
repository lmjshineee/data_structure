#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef enum{DG,UDG} GraphType;

typedef struct {
    char vex[MAX];  //����һά����洢����
    int arcs[MAX][MAX];  //�����ά����洢��
    int vexnum,arcnum;  //�洢����ͱߵ�����
    GraphType type;  //�洢ͼ������
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
    //��ȡͼ������
    int type;
    printf("������ͼ�����ͣ�����ͼ���� 1������ͼ���� 0:");
    scanf("%d",&type);
    if(type==1){
        G->type=DG;
    }else if(type==0){
        G->type=UDG;
    }else{
        printf("��������Ͳ���ȷ��\n");
        return;
    }
    //��ȡͼ�ö������ͱ���
    printf("ͼ�м������㣺");
    scanf("%d",&G->vexnum);
    printf("ͼ�м����ߣ�");
    scanf("%d",&G->arcnum);
    getchar();
    //���ÿ�������ֵ
    
    for(int k=1;k<=G->vexnum;k++){
        printf("�������%d������ֵ��",k);
        scanf("%s",&G->vex[k]);
        getchar();
    }
    //ֵȫ��������
    
    //�����ʼ��
    int i,j;
    for (i = 1; i <= G->vexnum; i++)
    {
        for (j = 1; j <= G->vexnum; j++)
        {
            G->arcs[i][j] = 0;
        }
    }
    //�ж��ٸ����ѭ�����ٴ�
    char V1,V2;
    int V1p,V2p;
    for(int l=1;l<=G->arcnum;l++){
        printf("�����%d���ߵ���Ϣ��",l);
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
        printf("ͼ���� : ����ͼ\n");
    }
    else
    {
        printf("ͼ���ͣ�����ͼ\n");
    }
    printf("ͼ�еĶ����У�%d ��\n",MG.vexnum);
    printf("ͼ�еı�/���У�%d ��\n",MG.arcnum);
    
    printf("����ļ��ϣ�");
    for (i = 1; i <= MG.vexnum; i++){
        printf("%c ", MG.vex[i]);
    }
    printf("\n");
    printf("�ڽӾ���:\n");
    
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