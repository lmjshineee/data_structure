#include <iostream>

// 双链表的节点结构
struct Node {
    int data;       // 数据域
    Node* prev;     // 指向前一个节点
    Node* next;     // 指向下一个节点

    // 构造函数
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// 双链表类
class DoublyLinkedList {
private:
    Node* head;     // 指向链表头部
    Node* tail;     // 指向链表尾部

public:
    // 构造函数，初始化空链表
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // 在链表头部插入节点
    void insertAtHead(int value) {
        Node* newNode = new Node(value);  // 创建新节点
        if (head == nullptr) {
            head = tail = newNode;  // 如果链表为空，新节点既是头节点又是尾节点
        } else {
            newNode->next = head;   // 新节点的 next 指向当前头节点
            head->prev = newNode;   // 当前头节点的 prev 指向新节点
            head = newNode;         // 更新头节点为新节点
        }
    }

    // 在链表尾部插入节点
    void insertAtTail(int value) {
        Node* newNode = new Node(value);  // 创建新节点
        if (tail == nullptr) {
            head = tail = newNode;  // 如果链表为空，新节点既是头节点又是尾节点
        } else {
            newNode->prev = tail;   // 新节点的 prev 指向当前尾节点
            tail->next = newNode;   // 当前尾节点的 next 指向新节点
            tail = newNode;         // 更新尾节点为新节点
        }
    }

    // 删除链表中的指定节点
    void deleteNode(int value) {
        if (head == nullptr) return;  // 如果链表为空，直接返回

        Node* temp = head;
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;  // 遍历找到值为 value 的节点
        }

        if (temp == nullptr) {
            std::cout << "Value not found!" << std::endl;
            return;  // 没有找到值为 value 的节点
        }

        // 如果要删除的是头节点
        if (temp == head) {
            head = temp->next;  // 更新头节点
            if (head != nullptr) {
                head->prev = nullptr;  // 如果有新的头节点，更新它的 prev
            } else {
                tail = nullptr;  // 如果链表为空，更新尾节点为 nullptr
            }
        }
        // 如果要删除的是尾节点
        else if (temp == tail) {
            tail = temp->prev;  // 更新尾节点
            if (tail != nullptr) {
                tail->next = nullptr;  // 更新新的尾节点的 next
            } else {
                head = nullptr;  // 如果链表为空，更新头节点为 nullptr
            }
        }
        // 中间节点
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;  // 释放要删除的节点
    }

    // 正向遍历链表
    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // 反向遍历链表
    void printReverse() {
        Node* temp = tail;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->prev;
        }
        std::cout << std::endl;
    }

    // 析构函数，释放链表中的所有节点
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    DoublyLinkedList list;

    // 插入节点
    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtTail(30);

    // 打印链表
    std::cout << "Forward: ";
    list.printList();

    std::cout << "Reverse: ";
    list.printReverse();

    // 删除节点
    list.deleteNode(20);
    std::cout << "After deleting 20, Forward: ";
    list.printList();

    std::cout << "After deleting 20, Reverse: ";
    list.printReverse();

    return 0;
}
