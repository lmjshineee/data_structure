#include <iostream>

template <typename T>
class RedBlackTree {
private:
    struct Node {
        T data;
        bool color; // true for Red, false for Black
        Node *left, *right, *parent;

        Node(T data) : data(data), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *root;
    Node *TNULL;

    void initializeNULLNode(Node *node, Node *parent) {
        node->data = 0;
        node->color = false; // black
        node->left = nullptr;
        node->right = nullptr;
        node->parent = parent;
    }

    void preOrderHelper(Node *node) {
        if (node != TNULL) {
            std::cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(Node *node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            std::cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    void fixInsert(Node *k) {
        Node *u;
        while (k->parent->color == true) {
            if (k->parent == k->parent->parent->left) {
                u = k->parent->parent->right;
                if (u->color == true) {
                    k->parent->color = false;
                    u->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    rightRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->left;
                if (u->color == true) {
                    k->parent->color = false;
                    u->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    leftRotate(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = false;
    }

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

public:
    RedBlackTree() {
        TNULL = new Node(0);
        TNULL->color = false;
        root = TNULL;
    }

    void preOrder() {
        preOrderHelper(this->root);
    }

    void inOrder() {
        inOrderHelper(this->root);
    }

    void insert(T key) {
        Node *node = new Node(key);
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;

        Node *y = nullptr;
        Node *x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = false;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }
};

// 示例用法
int main() {
    RedBlackTree<int> rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(5);
    rbt.insert(6);
    rbt.insert(12);
    rbt.insert(30);
    rbt.insert(7);
    rbt.insert(17);

    std::cout << "红黑树的前序遍历结果：";
    rbt.preOrder();
    std::cout << std::endl;

    std::cout << "红黑树的中序遍历结果：";
    rbt.inOrder();
    std::cout << std::endl;

    return 0;
}
