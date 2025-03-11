#include <iostream>
#include <vector>
#include <string>

class TreeNode {
public:
    int data;
    TreeNode* firstChild;
    TreeNode* nextSibling;
    
    TreeNode(int value) : data(value), firstChild(nullptr), nextSibling(nullptr) {}
};

class Tree {
private:
    TreeNode* root;

public:
    Tree() : root(nullptr) {}
    
    void insert(int parentValue, int value);
    void display();
    int countLeaves();
    int getHeight();

private:
    TreeNode* findNode(TreeNode* node, int value);
    void displayNode(TreeNode* node, std::string prefix, bool isLast);
    int countLeavesHelper(TreeNode* node);
    int getHeightHelper(TreeNode* node);
};


void Tree::insert(int parentValue, int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
        return;
    }

    TreeNode* parentNode = findNode(root, parentValue);
    if (parentNode == nullptr) {
        std::cout << "Parent node not found" << std::endl;
        return;
    }

    TreeNode* newNode = new TreeNode(value);
    if (parentNode->firstChild == nullptr) {
        parentNode->firstChild = newNode;
    } else {
        TreeNode* sibling = parentNode->firstChild;
        while (sibling->nextSibling != nullptr) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = newNode;
    }
}

TreeNode* Tree::findNode(TreeNode* node, int value) {
    if (node == nullptr) return nullptr;
    if (node->data == value) return node;

    TreeNode* found = findNode(node->firstChild, value);
    if (found != nullptr) return found;

    return findNode(node->nextSibling, value);
}

void Tree::display() {
    if (root == nullptr) {
        std::cout << "����" << std::endl;
        return;
    }
    displayNode(root, "", true);
}

void Tree::displayNode(TreeNode* node, std::string prefix, bool isLast) {
    if (node == nullptr) return;

    std::cout << prefix;
    std::cout << (isLast ? "������ " : "������ ");
    std::cout << node->data << std::endl;

    TreeNode* child = node->firstChild;
    while (child != nullptr) {
        bool lastChild = (child->nextSibling == nullptr);
        displayNode(child, prefix + (isLast ? "    " : "��   "), lastChild);
        child = child->nextSibling;
    }
}

int Tree::countLeaves() {
    return countLeavesHelper(root);
}

int Tree::countLeavesHelper(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    if (node->firstChild == nullptr) {
        return 1;  // ����һ��Ҷ�ڵ�
    }
    int count = 0;
    TreeNode* child = node->firstChild;
    while (child != nullptr) {
        count += countLeavesHelper(child);
        child = child->nextSibling;
    }
    return count;
}

int Tree::getHeight() {
    return getHeightHelper(root);
}

int Tree::getHeightHelper(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    int maxHeight = 0;
    TreeNode* child = node->firstChild;
    while (child != nullptr) {
        int childHeight = getHeightHelper(child);
        if (childHeight > maxHeight) {
            maxHeight = childHeight;
        }
        child = child->nextSibling;
    }
    return maxHeight + 1;
}


void Test(){
    Tree companyStructure;
    
    companyStructure.insert(0, 1);    // CEO (���ڵ�)
    companyStructure.insert(1, 2);    // CTO
    companyStructure.insert(1, 3);    // CFO
    companyStructure.insert(1, 4);    // COO
    companyStructure.insert(2, 5);    // ��������
    companyStructure.insert(2, 6);    // ���Ծ���
    companyStructure.insert(4, 7);    // ��Ӫ����
    companyStructure.insert(4, 8);    // ������Դ����
    companyStructure.insert(5, 9);    // �߼�������
    companyStructure.insert(5, 10);   // ����������
    companyStructure.insert(7, 11);   // �ͻ��������

    std::cout << "��˾��֯�ṹ��" << std::endl;
    companyStructure.display();

    std::cout << "Ҷ�ڵ����� (û��������Ա��): " << companyStructure.countLeaves() << std::endl;
    std::cout << "��֯�ṹ�Ĳ㼶����" << companyStructure.getHeight() << std::endl;
}

int main() {
    Tree tree;
    tree.insert(0, 1);  // ������ڵ�
    tree.insert(1, 2);  // 1 �ĵ�һ���ӽڵ�
    tree.insert(1, 3);  // 1 �ĵڶ����ӽڵ�
    tree.insert(2, 4);  // 2 ���ӽڵ�
    tree.insert(3, 5);  // 3 ���ӽڵ�

    std::cout << "Tree structure:" << std::endl;
    tree.display();

    std::cout << "Number of leaves: " << tree.countLeaves() << std::endl;
    std::cout << "Height of the tree: " << tree.getHeight() << std::endl;

    Test();

    return 0;
}