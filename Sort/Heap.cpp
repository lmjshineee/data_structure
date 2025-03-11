#include <queue>
#include <vector>
#include <iostream>

using namespace std;
// C++ �еĶѣ�Heap����һ���������ȫ����������Ϊ�󶥶Ѻ�С����

/* �����б����� */
vector<int> input{1, 3, 2, 5, 4};
priority_queue<int, vector<int>, greater<int>> minHeap(input.begin(), input.end());


int main(){
    /* ��ʼ���� */
// ��ʼ��С����
priority_queue<int, vector<int>, greater<int>> minHeap;
// ��ʼ���󶥶�
priority_queue<int, vector<int>, less<int>> maxHeap;

/* Ԫ����� */
maxHeap.push(1);
maxHeap.push(3);
maxHeap.push(2);
maxHeap.push(5);
maxHeap.push(4);

/* ��ȡ�Ѷ�Ԫ�� */
int peek = maxHeap.top(); // 5
cout<<peek<<endl;
/* �Ѷ�Ԫ�س��� */
// ����Ԫ�ػ��γ�һ���Ӵ�С������
maxHeap.pop(); // 5
maxHeap.pop(); // 4
maxHeap.pop(); // 3
maxHeap.pop(); // 2
maxHeap.pop(); // 1
    return 0;
}
