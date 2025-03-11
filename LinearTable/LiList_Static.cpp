#include <iostream>
#define MAX_SIZE 100  // 链表的最大节点数

// 静态链表 next==-1 结束 在不支持指针时有用
// 节点结构体
struct StaticNode {
    int data;    // 数据域
    int next;    // 下一个节点的索引
};

// 静态链表类
class StaticLinkedList {
private:
    StaticNode nodes[MAX_SIZE];  // 节点数组
    int head;                    // 链表的头节点索引
    int free;                    // 空闲节点的起始索引

public:
    StaticLinkedList() {
        head = -1;  // 初始化头节点为空
        free = 0;   // 初始化空闲节点从 0 开始

        // 初始化节点数组，空闲节点用 next 字段串联起来
        for (int i = 0; i < MAX_SIZE - 1; ++i) {
            nodes[i].next = i + 1;  // 把空闲节点串联
        }
        nodes[MAX_SIZE - 1].next = -1;  // 最后一个空闲节点的 next 置为 -1
    }

    // 在链表头部插入一个新节点
    void insertAtHead(int value) {
        if (free == -1) {  // 如果没有空闲节点
            std::cout << "No free space to insert!" << std::endl;
            return;
        }

        // 从空闲链表中取出一个节点
        int newNodeIndex = free;
        free = nodes[free].next;  // 更新空闲链表头节点

        // 设置新节点的数据
        nodes[newNodeIndex].data = value;
        nodes[newNodeIndex].next = head;  // 新节点的 next 指向原来的头节点
        head = newNodeIndex;              // 更新头节点为新节点
    }

    // 删除链表中第一个值为 value 的节点
    void deleteNode(int value) {
        if (head == -1) {
            std::cout << "List is empty!" << std::endl;
            return;
        }

        int current = head;
        int prev = -1;

        // 找到要删除的节点
        while (current != -1 && nodes[current].data != value) {
            prev = current;
            current = nodes[current].next;
        }

        if (current == -1) {
            std::cout << "Value not found in the list!" << std::endl;
            return;
        }

        // 如果删除的是头节点
        if (prev == -1) {
            head = nodes[current].next;
        } else {
            nodes[prev].next = nodes[current].next;  // 跳过要删除的节点
        }

        // 将删除的节点添加回空闲链表
        nodes[current].next = free;
        free = current;
    }

    // 打印链表
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

    // 插入节点
    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtHead(30);

    // 打印链表
    std::cout << "Linked List: ";
    list.printList();

    // 删除节点
    list.deleteNode(20);
    std::cout << "After deleting 20: ";
    list.printList();

    return 0;
}
