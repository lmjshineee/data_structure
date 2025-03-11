#include <iostream>
/*
无头节点的单链表 即所有节点都是数据节点
*/

struct Node {
    int data;      // 数据域
    Node* next;    // 指向下一个节点的指针

    // 构造函数，用于初始化节点
    Node(int value) : data(value), next(nullptr) {}
};


class SinglyLinkedList {
private:
    Node* head;  // 指向链表头部的指针

public:
    // 构造函数，初始化链表为空
    SinglyLinkedList() : head(nullptr) {}

    // 链表长度
    int size() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // 插入节点到链表的头部
    void insertAtHead(int value) {
        Node* newNode = new Node(value);  // 创建新节点
        newNode->next = head;             // 将新节点的 next 指向当前的头节点
        head = newNode;                   // 更新头节点为新节点
    }

    // 插入节点到链表的尾部
    void insertAtTail(int value) {
        Node* newNode = new Node(value);  // 创建新节点
        if (head == nullptr) {
            head = newNode;               // 如果链表为空，直接插入到头部
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {  // 遍历找到链表的最后一个节点
                temp = temp->next;
            }
            temp->next = newNode;            // 将最后一个节点的 next 指向新节点
        }
    }

    // 删除指定位置的节点
    void deleteNode(int position) {
        if (head == nullptr||position>size()) return;  // 如果链表为空，直接返回

        if (position==0) {    // 如果要删除的是头节点
            Node* temp = head;
            head = head->next;        // 更新头节点
            delete temp;              // 删除原头节点
            return;
        }

        Node* temp = head;
        for(int i=0; i<position-1; i++) {
            temp = temp->next;
        }

        if (temp->next != nullptr) {  // 如果找到了要删除的节点
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;  // 更新链表指向，跳过要删除的节点
            delete nodeToDelete;            // 删除节点
        }
    }

    // 遍历链表并打印所有节点数据
    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // 查找指定值的节点
    int search(int value) {
        Node* temp = head;
        int count=1;
        while (temp != nullptr) {
            if (temp->data == value) {
                return count;  // 找到了该值
            }
            temp = temp->next;
            count++;
        }
        return -1;  // 没有找到该值
    }

    // 析构函数，释放链表中的所有节点
    ~SinglyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    SinglyLinkedList list;

    // 插入节点到链表
    list.insertAtHead(3);
    list.insertAtHead(2);
    list.insertAtTail(4);
    list.insertAtTail(5);

    // 打印链表
    std::cout << "Linked List: ";
    list.printList();

    // 查找节点
    int valueToSearch = 4;
    if (list.search(valueToSearch)!=-1) {
        std::cout << valueToSearch << " found in the list at No"<<list.search(valueToSearch)<< std::endl;
    } else {
        std::cout << valueToSearch << " not found in the list." << std::endl;
    }

    // 删除节点
    int delnode = 2;
    list.deleteNode(delnode);
    std::cout << "Linked List after deleting No."<<delnode<<": ";
    list.printList();
    std::cout<<"size:"<<list.size()<<std::endl;

    return 0;
}
