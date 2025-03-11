#include <iostream>
#include <algorithm>

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node *left, *right;
        int height;

        Node(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node *root;

    int getHeight(Node *node) {
        return node ? node->height : 0;
    }

    int getBalance(Node *node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x; // Return new root
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y; // Return new root
    }

    Node *insert(Node *node, T key) {
        // Normal BST insertion
        if (!node) return new Node(key);

        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        } else {
            return node; // Duplicate keys are not allowed
        }

        // Update height of this ancestor node
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        // Get the balance factor
        int balance = getBalance(node);

        // If the node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->data) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && key > node->right->data) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // Return the (unchanged) node pointer
    }

    void preOrder(Node *node) {
        if (node) {
            std::cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void inOrder(Node *node) {
        if (node) {
            inOrder(node->left);
            std::cout << node->data << " ";
            inOrder(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T key) {
        root = insert(root, key);
    }

    void preOrder() {
        preOrder(root);
    }

    void inOrder() {
        inOrder(root);
    }
};

// 示例用法
int main() {
    AVLTree<int> avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    std::cout << "AVL 树的前序遍历结果：";
    avl.preOrder();
    std::cout << std::endl;

    std::cout << "AVL 树的中序遍历结果：";
    avl.inOrder();
    std::cout << std::endl;

    return 0;
}
