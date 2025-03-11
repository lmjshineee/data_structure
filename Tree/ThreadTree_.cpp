#include <iostream>
#include <string>

using namespace std;

/**
 * ������������
 */
class HeroNode {
public:
    int id;
    string name;
    HeroNode* left;
    HeroNode* right;
    /**
     * ��ڵ�����ͣ�0����������1��ǰ���ڵ�
     */
    int leftType;
    /**
     * �ҽڵ�����ͣ�0����������1����̽ڵ�
     */
    int rightType;

    HeroNode(int id, string name) {
        this->id = id;
        this->name = name;
        this->left = nullptr;
        this->right = nullptr;
        this->leftType = 0;
        this->rightType = 0;
    }

    friend ostream& operator<<(ostream& os, const HeroNode& node) {
        os << "HeroNode{id=" << node.id << ", name='" << node.name << "'}";
        return os;
    }
};

class ThreadedBinaryTree {
public:
    HeroNode* root;
    HeroNode* pre; // ������һ���ڵ�

    ThreadedBinaryTree() {
        root = nullptr;
        pre = nullptr;
    }

    /**
     * ���������������� ����ķ�ʽ������
     */
    void threadeNodes() {
        // �� root ��ʼ������Ȼ��������
        this->threadeNodes(root);
    }

private:
    void threadeNodes(HeroNode* node) {
        if (node == nullptr) {
            return;
        }
        // �������˳�������Լ�������
        threadeNodes(node->left);
        // ���Լ��� left �ڵ�Ϊ�գ�������Ϊǰ���ڵ�
        if (node->left == nullptr) {
            node->left = pre;
            node->leftType = 1;
        }
        // ǰһ���ڵ�� right Ϊ��ʱ������Ҫ�Լ��Ǻ�̽ڵ�
        if (pre != nullptr && pre->right == nullptr) {
            pre->right = node;
            pre->rightType = 1;
        }
        // ����ǰһ���ڵ�
        pre = node;
        threadeNodes(node->right);
    }
};

// ���Ժ���
void threadeNodesTest() {
    HeroNode* n1 = new HeroNode(1, "�ν�");
    HeroNode* n3 = new HeroNode(3, "����");
    HeroNode* n6 = new HeroNode(6, "¬��");
    HeroNode* n8 = new HeroNode(8, "�ֳ� 2");
    HeroNode* n10 = new HeroNode(10, "�ֳ� 3");
    HeroNode* n14 = new HeroNode(14, "�ֳ� 4");

    n1->left = n3;
    n1->right = n6;
    n3->left = n8;
    n3->right = n10;
    n6->left = n14;

    ThreadedBinaryTree tree;
    tree.root = n1;

    tree.threadeNodes();

    // ��֤��
    HeroNode* left = n10->left;
    HeroNode* right = n10->right;
    cout << "10 �Žڵ��ǰ���ڵ㣺" << left->id << endl;
    cout << "10 �Žڵ�ĺ�̽ڵ㣺" << right->id << endl;

    // �ͷŶ�̬������ڴ�
    delete n1;
    delete n3;
    delete n6;
    delete n8;
    delete n10;
    delete n14;
}

int main() {
    threadeNodesTest();
    return 0;
}
