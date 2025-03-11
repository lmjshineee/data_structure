#include<iostream>
#include<cstring>
using namespace std;
 
const int N = 100, M = 100;
 
//������� �� ����
int n, m;
//dis ���飬��¼�ϴ�״̬�� dis ����
int dis[N];
 
//�洢�ߵĽṹ������
struct Edge {
    int a, b, w;
}edges[M];
 
void bellmanford(int x) {
    //��ʼ�� dist ����
    memset(dis, 0x3f, sizeof(dis));
    dis[x] = 0;// x ��Դ��
 
    //���� n - 1 ���ɳ�
    //�����б߽���һ���ɳڲ������������Դ�㵽���е㣬�����ı������Ϊ 1 �����·
	//�����б߽��������ɳڲ������������Դ�㵽���е㣬�����ı������Ϊ 2 �����·
	//....
	//�����б߽��� n- 1 ���ɳڲ������������Դ�㵽���е㣬�����ı������Ϊ n - 1 �����·
    for(int i = 0; i < n - 1; i++) {
        
        //�������б�
        for(int j = 0; j < m; j++) {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            if(dis[a] != 0x3f3f3f3f && dis[b] > dis[a] + w) //�ɳڲ���
                dis[b] = dis[a] + w;
        }
    }
    
}
int main() {
    //�������������
    //cin >> n >> m;
    n=3,m=3;
    //�����
    /*for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }*/
    edges[0]={0,1,2};
    edges[1]={1,2,1};
    edges[2]={2,0,7};
    int x;
    cin>>x;
    //���� bellman - ford �㷨
    bellmanford(x);
    
    //��ӡ dis ����
    for(int i = 1; i <= n; i++)
        cout << dis[i] << " ";
    cout << endl;
 
    system("pause");
    return 0;
}
/*
�������
5 5
2 3 2
1 2 -3
1 5 5
4 5 2
3 4 3
�������
0 -3 -1 2 4
*/