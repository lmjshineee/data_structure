#include <iostream>
/*
��ͷ�ڵ�ĵ����� �����нڵ㶼�����ݽڵ�
*/

struct Node {
    int data;      // ������
    Node* next;    // ָ����һ���ڵ��ָ��

    // ���캯�������ڳ�ʼ���ڵ�
    Node(int value) : data(value), next(nullptr) {}
};


class SinglyLinkedList {
private:
    Node* head;  // ָ������ͷ����ָ��

public:
    // ���캯������ʼ������Ϊ��
    SinglyLinkedList() : head(nullptr) {}

    // ������
    int size() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // ����ڵ㵽�����ͷ��
    void insertAtHead(int value) {
        Node* newNode = new Node(value);  // �����½ڵ�
        newNode->next = head;             // ���½ڵ�� next ָ��ǰ��ͷ�ڵ�
        head = newNode;                   // ����ͷ�ڵ�Ϊ�½ڵ�
    }

    // ����ڵ㵽�����β��
    void insertAtTail(int value) {
        Node* newNode = new Node(value);  // �����½ڵ�
        if (head == nullptr) {
            head = newNode;               // �������Ϊ�գ�ֱ�Ӳ��뵽ͷ��
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {  // �����ҵ���������һ���ڵ�
                temp = temp->next;
            }
            temp->next = newNode;            // �����һ���ڵ�� next ָ���½ڵ�
        }
    }

    // ɾ��ָ��λ�õĽڵ�
    void deleteNode(int position) {
        if (head == nullptr||position>size()) return;  // �������Ϊ�գ�ֱ�ӷ���

        if (position==0) {    // ���Ҫɾ������ͷ�ڵ�
            Node* temp = head;
            head = head->next;        // ����ͷ�ڵ�
            delete temp;              // ɾ��ԭͷ�ڵ�
            return;
        }

        Node* temp = head;
        for(int i=0; i<position-1; i++) {
            temp = temp->next;
        }

        if (temp->next != nullptr) {  // ����ҵ���Ҫɾ���Ľڵ�
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;  // ��������ָ������Ҫɾ���Ľڵ�
            delete nodeToDelete;            // ɾ���ڵ�
        }
    }

    // ����������ӡ���нڵ�����
    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // ����ָ��ֵ�Ľڵ�
    int search(int value) {
        Node* temp = head;
        int count=1;
        while (temp != nullptr) {
            if (temp->data == value) {
                return count;  // �ҵ��˸�ֵ
            }
            temp = temp->next;
            count++;
        }
        return -1;  // û���ҵ���ֵ
    }

    // �����������ͷ������е����нڵ�
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

    // ����ڵ㵽����
    list.insertAtHead(3);
    list.insertAtHead(2);
    list.insertAtTail(4);
    list.insertAtTail(5);

    // ��ӡ����
    std::cout << "Linked List: ";
    list.printList();

    // ���ҽڵ�
    int valueToSearch = 4;
    if (list.search(valueToSearch)!=-1) {
        std::cout << valueToSearch << " found in the list at No"<<list.search(valueToSearch)<< std::endl;
    } else {
        std::cout << valueToSearch << " not found in the list." << std::endl;
    }

    // ɾ���ڵ�
    int delnode = 2;
    list.deleteNode(delnode);
    std::cout << "Linked List after deleting No."<<delnode<<": ";
    list.printList();
    std::cout<<"size:"<<list.size()<<std::endl;

    return 0;
}
