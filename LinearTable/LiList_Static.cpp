#include <iostream>
#define MAX_SIZE 100  // ��������ڵ���

// ��̬���� next==-1 ���� �ڲ�֧��ָ��ʱ����
// �ڵ�ṹ��
struct StaticNode {
    int data;    // ������
    int next;    // ��һ���ڵ������
};

// ��̬������
class StaticLinkedList {
private:
    StaticNode nodes[MAX_SIZE];  // �ڵ�����
    int head;                    // �����ͷ�ڵ�����
    int free;                    // ���нڵ����ʼ����

public:
    StaticLinkedList() {
        head = -1;  // ��ʼ��ͷ�ڵ�Ϊ��
        free = 0;   // ��ʼ�����нڵ�� 0 ��ʼ

        // ��ʼ���ڵ����飬���нڵ��� next �ֶδ�������
        for (int i = 0; i < MAX_SIZE - 1; ++i) {
            nodes[i].next = i + 1;  // �ѿ��нڵ㴮��
        }
        nodes[MAX_SIZE - 1].next = -1;  // ���һ�����нڵ�� next ��Ϊ -1
    }

    // ������ͷ������һ���½ڵ�
    void insertAtHead(int value) {
        if (free == -1) {  // ���û�п��нڵ�
            std::cout << "No free space to insert!" << std::endl;
            return;
        }

        // �ӿ���������ȡ��һ���ڵ�
        int newNodeIndex = free;
        free = nodes[free].next;  // ���¿�������ͷ�ڵ�

        // �����½ڵ������
        nodes[newNodeIndex].data = value;
        nodes[newNodeIndex].next = head;  // �½ڵ�� next ָ��ԭ����ͷ�ڵ�
        head = newNodeIndex;              // ����ͷ�ڵ�Ϊ�½ڵ�
    }

    // ɾ�������е�һ��ֵΪ value �Ľڵ�
    void deleteNode(int value) {
        if (head == -1) {
            std::cout << "List is empty!" << std::endl;
            return;
        }

        int current = head;
        int prev = -1;

        // �ҵ�Ҫɾ���Ľڵ�
        while (current != -1 && nodes[current].data != value) {
            prev = current;
            current = nodes[current].next;
        }

        if (current == -1) {
            std::cout << "Value not found in the list!" << std::endl;
            return;
        }

        // ���ɾ������ͷ�ڵ�
        if (prev == -1) {
            head = nodes[current].next;
        } else {
            nodes[prev].next = nodes[current].next;  // ����Ҫɾ���Ľڵ�
        }

        // ��ɾ���Ľڵ���ӻؿ�������
        nodes[current].next = free;
        free = current;
    }

    // ��ӡ����
    void printList() {
        int temp = head;
        while (temp != -1) {
            std::cout << nodes[temp].data << " ";
            temp = nodes[temp].next;
        }
        std::cout << std::endl;
    }
};

int main() {
    StaticLinkedList list;

    // ����ڵ�
    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtHead(30);

    // ��ӡ����
    std::cout << "Linked List: ";
    list.printList();

    // ɾ���ڵ�
    list.deleteNode(20);
    std::cout << "After deleting 20: ";
    list.printList();

    return 0;
}
