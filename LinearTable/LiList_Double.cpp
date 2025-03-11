#include <iostream>

// ˫����Ľڵ�ṹ
struct Node {
    int data;       // ������
    Node* prev;     // ָ��ǰһ���ڵ�
    Node* next;     // ָ����һ���ڵ�

    // ���캯��
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// ˫������
class DoublyLinkedList {
private:
    Node* head;     // ָ������ͷ��
    Node* tail;     // ָ������β��

public:
    // ���캯������ʼ��������
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // ������ͷ������ڵ�
    void insertAtHead(int value) {
        Node* newNode = new Node(value);  // �����½ڵ�
        if (head == nullptr) {
            head = tail = newNode;  // �������Ϊ�գ��½ڵ����ͷ�ڵ�����β�ڵ�
        } else {
            newNode->next = head;   // �½ڵ�� next ָ��ǰͷ�ڵ�
            head->prev = newNode;   // ��ǰͷ�ڵ�� prev ָ���½ڵ�
            head = newNode;         // ����ͷ�ڵ�Ϊ�½ڵ�
        }
    }

    // ������β������ڵ�
    void insertAtTail(int value) {
        Node* newNode = new Node(value);  // �����½ڵ�
        if (tail == nullptr) {
            head = tail = newNode;  // �������Ϊ�գ��½ڵ����ͷ�ڵ�����β�ڵ�
        } else {
            newNode->prev = tail;   // �½ڵ�� prev ָ��ǰβ�ڵ�
            tail->next = newNode;   // ��ǰβ�ڵ�� next ָ���½ڵ�
            tail = newNode;         // ����β�ڵ�Ϊ�½ڵ�
        }
    }

    // ɾ�������е�ָ���ڵ�
    void deleteNode(int value) {
        if (head == nullptr) return;  // �������Ϊ�գ�ֱ�ӷ���

        Node* temp = head;
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;  // �����ҵ�ֵΪ value �Ľڵ�
        }

        if (temp == nullptr) {
            std::cout << "Value not found!" << std::endl;
            return;  // û���ҵ�ֵΪ value �Ľڵ�
        }

        // ���Ҫɾ������ͷ�ڵ�
        if (temp == head) {
            head = temp->next;  // ����ͷ�ڵ�
            if (head != nullptr) {
                head->prev = nullptr;  // ������µ�ͷ�ڵ㣬�������� prev
            } else {
                tail = nullptr;  // �������Ϊ�գ�����β�ڵ�Ϊ nullptr
            }
        }
        // ���Ҫɾ������β�ڵ�
        else if (temp == tail) {
            tail = temp->prev;  // ����β�ڵ�
            if (tail != nullptr) {
                tail->next = nullptr;  // �����µ�β�ڵ�� next
            } else {
                head = nullptr;  // �������Ϊ�գ�����ͷ�ڵ�Ϊ nullptr
            }
        }
        // �м�ڵ�
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;  // �ͷ�Ҫɾ���Ľڵ�
    }

    // �����������
    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // �����������
    void printReverse() {
        Node* temp = tail;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->prev;
        }
        std::cout << std::endl;
    }

    // �����������ͷ������е����нڵ�
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

    // ����ڵ�
    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtTail(30);

    // ��ӡ����
    std::cout << "Forward: ";
    list.printList();

    std::cout << "Reverse: ";
    list.printReverse();

    // ɾ���ڵ�
    list.deleteNode(20);
    std::cout << "After deleting 20, Forward: ";
    list.printList();

    std::cout << "After deleting 20, Reverse: ";
    list.printReverse();

    return 0;
}
