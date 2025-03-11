#include <iostream>
#include <string>

using namespace std;

/**
 * 线索化二叉树
 */
class HeroNode {
public:
    int id;
    string name;
    HeroNode* left;
    HeroNode* right;
    /**
     * 左节点的类型：0：左子树，1：前驱节点
     */
    int leftType;
    /**
     * 右节点的类型：0：右子树，1：后继节点
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
    HeroNode* pre; // 保留上一个节点

    ThreadedBinaryTree() {
        root = nullptr;
        pre = nullptr;
    }

    /**
     * 线索化二叉树：以 中序的方式线索化
     */
    void threadeNodes() {
        // 从 root 开始遍历，然后线索化
        this->threadeNodes(root);
    }

private:
    void threadeNodes(HeroNode* node) {
        if (node == nullptr) {
            return;
        }
        // 中序遍历顺序：先左、自己、再右
        threadeNodes(node->left);
        // 当自己的 left 节点为空，则设置为前驱节点
        if (node->left == nullptr) {
            node->left = pre;
            node->leftType = 1;
        }
        // 前一个节点的 right 为空时，则需要自己是后继节点
        if (pre != nullptr && pre->right == nullptr) {
            pre->right = node;
            pre->rightType = 1;
        }
        // 更新前一个节点
        pre = node;
        threadeNodes(node->right);
    }
};

// 测试函数
void threadeNodesTest() {
    HeroNode* n1 = new HeroNode(1, "宋江");
    HeroNode* n3 = new HeroNode(3, "无用");
    HeroNode* n6 = new HeroNode(6, "卢俊");
    HeroNode* n8 = new HeroNode(8, "林冲 2");
    HeroNode* n10 = new HeroNode(10, "林冲 3");
    HeroNode* n14 = new HeroNode(14, "林冲 4");

    n1->left = n3;
    n1->right = n6;
    n3->left = n8;
    n3->right = n10;
    n6->left = n14;

    ThreadedBinaryTree tree;
    tree.root = n1;

    tree.threadeNodes();

    // 验证：
    HeroNode* left = n10->left;
    HeroNode* right = n10->right;
    cout << "10 号节点的前驱节点：" << left->id << endl;
    cout << "10 号节点的后继节点：" << right->id << endl;

    // 释放动态分配的内存
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
